#include <iostream>
#include "OpenGL.Shader.hpp"

OpenGL::Shader::Shader(GLenum type, const char* Source)
{
    Handle = glCreateShader(type);

    glShaderSource(Handle, 1, &Source, 0);

    glCompileShader(Handle);

    GLint Compiled;
    glGetShaderiv(Handle, GL_COMPILE_STATUS, &Compiled);

    if (!Compiled)
    {
        int LogLength, CharsWritten;
        glGetShaderiv(Handle, GL_INFO_LOG_LENGTH, &LogLength);

        char* Log = new char[LogLength];
        glGetShaderInfoLog(Handle, LogLength, &CharsWritten, Log);

        std::cout << "Failed to compile shader: " << Log << "\n";

        delete[] Log;

        throw "Failed to compile shader";
    }
}

OpenGL::Shader::~Shader()
{
    /*if(Handle != 0)
        glDeleteShader(Handle);*/
}


