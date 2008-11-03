/*
    Scale - An shell for Pandora, a handheld gaming device.
    Copyright (C) 2008 Zoxc

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#include "OpenGL/OpenGL.Texture.hpp"

namespace Scale
{
    namespace Graphics
    {
        void AlphaTexture(OpenGL::Texture* Tex, int X, int Y, unsigned char R, unsigned char G, unsigned char B, unsigned char Alpha);
        void Texture(OpenGL::Texture* Tex, int X, int Y, unsigned char Alpha);
        void Rect(int X, int Y, int Width, int Height, unsigned char R, unsigned char G, unsigned char B, unsigned char Alpha);
        void RoundRect(int X, int Y, int Width, int Height, unsigned char R, unsigned char G, unsigned char B, unsigned char Alpha);
    };
};
