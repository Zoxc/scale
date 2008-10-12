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

#include "SDL_image.h"

#include "Resources.hpp"
#include "Graphics.hpp"

namespace Resources
{
    TTF_Font* FontSmall = 0;
    TTF_Font* FontNormal = 0;
    TTF_Font* FontBig = 0;

    SDL_Surface* RoundTopLeft = 0;
    SDL_Surface* RoundTopRight = 0;
    SDL_Surface* RoundBottomLeft = 0;
    SDL_Surface* RoundBottomRight = 0;
};

void Resources::Allocate()
{
    FontSmall = TTF_OpenFont("resources/FreeSans.ttf", 19);
    FontNormal = TTF_OpenFont("resources/FreeSans.ttf", 22);
    FontBig = TTF_OpenFont("resources/FreeSans.ttf", 24);

    RoundTopLeft = Graphics::OptimizeSurface(IMG_Load("resources/border_tl.png"), true);
    RoundTopRight = Graphics::OptimizeSurface(IMG_Load("resources/border_tr.png"), true);
    RoundBottomLeft = Graphics::OptimizeSurface(IMG_Load("resources/border_bl.png"), true);
    RoundBottomRight = Graphics::OptimizeSurface(IMG_Load("resources/border_br.png"), true);
}

void Resources::Deallocate()
{
    TTF_CloseFont(FontSmall);
    TTF_CloseFont(FontNormal);
    TTF_CloseFont(FontBig);

    SDL_FreeSurface(RoundTopLeft);
    SDL_FreeSurface(RoundTopRight);
    SDL_FreeSurface(RoundBottomLeft);
    SDL_FreeSurface(RoundBottomRight);
}
