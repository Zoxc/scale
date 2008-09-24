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

Solid::Solid(Element* AOwner) : Element::Element(AOwner)
{
}

Solid::~Solid()
{
}

void Solid::Draw(SDL_Surface* Surface, int X, int Y)
{
    Element::Draw(Surface, X, Y);

    SDL_Surface* Fill = SDL_CreateRGBSurface(0, Width, Height, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);

    SDL_FillRect(Fill, 0, SDL_MapRGB(Fill->format, 0, 0,0));

    Graphics::HalfAlpha(Fill);

    Graphics::ApplySurface(X, Y, Fill, Surface);

    SDL_FreeSurface(Fill);
}
