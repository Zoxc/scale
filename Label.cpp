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

TTF_Font* FontSmall = NULL;
TTF_Font* FontNormal = NULL;
TTF_Font* FontBig = NULL;

Label::Label(Element* Owner, std::string ACaption, TTF_Font* AFont, FontColor AColor) :
    Element::Element(Owner),
    Font(AFont),
    Color(AColor)
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

void Label::Allocate()
{
    Element::Allocate();

    if(Color == FontColorBlack)
    {
        SDL_Surface* Shadow = TTF_RenderText_Blended(Font, (char*)Caption.c_str(), White);

        SDL_Surface* Text = TTF_RenderText_Blended(Font, (char*)Caption.c_str(), Black);

        Graphics::HalfAlpha(Shadow);

        Bitmap = Graphics::CreateSurface(Text->w, Text->h + 1, true);

        Graphics::ApplySurfaceEx(0, 1, Shadow, Bitmap);
        Graphics::ApplySurfaceEx(0, 0, Text, Bitmap);

        SDL_FreeSurface(Shadow);
        SDL_FreeSurface(Text);
    }
    else
    {
        // Create shadow
        SDL_Surface* Text = TTF_RenderText_Blended(Font, (char*)Caption.c_str(), Black);
        SDL_Surface* Shadow = Graphics::BlurAlpha(Text);
        SDL_FreeSurface(Text);

        Text = TTF_RenderText_Blended(Font, (char*)Caption.c_str(), White);

        Bitmap = Graphics::CreateSurface(Text->w + 4, Text->h + 3, true);

        Graphics::ApplySurfaceEx(0, 0, Shadow, Bitmap);
        Graphics::ApplySurfaceEx(2, 1, Text, Bitmap);

        SDL_FreeSurface(Shadow);
        SDL_FreeSurface(Text);
    }
}

void Label::Deallocate()
{
    Element::Deallocate();

    //SDL_FreeSurface(Text);
    //SDL_FreeSurface(Shadow);
    SDL_FreeSurface(Bitmap);
}

void Label::Draw(SDL_Surface* Surface, int X, int Y, unsigned char Alpha)
{
    if(Color == FontColorBlack)
        Graphics::ApplyAlpha(X, Y + 1, Bitmap, Surface, Alpha);
    else
        Graphics::ApplyAlpha(X - 2, Y - 1, Bitmap, Surface, Alpha);

}
