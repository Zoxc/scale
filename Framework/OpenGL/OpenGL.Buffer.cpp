#include <iostream>
#include "OpenGL.Buffer.hpp"

OpenGL::Buffer::Buffer(GLenum target, GLsizeiptr size) : Target(target)
{
    glGenBuffers(1, &Handle);
    Bind();
    glBufferData(Target, size, 0, GL_STATIC_DRAW);
}

void OpenGL::Buffer::Bind()
{
    glBindBuffer(Target, Handle);
}

void *OpenGL::Buffer::Map()
{
    Bind();
    return glMapBufferOES(Target, GL_WRITE_ONLY_OES);
}

void OpenGL::Buffer::UnMap()
{
    glUnmapBufferOES(Target);
}

OpenGL::Buffer::~Buffer()
{
    if(Handle != 0)
        glDeleteBuffers(1, &Handle);
}
