#include <SDL.h>
#include <SDL_opengl.h>
#include "glfunctions.h"

void GL::SetupGLFunctions(){
    SetProcAddress(GenVertexArrays, "glGenVertexArrays");
    SetProcAddress(DeleteVertexArrays, "glDeleteVertexArrays");
    SetProcAddress(BindVertexArray, "glBindVertexArray");
    SetProcAddress(GenBuffers, "glGenBuffers");
    SetProcAddress(DeleteBuffers, "glDeleteBuffers");
    SetProcAddress(BindBuffer, "glBindBuffer");
    SetProcAddress(BufferData, "glBufferData");
    SetProcAddress(EnableVertexAttribArray, "glEnableVertexAttribArray");
    SetProcAddress(VertexAttribPointer, "glVertexAttribPointer");
    SetProcAddress(DisableVertexAttribArray, "glDisableVertexAttribArray");
    SetProcAddress(CreateShader, "glCreateShader");
    SetProcAddress(ShaderSource, "glShaderSource");
    SetProcAddress(CompileShader, "glCompileShader");
    SetProcAddress(GetShaderiv, "glGetShaderiv");
    SetProcAddress(GetShaderInfoLog, "glGetShaderInfoLog");
    SetProcAddress(CreateProgram, "glCreateProgram");
    SetProcAddress(AttachShader, "glAttachShader");
    SetProcAddress(LinkProgram, "glLinkProgram");
    SetProcAddress(GetProgramiv, "glGetProgramiv");
    SetProcAddress(GetProgramInfoLog, "glGetProgramInfoLog");
    SetProcAddress(DetachShader, "glDetachShader");
    SetProcAddress(DeleteShader, "glDeleteShader");
    SetProcAddress(UseProgram, "glUseProgram");
    SetProcAddress(DeleteProgram, "glDeleteProgram");
    SetProcAddress(GetUniformLocation, "glGetUniformLocation");
    SetProcAddress(Uniform1f, "glUniform1f");
    SetProcAddress(UniformMatrix4fv, "glUniformMatrix4fv");
    SetProcAddress(GetAttribLocation, "glGetAttribLocation");
    SetProcAddress(VertexAttrib1f, "glVertexAttrib1f");
    SetProcAddress(ActiveTexture, "glActiveTexture");
    SetProcAddress(GenerateMipMap, "glGenerateMipMap");
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
PFNGLVERTEXATTRIB1FPROC GL::VertexAttrib1f = nullptr;
PFNGLACTIVETEXTUREPROC GL::ActiveTexture = nullptr;
PFNGLGENERATEMIPMAPPROC GL::GenerateMipMap = nullptr;