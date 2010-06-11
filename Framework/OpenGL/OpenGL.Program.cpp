#include <iostream>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "OpenGL.Program.hpp"

OpenGL::Program::Program():
    Linked(false)
{
    Handle = glCreateProgram();
}

void OpenGL::Program::operator<<(Shader shader)
{
    glAttachShader(Handle, shader.Handle);
}

void OpenGL::Program::Link()
{
    if(Linked)
        return;

    // Link the program
    glLinkProgram(Handle);

    // Check if linking succeeded in the same way we checked for compilation success
    GLint LinkedStatus;
    glGetProgramiv(Handle, GL_LINK_STATUS, &LinkedStatus);

    if (!LinkedStatus)
    {
        int LogLength, CharsWritten;

        glGetProgramiv(Handle, GL_INFO_LOG_LENGTH, &LogLength);

        char* Log = new char[LogLength];

        glGetProgramInfoLog(Handle, LogLength, &CharsWritten, Log);

        std::cout << "Failed to link program: " << Log << "\n";

        delete[] Log;

        throw "Failed to link program";
    }

    Linked = true;
}

void OpenGL::Program::Assign()
{
    if(!Linked)
        Link();

    glUseProgram(Handle);
}

OpenGL::Program::~Program()
{
    glDeleteProgram(Handle);
}


