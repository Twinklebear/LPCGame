#include <SDL.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "glfunctions.h"
#include "handle.h"
#include "window.h"

SDL_Window *win = nullptr;
SDL_GLContext glContext;

//The vertex array object
//GLuint vao;
GL::Handle vertexArrObj;
//Shader program
GLuint programID;

//Vertex buffer data for a triangle
static const float vertexBufferData[] = {
    0.75f, 0.75f, 1.0f, 1.0f,
    0.75f, -0.75f, 1.0f, 1.0f,
    -0.75f, -0.75f, 1.0f, 1.0f
};

bool InitSDLGL(){
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
        return false;

    //Enable 8x AA
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    win = SDL_CreateWindow("SDL GL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    //Create the gl context and setup matrix
    glContext = SDL_GL_CreateContext(win);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    GL::SetupGLFunctions();

    //print the GL version
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl
        << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl
        << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl
        << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n\n";

    return true;
}
std::string ReadShader(const std::string &shaderFile){
    std::string shaderCode = "";
    std::ifstream shaderFStream(shaderFile);
    if (shaderFStream.is_open()){
        std::string line = "";
        while (std::getline(shaderFStream, line))
            shaderCode += line + "\n";
        
        shaderFStream.close();
    }
    return shaderCode;
}
GLuint CreateShader(GLenum shaderType, const std::string &shaderFile){
    GLuint shader = GL::CreateShader(shaderType);
    std::string shaderCode = ReadShader(shaderFile);
    const char *shaderCodeCStr = shaderCode.c_str();
    GL::ShaderSource(shader, 1, &shaderCodeCStr, NULL);

    GL::CompileShader(shader);

    //Check status of compilation
    GLint status;
    GL::GetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE){
        GLint infoLogLength;
        GL::GetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        std::vector<char> shaderErrMsg(infoLogLength);
        GL::GetShaderInfoLog(shader, infoLogLength, NULL, &shaderErrMsg[0]);

        std::string strShaderType = "";
        switch (shaderType){
            case GL_VERTEX_SHADER:  
                strShaderType = "Vertex";
                break;
            case GL_GEOMETRY_SHADER:
                strShaderType = "Geometry";
                break;
            case GL_FRAGMENT_SHADER:
                strShaderType = "Fragment";
                break;
        }
        std::cout << strShaderType << " compilation errors: ";
        for (int i = 0; i < shaderErrMsg.size(); ++i)
            std::cout << shaderErrMsg[i];
        std::cout << std::endl;
    }
    return shader;
}
GLuint CreateShaderProgram(const std::vector<GLuint> &shaders){
    GLuint program = GL::CreateProgram();
    //Attach the shaders
    for (GLuint s : shaders)
        GL::AttachShader(program, s);

    GL::LinkProgram(program);

    //Check for errors
    GLint status;
    GL::GetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE){
        GLint infoLogLength;
        GL::GetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<char> programErrMsg(std::max(infoLogLength, 1));
        GL::GetProgramInfoLog(program, infoLogLength, NULL, &programErrMsg[0]);

        std::cout << "Program errors: ";
        for (int i = 0; i < programErrMsg.size(); ++i)
            std::cout << programErrMsg[i];
        std::cout << std::endl;
    }
    //Detach the shaders
    for (GLuint s : shaders)
        GL::DetachShader(program, s);

    return program;
}
//Can make more generic, take the filenames, return the GLuint
void InitializeShaderProgram(){
    std::vector<GLuint> shaderList;
    shaderList.push_back(CreateShader(GL_VERTEX_SHADER, "../res/shader.v.glsl"));
    shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, "../res/shader.f.glsl"));

    programID = CreateShaderProgram(shaderList);
    //clean up the shaders
    std::for_each(shaderList.begin(), shaderList.end(), GL::DeleteShader);
}
void DrawGLTriangle(){
    //Draw our triangle VAO
    GL::UseProgram(programID);
    GL::BindVertexArray(vertexArrObj);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    GL::BindVertexArray(0);
    GL::UseProgram(0);
}

