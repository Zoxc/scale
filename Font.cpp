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

#include "Element.hpp"
#include <algorithm>
#include "Font.hpp"
#include "Resources.hpp"

namespace Scale
{
    void Font::Allocate(int PointHeight, FontData* Data)
    {
        #ifndef NO_FREETYPE
        if(Data->FontFace == 0)
        {
            FT_New_Face(Resources::FreeType, Data->Filename, 0, &Data->FontFace);
            FT_Set_Char_Size(Data->FontFace, 0, PointHeight * 64, 96, 96);
        }

        FT_Error Error;

        Data->Bitmap = new OpenGL::Texture();

        Data->Bitmap->Width = 0;
        Data->Bitmap->Height = 0;

        for(int i = 0; i <= 255; i++)
        {
            Error = FT_Load_Glyph(Data->FontFace, FT_Get_Char_Index(Data->FontFace, (unsigned char)i), FT_LOAD_DEFAULT);

            if(Error)
                assert(0);

            Data->Glyphs[i].Width = Data->Bitmap->Width;

            Data->Bitmap->Width += (Data->FontFace->glyph->metrics.width >> 6) + 1;
            Data->Bitmap->Height = std::max(Data->Bitmap->Height, int(Data->FontFace->glyph->metrics.height >> 6));

            Data->Glyphs[i].Advance = Data->FontFace->glyph->advance.x >> 6;
        }

        glBindTexture(GL_TEXTURE_2D, Data->Bitmap->Handle);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Data->Bitmap->Width, Data->Bitmap->Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        for(int i = 0; i <= 255; i++)
        {
            Error = FT_Load_Glyph(Data->FontFace, FT_Get_Char_Index(Data->FontFace, (unsigned char)i), FT_LOAD_DEFAULT);

            if(Error)
                assert(0);

            Error = FT_Render_Glyph(Data->FontFace->glyph, FT_RENDER_MODE_NORMAL);

            if(Error)
               assert(0);

            #ifdef NO_GL_ALPHA
                unsigned int* PixelData = new unsigned int[Data->FontFace->glyph->bitmap.width * Data->FontFace->glyph->bitmap.rows];

                unsigned int* Pixel = PixelData;
                unsigned int* PixelEnd = PixelData + Data->FontFace->glyph->bitmap.rows * Data->FontFace->glyph->bitmap.width;

                unsigned char* Buffer = Data->FontFace->glyph->bitmap.buffer;

                while(Pixel != PixelEnd)
                {
                    *Pixel = 0;
                    reinterpret_cast<unsigned char*>(Pixel++)[3] = *Buffer++;
                }

                glTexSubImage2D(GL_TEXTURE_2D, 0, Data->Glyphs[i].Width, 0, Data->FontFace->glyph->bitmap.width, Data->FontFace->glyph->bitmap.rows, GL_RGBA, GL_UNSIGNED_BYTE, PixelData);

                delete[] PixelData;
            #else
                glTexSubImage2D(GL_TEXTURE_2D, 0, Data->Glyphs[i].Width, 0, Data->FontFace->glyph->bitmap.width, Data->FontFace->glyph->bitmap.rows, GL_ALPHA, GL_UNSIGNED_BYTE, Data->FontFace->glyph->bitmap.buffer);
            #endif

            Data->Glyphs[i].Cords[0] = (float)Data->Glyphs[i].Width / (float)Data->Bitmap->Width; // X
            Data->Glyphs[i].Cords[1] = (float)Data->FontFace->glyph->bitmap.rows / (float)Data->Bitmap->Height; // Height
            Data->Glyphs[i].Cords[2] = Data->Glyphs[i].Cords[0];
            Data->Glyphs[i].Cords[3] = 0;
            Data->Glyphs[i].Cords[4] = ((float)Data->Glyphs[i].Width + (float)Data->FontFace->glyph->bitmap.width) / (float)Data->Bitmap->Width; // X + Width
            Data->Glyphs[i].Cords[5] = Data->Glyphs[i].Cords[1];
            Data->Glyphs[i].Cords[6] = Data->Glyphs[i].Cords[4];
            Data->Glyphs[i].Cords[7] = 0;

            Data->Glyphs[i].Width = Data->FontFace->glyph->bitmap.width;
            Data->Glyphs[i].Height = Data->FontFace->glyph->bitmap.rows;
            Data->Glyphs[i].Top = Data->FontFace->glyph->bitmap_top - (Data->FontFace->height >> 6);
        }

        FT_Done_Face(Data->FontFace);

        Data->FontFace = 0;
        #endif
    }

    void Font::Measure(int PointHeight, FontData* Data)
    {
        #ifndef NO_FREETYPE
        FT_New_Face(Resources::FreeType, Data->Filename, 0, &Data->FontFace);
        FT_Set_Char_Size(Data->FontFace, 0, PointHeight * 64, 96, 96);

        FT_Error Error;

        for(int i = 0; i <= 255; i++)
        {
            Error = FT_Load_Glyph(Data->FontFace, FT_Get_Char_Index(Data->FontFace, (unsigned char)i), FT_LOAD_DEFAULT);

            if(Error)
            {
                Data->Glyphs[i].Width = 0;
                Data->Glyphs[i].Height = 0;
                Data->Glyphs[i].Advance = 0;

                continue;
            }

            Data->Glyphs[i].Width = Data->FontFace->glyph->metrics.width >> 6;
            Data->Glyphs[i].Height = Data->FontFace->glyph->metrics.height >> 6;

            Data->Glyphs[i].Advance = Data->FontFace->glyph->advance.x >> 6;
        }
        #endif
    }

