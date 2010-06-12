#include <iostream>
#include <malloc.h>
#include "OpenGL.Buffer.hpp"


PFNGLMAPBUFFEROESPROC glMapBufferOES;
PFNGLUNMAPBUFFEROESPROC glUnmapBufferOES;

void OpenGL::Buffer::Init()
{
    glMapBufferOES = (PFNGLMAPBUFFEROESPROC)eglGetProcAddress("glMapBufferOES");
    glUnmapBufferOES = (PFNGLUNMAPBUFFEROESPROC)eglGetProcAddress("glUnmapBufferOES");
}

OpenGL::Buffer::Buffer(GLenum target, GLsizeiptr size) : Target(target), Size(size)
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
    /*Bind();
    return glMapBufferOES(Target, GL_WRITE_ONLY_OES);*/
    Mapped = malloc(Size);
    return Mapped;
}

void OpenGL::Buffer::UnMap()
{
    /*glUnmapBufferOES(Target);*/
    Bind();
    glBufferData(Target, Size, Mapped, GL_STATIC_DRAW);
    free(Mapped);
}

OpenGL::Buffer::~Buffer()
{
    if(Handle != 0)
        glDeleteBuffers(1, &Handle);
}
