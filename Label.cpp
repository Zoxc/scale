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
#include "Graphics.hpp"

SDL_Surface* Label::CreateFont(TTF_Font* Font, FontColor Color, std::string Text)
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
}

Label::Label(Element* Owner, std::string ACaption, TTF_Font* AFont, FontColor AColor) :
    Element::Element(Owner),
    Font(AFont),
    Color(AColor),
    Bitmap(0)
{
    Caption = ACaption;

    SDL_Surface* Text = TTF_RenderText_Blended(Font, Caption.c_str(), White);

    Width = Text->w;
    Height = Text->h + 1;

    SDL_FreeSurface(Text);
}

Label::~Label()
{

}

void Label::SetCaption(std::string NewCaption)
{
    if(Caption != NewCaption && Bitmap != 0)
    {
       Caption = NewCaption;

       SDL_FreeSurface(Bitmap);

       Bitmap = CreateFont(Font, Color, Caption);
    }
    else
        Caption = NewCaption;
}

void Label::Allocate()
{
    Element::Allocate();

    Bitmap = CreateFont(Font, Color, Caption);
}

void Label::Deallocate()
{
    Element::Deallocate();

    SDL_FreeSurface(Bitmap);

    Bitmap = 0;
}

void Label::Draw(SDL_Surface* Surface, int X, int Y, unsigned char Alpha)
{
    if(Color == FontColorBlack)
        Graphics::ApplyAlpha(X, Y + 1, Bitmap, Surface, Alpha);
    else
        Graphics::ApplyAlpha(X - 2, Y - 1, Bitmap, Surface, Alpha);

}
