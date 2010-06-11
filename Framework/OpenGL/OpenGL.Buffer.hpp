#pragma once

#define GL_GLEXT_PROTOTYPES

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

namespace OpenGL
{
    class Buffer
    {
        public:
            Buffer(GLenum target, GLsizeiptr size);
            ~Buffer();

            void Bind();
            void *Map();
            void UnMap();

            GLuint Handle;
            GLenum Target;
    };
};