    Font::Font(const char* Filename, int APointHeight):
        PointHeight(APointHeight)
    {
        Normal.Filename = Filename;
        Measure(PointHeight, &Normal);
    }

    void Font::Allocate()
    {
        Allocate(PointHeight, &Normal);
    }

    void Font::Deallocate()
    {
        #ifndef NO_FREETYPE
        delete Normal.Bitmap;
        #endif
    }

    Font::~Font()
    {
    }

    int Font::Size(const char* Text, int* Height)
    {
        int Width = 0;
        int _Height = 0;

        #ifndef NO_FREETYPE
        while(*Text != 0)
        {
            if(Text[1] == 0)
                Width += Normal.Glyphs[(unsigned char)*Text].Width;
            else
                Width += Normal.Glyphs[(unsigned char)*Text].Advance;

            _Height = std::max(_Height, Normal.Glyphs[(unsigned char)*Text].Height);

            Text++;
        }
        #endif

        if(Height != 0)
            *Height = _Height;

        return Width;
    }

    void Font::Print(const char* Text, unsigned int Color, int X, int Y, unsigned char Alpha)
    {
        #ifndef NO_FREETYPE
        int Position = X;

        glBindTexture(GL_TEXTURE_2D, Normal.Bitmap->Handle);
        glUniform1i(Screen->ModeUniform, 2);
        glUniform1i(Screen->TextureUniform, 0);
        glUniform4f(Screen->ColorUniform, reinterpret_cast<unsigned char*>(&Color)[0] / 255.0f, reinterpret_cast<unsigned char*>(&Color)[1] / 255.0f, reinterpret_cast<unsigned char*>(&Color)[2] / 255.0f, Alpha / 255.0f);

        while(*Text != 0)
        {
            Glyph* Char = &Normal.Glyphs[(unsigned char)*Text];

            if((unsigned char)*Text > 32)
            {
                GLshort Positions[] = {
                    Position, Y + Char->Height - Char->Top,
                    Position, Y - Char->Top,
                    Position + Char->Width, Y + Char->Height - Char->Top,
                    Position + Char->Width, Y - Char->Top
                };

                glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, 0, Positions);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, Char->Cords);

                glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            }

            Position += Char->Advance;

            Text++;
        }
        #endif
    }

    AdvancedFont::AdvancedFont(const char* FilenameNormal, const char* FilenameBold, int APointHeight):
        Font(FilenameNormal, APointHeight)
    {
        Bold.Filename = FilenameBold;
        Measure(PointHeight, &Bold);
    }

    void AdvancedFont::Allocate()
    {
        Font::Allocate();

        Font::Allocate(PointHeight, &Bold);
    }

    void AdvancedFont::Deallocate()
    {
        Font::Deallocate();

        #ifndef NO_FREETYPE
        delete Bold.Bitmap;
        #endif
    }

    void AdvancedFont::Print(const char* Text, unsigned int Color, int X, int Y, unsigned char Alpha)
    {
        #ifndef NO_FREETYPE
        int Position = X;

        FontData* Data = &Normal;

        glBindTexture(GL_TEXTURE_2D, Data->Bitmap->Handle);

        glUniform1i(Screen->ModeUniform, 2);
        glUniform1i(Screen->TextureUniform, 0);
        glUniform4f(Screen->ColorUniform, reinterpret_cast<unsigned char*>(&Color)[0] / 255.0f, reinterpret_cast<unsigned char*>(&Color)[1] / 255.0f, reinterpret_cast<unsigned char*>(&Color)[2] / 255.0f, Alpha / 255.0f);

        while(*Text != 0)
        {
            switch((unsigned char)*Text)
            {
                case 11:
                    if(Data == &Normal)
                        Data = &Bold;
                    else
                        Data = &Normal;

                    glBindTexture(GL_TEXTURE_2D, Data->Bitmap->Handle);

                    break;

                default:
                    Glyph* Char = &Data->Glyphs[(unsigned char)*Text];

                    if((unsigned char)*Text > 32)
                    {
                        GLshort Positions[] = {
                            Position, Y + Char->Height - Char->Top,
                            Position, Y - Char->Top,
                            Position + Char->Width, Y + Char->Height - Char->Top,
                            Position + Char->Width, Y - Char->Top
                        };

                        glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, 0, Positions);
                        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, Char->Cords);

                        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
                    }

                    Position += Char->Advance;
            }
            Text++;
        }
        #endif
    }

    int AdvancedFont::Size(const char* Text, int* Height)
    {
        int Width = 0;
        int _Height = 0;

        FontData* Data = &Normal;

        #ifndef NO_FREETYPE
        while(*Text != 0)
        {
            switch((unsigned char)*Text)
            {
                case 11:
                    if(Data == &Normal)
                        Data = &Bold;
                    else
                        Data = &Normal;
                    break;

                default:
                    if(Text[1] == 0)
                        Width += Data->Glyphs[(unsigned char)*Text].Width;
                    else
                        Width += Data->Glyphs[(unsigned char)*Text].Advance;

                    _Height = std::max(_Height, Data->Glyphs[(unsigned char)*Text].Height);
            }

            Text++;
        }
        #endif

        if(Height != 0)
            *Height = _Height;

        return Width;
    }

    AdvancedFont::~AdvancedFont()
    {
    }

};
