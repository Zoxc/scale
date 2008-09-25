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
        Shadow = TTF_RenderText_Blended(Font, (char*)Caption.c_str(), White);

        Text = TTF_RenderText_Blended(Font, (char*)Caption.c_str(), Black);

        Graphics::HalfAlpha(Shadow);

        //Bitmap = SDL_CreateRGBSurface(SDL_SRCALPHA, Text->w + 10, Text->h + 10, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);

        //Graphics::ApplyAlphaSurface(0, 1, Shadow, Bitmap);
        //Graphics::ApplyAlphaSurface(0, 0, Text, Bitmap);

        //SDL_FreeSurface(Shadow);
        //SDL_FreeSurface(Text);
    }
    else
    {
        // Create shadow
        Text = TTF_RenderText_Blended(Font, (char*)Caption.c_str(), Black);
        Shadow = Graphics::BlurAlpha(Text);
        SDL_FreeSurface(Text);

        Text = TTF_RenderText_Blended(Font, (char*)Caption.c_str(), White);

        //Bitmap = SDL_CreateRGBSurface(SDL_SRCALPHA, Text->w + 40, Text->h + 20, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);

        //Graphics::ApplyAlphaSurface(0, 0, Shadow, Bitmap);
        //Graphics::ApplyAlphaSurface(2, 1, Text, Bitmap);

        //SDL_FreeSurface(Shadow);
        //SDL_FreeSurface(Text);
    }
}

void Label::Deallocate()
{
    Element::Deallocate();

    SDL_FreeSurface(Text);
    SDL_FreeSurface(Shadow);
    //SDL_FreeSurface(Bitmap);
}

void Label::Draw(SDL_Surface* Surface, int X, int Y)
{
    Element::Draw(Surface, X, Y);

    if(Color == FontColorBlack)
    {
        Graphics::ApplySurface(X, Y + 1, Shadow, Surface);
        Graphics::ApplySurface(X, Y, Text, Surface);
    }
    else
    {
        Graphics::ApplySurface(X - 2, Y - 1, Shadow, Surface);
        Graphics::ApplySurface(X, Y, Text, Surface);
    }
}
