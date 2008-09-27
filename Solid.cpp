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

#include "Solid.hpp"
#include "Graphics.hpp"

Solid::Solid(Element* AOwner) :
    Element::Element(AOwner),
    R(0),
    G(0),
    B(0)
{
}

Solid::~Solid()
{
}

void Solid::Allocate()
{
    Element::Allocate();

    Fill = Graphics::CreateSurface(Width, Height, false);

    SDL_FillRect(Fill, 0, SDL_MapRGB(Fill->format, R, G, B));
}

void Solid::Deallocate()
{
    Element::Deallocate();

    SDL_FreeSurface(Fill);
}

void Solid::Draw(SDL_Surface* Surface, int X, int Y, unsigned char Alpha)
{
    SDL_SetAlpha(Fill, SDL_SRCALPHA, Alpha);

    Graphics::ApplySurface(X, Y, Fill, Surface);
}
