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

#include "Graphics.hpp"
#include "Element.hpp"
#include "Resources.hpp"

namespace Scale
{
    namespace Graphics
    {
        void Texture(OpenGL::Texture* Tex, int X, int Y, unsigned char Alpha)
        {
            if(Alpha == 0)
                return;

            GLshort Positions[] = {
                X, Y + Tex->Height,
                X, Y,
                X + Tex->Width, Y + Tex->Height,
                X + Tex->Width, Y
            };

            glBindTexture(GL_TEXTURE_2D, Tex->Handle);
            Screen->ChangeMode(1);
            glUniform1i(Screen->TextureUniforms[1], 0);
            glUniform4f(Screen->ColorUniforms[1], 0, 0, 0, Alpha / 255.0f);

            glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, 0, Positions);
            glVertexAttribPointer(1, 2, GL_UNSIGNED_BYTE, GL_FALSE, 0, TextureCoordinate);

            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            DrawCalls++;
        }

        void AlphaTexture(OpenGL::Texture* Tex, int X, int Y, unsigned char R, unsigned char G, unsigned char B, unsigned char Alpha)
        {
            if(Alpha == 0)
                return;

            GLshort Positions[] = {
                X, Y + Tex->Height,
                X, Y,
                X + Tex->Width, Y + Tex->Height,
                X + Tex->Width, Y
            };

            glBindTexture(GL_TEXTURE_2D, Tex->Handle);
            Screen->ChangeMode(2);
            glUniform1i(Screen->TextureUniforms[2], 0);
            glUniform4f(Screen->ColorUniforms[2], R / 255.0f, G / 255.0f, B / 255.0f, Alpha / 255.0f);

            glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, 0, Positions);
            glVertexAttribPointer(1, 2, GL_UNSIGNED_BYTE, GL_FALSE, 0, TextureCoordinate);

            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            DrawCalls++;
        }

        void Rect(int X, int Y, int Width, int Height, unsigned char R, unsigned char G, unsigned char B, unsigned char Alpha)
        {
            if(Alpha == 0)
                return;

            GLshort Positions[] = {
                X, Y + Height,
                X, Y,
                X + Width, Y + Height,
                X + Width, Y
            };

            glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, 0, Positions);
            Screen->ChangeMode(0);
            glUniform4f(Screen->ColorUniforms[0], R / 255.0f, G / 255.0f, B / 255.0f, Alpha / 255.0f);

            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            DrawCalls++;
        }

        void RoundRect(int X, int Y, int Width, int Height, unsigned char R, unsigned char G, unsigned char B, unsigned char Alpha)
        {
            if(Alpha == 0)
                return;

            const int RoundSize = 10;

            AlphaTexture(Resources::RoundCornerTopLeft, X, Y, R, G, B, Alpha);
            AlphaTexture(Resources::RoundCornerTopRight, X + Width - RoundSize, Y, R, G, B, Alpha);
            AlphaTexture(Resources::RoundCornerBottomLeft, X, Y + Height - RoundSize, R, G, B, Alpha);
            AlphaTexture(Resources::RoundCornerBottomRight, X + Width - RoundSize, Y + Height - RoundSize, R, G, B, Alpha);

            Rect(X, Y + RoundSize, Width, Height - RoundSize - RoundSize, R, G, B, Alpha);
            Rect(X + RoundSize, Y, Width - RoundSize - RoundSize, RoundSize, R, G, B, Alpha);
            Rect(X + RoundSize, Y + Height - RoundSize, Width - RoundSize - RoundSize, RoundSize, R, G, B, Alpha);
        }
    };
};
