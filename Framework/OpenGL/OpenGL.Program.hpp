#pragma once

#include "OpenGL.Shader.hpp"

namespace OpenGL
{
    class Program
    {
        public:
            Program();
            ~Program();

            bool Linked;

            void Link();
            void Assign();

            void operator<<(Shader shader);

            GLuint Handle;
    };
};
