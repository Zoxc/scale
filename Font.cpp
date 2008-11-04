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

#include <algorithm>

#include "Element.hpp"
#include "Font.hpp"
#include "Resources.hpp"

namespace Scale
{
    Font::Font(const char* Filename, int APointHeight):
        PointHeight(APointHeight),
        _Filename(Filename)
    {
        Measure();
    }

    Font::~Font()
    {
    }

    void Font::Size(std::string& Text, int& Width, int& Height)
    {
        Width = 0;
        Height = 0;
/*
        for(unsigned int i = 0; i < Text.length(); i++)
        {
            if(i == Text.length()-1)
                Width += Glyphs[(unsigned char)Text[i]].Width;
            else
                Width += Glyphs[(unsigned char)Text[i]].Advance;

            Height = std::max(Height, Glyphs[(unsigned char)Text[i]].Height);
        }*/
    }

    void Font::Print(std::string& Text, unsigned int Color, int X, int Y, unsigned char Alpha)
    {
     /*   int Position = X;

        glBindTexture(GL_TEXTURE_2D, Bitmap->Handle);
        glUniform1i(Screen->ModeUniform, 2);
        glUniform1i(Screen->TextureUniform, 0);
        glUniform4f(Screen->ColorUniform, reinterpret_cast<unsigned char*>(&Color)[0] / 255.0f, reinterpret_cast<unsigned char*>(&Color)[1] / 255.0f, reinterpret_cast<unsigned char*>(&Color)[2] / 255.0f, Alpha / 255.0f);

        for(unsigned int i = 0; i < Text.length(); i++)
        {
            Glyph* Char = &Glyphs[(unsigned char)Text[i]];

            GLshort Positions[] = {
                Position, Y + Char->Height - Char->Top,
                Position, Y - Char->Top,
                Position + Char->Width, Y + Char->Height - Char->Top,
                Position + Char->Width, Y - Char->Top
            };

            glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, 0, Positions);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, Char->Cords);

            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

            Position += Char->Advance;
        }*/
    }

    void Font::Measure()
    {
     /*   FT_New_Face(Resources::FreeType, _Filename, 0, &FontFace);
        FT_Set_Char_Size(FontFace, 0, PointHeight * 64, 96, 96);

        PixelHeight = FontFace->height >> 6;

        FT_Error Error;

        for(int i = 0; i <= 255; i++)
        {
            Error = FT_Load_Glyph(FontFace, FT_Get_Char_Index(FontFace, (unsigned char)i), FT_LOAD_DEFAULT);

            if(Error)
            {
                Glyphs[i].Width = 0;
                Glyphs[i].Height = 0;
                Glyphs[i].Advance = 0;

                continue;
            }

            Glyphs[i].Width = FontFace->glyph->metrics.width >> 6;
            Glyphs[i].Height = FontFace->glyph->metrics.height >> 6;
            Glyphs[i].Advance = FontFace->glyph->advance.x >> 6;
        }*/
    }

    void Font::Allocate()
    {
       /* if(FontFace == 0)
        {
            FT_New_Face(Resources::FreeType, _Filename, 0, &FontFace);
            FT_Set_Char_Size(FontFace, 0, PointHeight * 64, 96, 96);

            PixelHeight = FontFace->height >> 6;
        }

        FT_Error Error;

        Bitmap = new OpenGL::Texture();

        Bitmap->Width = 0;
        Bitmap->Height = 0;

        for(int i = 0; i <= 255; i++)
        {
            Error = FT_Load_Glyph(FontFace, FT_Get_Char_Index(FontFace, (unsigned char)i), FT_LOAD_DEFAULT);

            if(Error)
                continue;

            Glyphs[i].Width = Bitmap->Width;

            Bitmap->Width += (FontFace->glyph->metrics.width >> 6) + 1;
            Bitmap->Height = std::max( Bitmap->Height, int(FontFace->glyph->metrics.height >> 6));

            Glyphs[i].Advance = FontFace->glyph->advance.x >> 6;
        }

        glBindTexture(GL_TEXTURE_2D, Bitmap->Handle);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Bitmap->Width, Bitmap->Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        for(int i = 0; i <= 255; i++)
        {
            Error = FT_Load_Glyph(FontFace, FT_Get_Char_Index(FontFace, (unsigned char)i), FT_LOAD_DEFAULT);

            if(Error)
                return;

            Error = FT_Render_Glyph(FontFace->glyph, FT_RENDER_MODE_NORMAL);

            if(Error)
                return;

            unsigned int* Data = new unsigned int[FontFace->glyph->bitmap.width * FontFace->glyph->bitmap.rows];

            unsigned int* Pixel = Data;
            unsigned int* PixelEnd = Data + FontFace->glyph->bitmap.rows * FontFace->glyph->bitmap.width;

            unsigned char* Buffer = FontFace->glyph->bitmap.buffer;

            while(Pixel != PixelEnd)
            {
                *Pixel = 0;
                reinterpret_cast<unsigned char*>(Pixel++)[3] = *Buffer++;
            }

            glTexSubImage2D(GL_TEXTURE_2D, 0, Glyphs[i].Width, 0, FontFace->glyph->bitmap.width, FontFace->glyph->bitmap.rows, GL_RGBA, GL_UNSIGNED_BYTE, Data);

            delete[] Data;

            Glyphs[i].Cords[0] = (float)Glyphs[i].Width / (float)Bitmap->Width; // X
            Glyphs[i].Cords[1] = (float)FontFace->glyph->bitmap.rows / (float)Bitmap->Height; // Height
            Glyphs[i].Cords[2] = Glyphs[i].Cords[0];
            Glyphs[i].Cords[3] = 0;
            Glyphs[i].Cords[4] = ((float)Glyphs[i].Width + (float)FontFace->glyph->bitmap.width) / (float)Bitmap->Width; // X + Width
            Glyphs[i].Cords[5] = Glyphs[i].Cords[1];
            Glyphs[i].Cords[6] = Glyphs[i].Cords[4];
            Glyphs[i].Cords[7] = 0;

            Glyphs[i].Width = FontFace->glyph->bitmap.width;
            Glyphs[i].Height = FontFace->glyph->bitmap.rows;
            Glyphs[i].Top = FontFace->glyph->bitmap_top - (FontFace->height >> 6);
        }

        FT_Done_Face(FontFace);

        FontFace = 0;*/
    }

    void Font::Deallocate()
    {
        //delete Bitmap;
    }
};