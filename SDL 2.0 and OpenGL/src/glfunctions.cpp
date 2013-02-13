#include <SDL.h>
#include <SDL_opengl.h>
#include "glfunctions.h"

void GL::SetupGLFunctions(){
    GenVertexArrays =           (PFNGLGENVERTEXARRAYSPROC)SDL_GL_GetProcAddress("glGenVertexArrays");
    DeleteVertexArrays =        (PFNGLDELETEVERTEXARRAYSPROC)SDL_GL_GetProcAddress("glDeleteVertexArrays");
    BindVertexArray =           (PFNGLBINDVERTEXARRAYPROC)SDL_GL_GetProcAddress("glBindVertexArray");
    GenBuffers =                (PFNGLGENBUFFERSPROC)SDL_GL_GetProcAddress("glGenBuffers");
    DeleteBuffers =             (PFNGLDELETEBUFFERSPROC)SDL_GL_GetProcAddress("glDeleteBuffers");
    BindBuffer =                (PFNGLBINDBUFFERPROC)SDL_GL_GetProcAddress("glBindBuffer");
    BufferData =                (PFNGLBUFFERDATAPROC)SDL_GL_GetProcAddress("glBufferData");
    EnableVertexAttribArray =   (PFNGLENABLEVERTEXATTRIBARRAYPROC)SDL_GL_GetProcAddress("glEnableVertexAttribArray");
    VertexAttribPointer =       (PFNGLVERTEXATTRIBPOINTERPROC)SDL_GL_GetProcAddress("glVertexAttribPointer");
    DisableVertexAttribArray =  (PFNGLDISABLEVERTEXATTRIBARRAYPROC)SDL_GL_GetProcAddress("glDisableVertexAttribArray");
    CreateShader =              (PFNGLCREATESHADERPROC)SDL_GL_GetProcAddress("glCreateShader");
    ShaderSource =              (PFNGLSHADERSOURCEPROC)SDL_GL_GetProcAddress("glShaderSource");
    CompileShader =             (PFNGLCOMPILESHADERPROC)SDL_GL_GetProcAddress("glCompileShader");
    GetShaderiv =               (PFNGLGETSHADERIVPROC)SDL_GL_GetProcAddress("glGetShaderiv");
    GetShaderInfoLog =          (PFNGLGETSHADERINFOLOGPROC)SDL_GL_GetProcAddress("glGetShaderInfoLog");
    CreateProgram =             (PFNGLCREATEPROGRAMPROC)SDL_GL_GetProcAddress("glCreateProgram");
    AttachShader =              (PFNGLATTACHSHADERPROC)SDL_GL_GetProcAddress("glAttachShader");
    LinkProgram =               (PFNGLLINKPROGRAMPROC)SDL_GL_GetProcAddress("glLinkProgram");
    GetProgramiv =              (PFNGLGETPROGRAMIVPROC)SDL_GL_GetProcAddress("glGetProgramiv");
    GetProgramInfoLog =         (PFNGLGETPROGRAMINFOLOGPROC)SDL_GL_GetProcAddress("glGetProgramInfoLog");
    DetachShader =              (PFNGLDETACHSHADERPROC)SDL_GL_GetProcAddress("glDetachShader");
    DeleteShader =              (PFNGLDELETESHADERPROC)SDL_GL_GetProcAddress("glDeleteShader");
    UseProgram =                (PFNGLUSEPROGRAMPROC)SDL_GL_GetProcAddress("glUseProgram");
    DeleteProgram =             (PFNGLDELETEPROGRAMPROC)SDL_GL_GetProcAddress("glDeleteProgram");
    GetUniformLocation =        (PFNGLGETUNIFORMLOCATIONPROC)SDL_GL_GetProcAddress("glGetUniformLocation");
    Uniform1f =                 (PFNGLUNIFORM1FPROC)SDL_GL_GetProcAddress("glUniform1f");
    UniformMatrix4fv =          (PFNGLUNIFORMMATRIX4FVPROC)SDL_GL_GetProcAddress("glUniformMatrix4fv");
    GetAttribLocation =         (PFNGLGETATTRIBLOCATIONPROC)SDL_GL_GetProcAddress("glGetAttribLocation");
    VertexAttrib1F =            (PFNGLVERTEXATTRIB1FPROC)SDL_GL_GetProcAddress("glVertexAttrib1F");
    ActiveTexture =             (PFNGLACTIVETEXTUREPROC)SDL_GL_GetProcAddress("glActiveTexture");
}
PFNGLGENVERTEXARRAYSPROC GL::GenVertexArrays = nullptr;
PFNGLDELETEVERTEXARRAYSPROC GL::DeleteVertexArrays = nullptr;
PFNGLBINDVERTEXARRAYPROC GL::BindVertexArray = nullptr;
PFNGLGENBUFFERSPROC GL::GenBuffers = nullptr;
PFNGLDELETEBUFFERSPROC GL::DeleteBuffers = nullptr;
PFNGLBINDBUFFERPROC GL::BindBuffer = nullptr;
PFNGLBUFFERDATAPROC GL::BufferData = nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC GL::EnableVertexAttribArray = nullptr;
PFNGLVERTEXATTRIBPOINTERPROC GL::VertexAttribPointer = nullptr;
PFNGLDISABLEVERTEXATTRIBARRAYPROC GL::DisableVertexAttribArray = nullptr;
PFNGLCREATESHADERPROC GL::CreateShader = nullptr;
PFNGLSHADERSOURCEPROC GL::ShaderSource = nullptr;
PFNGLCOMPILESHADERPROC GL::CompileShader = nullptr;
PFNGLGETSHADERIVPROC GL::GetShaderiv = nullptr;
PFNGLGETSHADERINFOLOGPROC GL::GetShaderInfoLog = nullptr;
PFNGLCREATEPROGRAMPROC GL::CreateProgram = nullptr;
PFNGLATTACHSHADERPROC GL::AttachShader = nullptr;
PFNGLLINKPROGRAMPROC GL::LinkProgram = nullptr;
PFNGLGETPROGRAMIVPROC GL::GetProgramiv = nullptr;
PFNGLGETPROGRAMINFOLOGPROC GL::GetProgramInfoLog = nullptr;
PFNGLDETACHSHADERPROC GL::DetachShader = nullptr;
PFNGLDELETESHADERPROC GL::DeleteShader = nullptr;
PFNGLUSEPROGRAMPROC GL::UseProgram = nullptr;
PFNGLDELETEPROGRAMPROC GL::DeleteProgram = nullptr;
PFNGLGETUNIFORMLOCATIONPROC GL::GetUniformLocation = nullptr;
PFNGLUNIFORM1FPROC GL::Uniform1f = nullptr;
PFNGLUNIFORMMATRIX4FVPROC GL::UniformMatrix4fv = nullptr;
PFNGLGETATTRIBLOCATIONPROC GL::GetAttribLocation = nullptr;
PFNGLVERTEXATTRIB1FPROC GL::VertexAttrib1F = nullptr;
PFNGLACTIVETEXTUREPROC GL::ActiveTexture = nullptr;