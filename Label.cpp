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

#include "Label.hpp"

void Label::FontSize(FT_Face Font, std::string Text, int* Width, int* Height)
{
    FT_Error Error;

    for (unsigned int i = 0; i < Text.length(); i++)
    {
        Error = FT_Load_Glyph(Font, FT_Get_Char_Index(Font,  Text[i]), FT_LOAD_DEFAULT);
        if(Error)
            continue;

        *Width += Font->glyph->advance.x >> 6;
    }

    *Height = Font->height >> 6;
}

void Label::DrawFont(FT_Face Font, unsigned int Color, std::string Text, int X, int Y, unsigned char Alpha)
{
    if(Y > Screen->Height)
        return;

    FT_Error Error;

    int Position = X;

    Y += Font->height >> 6;

    if(Y < 0)
        return;

    for (unsigned int i = 0; i < Text.length(); i++)
    {
        Error = FT_Load_Glyph(Font, FT_Get_Char_Index(Font,  Text[i]), FT_LOAD_DEFAULT );
        if(Error)
            continue;

        if(X + Font->glyph->advance.x < 0)
            continue;

        if(X > Screen->Width)
            return;

        Error = FT_Render_Glyph(Font->glyph, FT_RENDER_MODE_NORMAL);
        if(Error)
            continue;

        int Width = Font->glyph->bitmap.width;

        unsigned int* Data = new unsigned int[Width * Font->glyph->bitmap.rows];

        unsigned int* Pixel = Data;
        unsigned int* PixelEnd = Data + Font->glyph->bitmap.rows * Width;

        unsigned char* Buffer = Font->glyph->bitmap.buffer;

        while(Pixel != PixelEnd)
        {
            *Pixel = Color;
            reinterpret_cast<unsigned char*>(Pixel++)[3] = *Buffer++;
        }

        OpenGL::Texture Glyph;

        glBindTexture(GL_TEXTURE_2D, Glyph.Handle);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Font->glyph->bitmap.width, Font->glyph->bitmap.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);

        delete[] Data;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        GLshort Positions[] = {
            Position, Y - Font->glyph->bitmap_top + Font->glyph->bitmap.rows,
            Position, Y - Font->glyph->bitmap_top,
            Position + Font->glyph->bitmap.width, Y - Font->glyph->bitmap_top + Font->glyph->bitmap.rows,
            Position + Font->glyph->bitmap.width, Y - Font->glyph->bitmap_top
        };

        glUniform4f(Screen->ColorUniform, 0, 0, 0, Alpha / 255.0f);
        glUniform1i(Screen->TexturedUniform, 1);
        glUniform1i(Screen->TextureUniform, 0);

        glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, 0, Positions);
        glVertexAttribPointer(1, 2, GL_UNSIGNED_BYTE, GL_FALSE, 0, TextureCoordinate);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        Position += Font->glyph->advance.x >> 6;
    }
}
/*
VGImage Label::CreateFont(FT_Face Font, unsigned int Color, std::string Text)
{

    if(Color == FontColorBlack)
    {
        SDL_Surface* Shadow = TTF_RenderText_Blended(Font, (char*)Text.c_str(), White);

        SDL_Surface* TextMain = TTF_RenderText_Blended(Font, (char*)Text.c_str(), Black);

        Graphics::HalfAlpha(Shadow, 1);

        SDL_Surface* Bitmap = Graphics::CreateSurface(TextMain->w, TextMain->h + 1, true);

        Graphics::ApplySurfaceEx(0, 1, Shadow, Bitmap);
        Graphics::ApplySurfaceEx(0, 0, TextMain, Bitmap);

        SDL_FreeSurface(Shadow);
        SDL_FreeSurface(TextMain);

        return Bitmap;
    }
    else
    {
        // Create shadow
        SDL_Surface* TextMain = TTF_RenderText_Blended(Font, (char*)Text.c_str(), Black);
        SDL_Surface* Shadow = Graphics::BlurAlpha(TextMain);
        SDL_FreeSurface(TextMain);

        TextMain = TTF_RenderText_Blended(Font, (char*)Text.c_str(), White);

        SDL_Surface* Bitmap = Graphics::CreateSurface(TextMain->w + 4, TextMain->h + 3, true);

        Graphics::ApplySurfaceEx(0, 0, Shadow, Bitmap);
        Graphics::ApplySurfaceEx(2, 1, TextMain, Bitmap);

        SDL_FreeSurface(Shadow);
        SDL_FreeSurface(TextMain);

        return Bitmap;
    }
    return 0;
}
*/
Label::Label(Element* Owner, std::string ACaption, FT_Face AFont, unsigned int AColor) :
    Element::Element(Owner),
    Font(AFont),
    Color(AColor)//,
   // Bitmap(0)
{
    Caption = ACaption;

    FontSize(Font, Caption, &Width, &Height);
}

Label::~Label()
{

}

void Label::SetCaption(std::string NewCaption)
{
    if(Caption != NewCaption /*&& Bitmap != 0*/)
    {
       Caption = NewCaption;

       //SDL_FreeSurface(Bitmap);

       //Bitmap = CreateFont(Font, Color, Caption);
    }
    else
        Caption = NewCaption;
}

void Label::Allocate()
{
    Element::Allocate();

    //Bitmap = CreateFont(Font, Color, Caption);
}

void Label::Deallocate()
{
    Element::Deallocate();
}

void Label::Draw(int X, int Y, unsigned char Alpha)
{
    DrawFont(Font, Color, Caption, X, Y, Alpha);
   /* if(Color == FontColorBlack)
        Graphics::ApplyAlpha(X, Y + 1, Bitmap, Surface, Alpha);
    else
        Graphics::ApplyAlpha(X - 2, Y - 1, Bitmap, Surface, Alpha);*/

}
