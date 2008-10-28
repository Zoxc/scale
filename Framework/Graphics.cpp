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

#include <math.h>

#include "Element.hpp"
#include "Graphics.hpp"

void Graphics::Texture(OpenGL::Texture* Tex, int X, int Y, unsigned char Alpha)
{
    GLshort Positions[] = {
        X, Y + Tex->Height,
        X, Y,
        X + Tex->Width, Y + Tex->Height,
        X + Tex->Width, Y
    };

    glBindTexture(GL_TEXTURE_2D, Tex->Handle);
    glUniform1i(Screen->TexturedUniform, 1);
    glUniform1i(Screen->TextureUniform, 0);
    glUniform4f(Screen->ColorUniform, 0, 0, 0, Alpha / 255.0f);

    glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, 0, Positions);
    glVertexAttribPointer(1, 2, GL_UNSIGNED_BYTE, GL_FALSE, 0, TextureCoordinate);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Graphics::Rect(int X, int Y, int Width, int Height, unsigned char R, unsigned char G, unsigned char B, unsigned char Alpha)
{
    GLshort Positions[] = {
        X, Y + Height,
        X, Y,
        X + Width, Y + Height,
        X + Width, Y
    };

    glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, 0, Positions);
    glUniform1i(Screen->TexturedUniform, 0);
    glUniform4f(Screen->ColorUniform, R / 255.0f, G / 255.0f, B / 255.0f, Alpha / 255.0f);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
