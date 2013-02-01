#include <SDL.h>
#include <SDL_opengl.h>
#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "glfunctions.h"
#include "window.h"

SDL_Window *win = nullptr;
SDL_GLContext glContext;

//The vertex buffer
GLuint vertexBuffer;
//Shader program
GLuint programID;

//Vertex buffer data for a triangle
static const float vertexBufferData[] = {
    0.75f, 0.75f, 0.0f, 1.0f,
    0.75f, -0.75f, 0.0f, 1.0f,
    -0.75f, -0.75f, 0.0f, 1.0f,
};
//Vertex buffer data for a triangle and colors to use for it
static const float coloredVertexBufferData[] = {
    0.0f, 0.5f, 0.0f, 1.0f,
    0.5f, -0.366f, 0.0f, 1.0f,
    -0.5f, -0.366f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
};

bool InitSDLGL(){
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
        return false;

    //Enable 8x AA
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

    win = SDL_CreateWindow("SDL GL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    //Create the gl context and setup matrix
    glContext = SDL_GL_CreateContext(win);
    //Is glMatrixMode and LoadIdentity used at all in OpenGL3+ when using shaders? I don't think it is
    /*glMatrixMode(GL_PROJECTION | GL_MODELVIEW);
    glLoadIdentity();*/
    glEnable(GL_MULTISAMPLE_ARB);
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
    //Use the shader
    GL::UseProgram(programID);

    //Set the state to be drawn
    GL::BindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    GL::EnableVertexAttribArray(0);
    GL::EnableVertexAttribArray(1);
    GL::VertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    GL::VertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)48);

    //Draw the state
    //We draw 6 verts bc we have that many in the array. How can i do without hardcoding?
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    GL::DisableVertexAttribArray(0);
    GL::DisableVertexAttribArray(1);
    GL::BindBuffer(GL_ARRAY_BUFFER, 0);
    GL::UseProgram(0);
}
#undef main
int main(int argc, char** argv){
    //Window::Init("Lesson 7");
    InitSDLGL();

    //Load the shaders
    //programID = LoadShaders("../res/shader.v.glsl", "../res/shader.f.glsl");
    InitializeShaderProgram();
    //Todo: GL_VERTEX_ARRAY?
    //Create our vertex buffer
    GL::GenBuffers(1, &vertexBuffer);
    GL::BindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    //Use stream draw if planning to move the object
    GL::BufferData(GL_ARRAY_BUFFER, sizeof(coloredVertexBufferData), coloredVertexBufferData, GL_STATIC_DRAW);
    GL::BindBuffer(GL_ARRAY_BUFFER, 0);

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
        //Window::Clear();
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        DrawGLTriangle();

        SDL_GL_SwapWindow(win);

        //Window::Present();
	}
    GL::DeleteProgram(programID);
    GL::DeleteBuffers(1, &vertexBuffer);
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(win);
    //Window::Quit();
	
	return 0;
}