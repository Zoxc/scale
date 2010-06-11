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
#include <string>

#ifndef NO_FREETYPE
#include "ft2build.h"
#include FT_FREETYPE_H
#endif

namespace Scale
{
    class Font
    {
        public:
            Font(const char* Filename, int APointHeight);
            virtual ~Font();

            struct Buffer
            {
                OpenGL::Texture* bitmap;
                GLuint text;
                size_t chars;
                OpenGL::Buffer *vertex_buffer;
                OpenGL::Buffer *coords_buffer;

                void Print(unsigned int Color, int X, int Y, unsigned char Alpha);
            };

            virtual void Allocate();
            virtual void Deallocate();

            virtual void Print(const char* Text, unsigned int Color, int X, int Y, unsigned char Alpha);
            virtual int Size(const char* Text, int* Height);

            Buffer *AllocBuffer(const char* Text);

            int PointHeight;

        protected:
            struct Glyph
            {
                GLfloat Cords[8];

                int Width;
                int Height;
                int Advance;
                int Top;
            };

            struct FontData
            {
                OpenGL::Texture* Bitmap;

                #ifndef NO_FREETYPE
                FT_Face FontFace;
                #endif

                const char* Filename;

                Glyph Glyphs[256];
            };

            FontData Normal;

            static void Allocate(int PointHeight, FontData* Data);
            static void Measure(int PointHeight, FontData* Data);
            GLshort *BufferQuad(int Position, Glyph* Char, GLshort *buffer, bool first);
            GLfloat *BufferCoords(Glyph* Char, GLfloat *buffer, bool first);

    };

    class AdvancedFont:
        public Font
    {
        public:
            AdvancedFont(const char* FilenameNormal, const char* FilenameBold, int PointHeight);
            virtual ~AdvancedFont();

            virtual void Allocate();
            virtual void Deallocate();

            virtual void Print(const char* Text, unsigned int Color, int X, int Y, unsigned char Alpha);
            virtual int Size(const char* Text, int* Height);

        protected:
            FontData Bold;
    };

};
