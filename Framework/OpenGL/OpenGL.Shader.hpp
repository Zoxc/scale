#pragma once

#include <GLES2/gl2.h>

namespace OpenGL
{
    class Shader
    {
        public:
            Shader(GLenum type, char* Source);
            ~Shader();

            GLuint Handle;
    };
};
