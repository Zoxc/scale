#pragma once
#include <GLES2/gl2.h>

namespace OpenGL
{
    class Texture
    {
        public:
            Texture();
            ~Texture();

            void Load(const char* FileName);

            bool Allocated;

            int Width;
            int Height;

            GLuint Handle;
    };
};
