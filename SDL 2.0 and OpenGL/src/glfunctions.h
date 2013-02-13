#ifndef GLFUNCTIONS_H
#define GLFUNCTIONS_H

#include <SDL_opengl.h>

/**
*  A namespace to contain the various gl* functions,
*  and a function to get them all via SDL_GL_ProcAddress which 
*  should be called after creating the SDL GL context
*/
namespace GL {
    /**
    *  Get all the GL functions via SDL_GL_ProcAddress
    */
    void SetupGLFunctions();
    ///The GL functions
    extern PFNGLGENVERTEXARRAYSPROC GenVertexArrays;
    extern PFNGLDELETEVERTEXARRAYSPROC DeleteVertexArrays;
    extern PFNGLBINDVERTEXARRAYPROC BindVertexArray;
    extern PFNGLGENBUFFERSPROC GenBuffers;
    extern PFNGLDELETEBUFFERSPROC DeleteBuffers;
    extern PFNGLBINDBUFFERPROC BindBuffer;
    extern PFNGLBUFFERDATAPROC BufferData;
    extern PFNGLENABLEVERTEXATTRIBARRAYPROC EnableVertexAttribArray;
    extern PFNGLVERTEXATTRIBPOINTERPROC VertexAttribPointer;
    extern PFNGLDISABLEVERTEXATTRIBARRAYPROC DisableVertexAttribArray;
    extern PFNGLCREATESHADERPROC CreateShader;
    extern PFNGLSHADERSOURCEPROC ShaderSource;
    extern PFNGLCOMPILESHADERPROC CompileShader;
    extern PFNGLGETSHADERIVPROC GetShaderiv;
    extern PFNGLGETSHADERINFOLOGPROC GetShaderInfoLog;
    extern PFNGLCREATEPROGRAMPROC CreateProgram;
    extern PFNGLATTACHSHADERPROC AttachShader;
    extern PFNGLLINKPROGRAMPROC LinkProgram;
    extern PFNGLGETPROGRAMIVPROC GetProgramiv;
    extern PFNGLGETPROGRAMINFOLOGPROC GetProgramInfoLog;
    extern PFNGLDETACHSHADERPROC DetachShader;
    extern PFNGLDELETESHADERPROC DeleteShader;
    extern PFNGLUSEPROGRAMPROC UseProgram;
    extern PFNGLDELETEPROGRAMPROC DeleteProgram;
    extern PFNGLGETUNIFORMLOCATIONPROC GetUniformLocation;
    extern PFNGLUNIFORM1FPROC Uniform1f;
    extern PFNGLUNIFORMMATRIX4FVPROC UniformMatrix4fv;
    extern PFNGLGETATTRIBLOCATIONPROC GetAttribLocation;
    extern PFNGLVERTEXATTRIB1FPROC VertexAttrib1F;
    extern PFNGLACTIVETEXTUREPROC ActiveTexture;
}

#endif