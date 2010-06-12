#pragma once

#include "EGL/egl.h"
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

            static void Init();

            GLuint Handle;
            GLenum Target;
    };
};