int TestHandle(){
    GLuint a = 10;
    auto funDel = [](GLuint x){ std::cout << "i'm deleting: " << x << std::endl; };
    GL::Handle h1(a, funDel);
    GL::Handle h2(h1);
    GLuint b = 20;
    GL::Handle h3(b, funDel);
    std::cout << "setting h3 = h2" << std::endl;
    h3 = h2;
    std::cout << "set" << std::endl;

    return 0;
}

//#undef main
int main(int argc, char** argv){
    //return TestHandle();

    InitSDLGL();

    //Load the shaders
    InitializeShaderProgram();
    
    //Create our vertex buffer
    GLuint vbo;
    GL::GenBuffers(1, &vbo);
    GL::BindBuffer(GL_ARRAY_BUFFER, vbo);
    //Use shaders + transform matrices to move object
    GL::BufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);
    GL::BindBuffer(GL_ARRAY_BUFFER, 0);

    //Setup the VAO to draw
    GLuint vao;
    GL::GenVertexArrays(1, &vao);
    GL::BindVertexArray(vao);
    GL::BindBuffer(GL_ARRAY_BUFFER, vbo);

    //Set attribs for program
    GLint posAttrib = GL::GetAttribLocation(programID, "position");
    GL::EnableVertexAttribArray(posAttrib);
    GL::VertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);

    //Need to bind when setting uniforms
    GL::UseProgram(programID);
    GLint widthAttrib = GL::GetUniformLocation(programID, "width");
    GL::Uniform1f(widthAttrib, 480.0f);

    //Setup model matrix
    glm::mat4x4 model = glm::scale<GLfloat>(0.5, 0.5, 0.5);// * glm::rotate<GLfloat>(-5, glm::vec3(0, 0, 1));

    //Setup view matrix
    glm::mat4x4 view = glm::lookAt<GLfloat>(glm::vec3(0, 0, 1), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

    //Setup projection matrix
    glm::mat4x4 ortho = glm::ortho<GLfloat>(-1.0, 1.0, -1.0, 1.0, -1.0, 100.0);
    glm::mat4x4 persp = glm::perspective<GLfloat>(45.0f, 640.0f/480.0f, 0.1f, 100.0f);

    //Create & pass the MVP matrix
    GLint mvpAttrib = GL::GetUniformLocation(programID, "mvp");
    glm::mat4x4 mvp = ortho * view * model;
    GL::UniformMatrix4fv(mvpAttrib, 1, GL_FALSE, glm::value_ptr(mvp));

    GL::UseProgram(0);

    //Unbind the state
    GL::BindBuffer(GL_ARRAY_BUFFER, 0);
    GL::BindVertexArray(0);

    //Store the vao in the handle, we also make this anonymous fcn because GL::DeleteVertexArrays takes a 
    //number of arrs and a pointer to the first in the array to be freed
    auto vaoDeleter = [](GLuint x){ GL::DeleteVertexArrays(1, &x); };
    vertexArrObj = GL::Handle(vao, vaoDeleter);

    //Our event structure
	SDL_Event e;
	//For tracking if we want to quit
	bool quit = false;
	while (!quit){
		//Event Polling
		while (SDL_PollEvent(&e)){
			//If user closes he window
			if (e.type == SDL_QUIT)
				quit = true;
			//If user presses any key
			if (e.type == SDL_KEYDOWN){
				switch (e.key.keysym.sym){
					//For quitting, escape key
					case SDLK_ESCAPE:
						quit = true;
						break;
					default:
						break;
				}
			}
		}
        //RENDERING
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        DrawGLTriangle();

        SDL_GL_SwapWindow(win);
	}
    GL::DeleteProgram(programID);
    //GL::DeleteVertexArrays(1, &vao);
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(win);
    SDL_Quit();

	return 0;
}