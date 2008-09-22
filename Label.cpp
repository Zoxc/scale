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

Label::Label(Element* AOwner, std::string ACaption, TTF_Font* AFont, FontColor AColor) :
    Element::Element(AOwner),
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

void Label::OnDraw(SDL_Surface* Surface, int X, int Y)
{
    if(Color == FontColorBlack)
    {
        Graphics::RenderTextBlack(Font, (char*)Caption.c_str(), X, Y, Surface);
    }
    else
    {
        SDL_Surface* Text = TTF_RenderText_Blended(Font, (char*)Caption.c_str(), Black);

        // Blit black blur
        SDL_Surface* Blur = Graphics::BlurAlpha(Text);

        SDL_FreeSurface(Text);

        Graphics::ApplySurface(X - 2, Y - 1, Blur, Surface);

        SDL_FreeSurface(Blur);

        // Blit the real thing
        Text = TTF_RenderText_Blended(Font, (char*)Caption.c_str(), White);

        Graphics::ApplySurface(X, Y, Text, Surface);

        SDL_FreeSurface(Text);
    }

}
