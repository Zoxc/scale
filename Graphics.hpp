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
#include "SDL_ttf.h"

extern SDL_Color Black;
extern SDL_Color White;

namespace Graphics
{
    SDL_Surface* ConvertSurface(SDL_Surface* source);
    void ApplySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
    SDL_Surface* BlurAlpha(SDL_Surface* source);
    int RenderTextBlack(TTF_Font* font, char* text, int x, int y, SDL_Surface* screen);
    void HalfAlpha(SDL_Surface* surface);
    void ApplyAlpha(int tx, int ty, SDL_Surface* source, SDL_Surface* dest);
};
