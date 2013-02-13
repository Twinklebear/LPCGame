#ifndef GLSHADER_H
#define GLSHADER_H

#include <string>
#include <vector>
#include <SDL_opengl.h>

//namespace GL {
//    /**
//    * A lightweight class to make dealing with OpenGL shader objects
//    * simpler
//    */
//    class ShaderProgram {
//    public:
//        ShaderProgram(std::string vertShader, std::string fragShader);
//        ~ShaderProgram();
//        /**
//        * Get the shader program reference
//        */
//        GLuint getProgram();
//
//    private:
//        /**
//        * Read the text of a shader program file
//        */
//        std::string ReadShader(const std::string &shaderFile);
//        /**
//        * Compile the shader program for a shader type with some program file
//        */
//        GLuint CreateShader(GLenum shaderType, const std::string &shaderFile);
//        /**
//        * Link the shaders into a program
//        */
//        GLuint CreateShaderProgram(const std::vector<GLuint> &shaders);
//
//    private:
//        //The OpenGL shader program reference
//        GLuint program;
//    };
//}

#endif