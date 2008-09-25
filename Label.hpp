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
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>

#include "Element.hpp"

extern TTF_Font* FontSmall;
extern TTF_Font* FontNormal;
extern TTF_Font* FontBig;

enum FontColor
{
    FontColorBlack, FontColorWhite
};

class Label:
    public Element
{
    public:
        Label(Element* Owner, std::string ACaption, TTF_Font* AFont, FontColor AColor);
        virtual ~Label();

        void Allocate();
        void Deallocate();
        void Draw(SDL_Surface* Surface, int X, int Y);

        TTF_Font* Font;
        FontColor Color;

        /*SDL_Surface* Text;
        SDL_Surface* Shadow;*/
        SDL_Surface* Bitmap;

        std::string Caption;
};
