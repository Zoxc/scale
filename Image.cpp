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

#include "Image.hpp"
#include "Graphics.hpp"

Image::Image(Element* Owner, char* Path) : Element::Element(Owner)
{
    Filename = Path;

    ImageSurface = IMG_Load(Path);

    Width = ImageSurface->w;
    Height = ImageSurface->h;

    SDL_FreeSurface(ImageSurface);
}

Image::~Image()
{
}

void Image::Allocate()
{
    ImageSurface = IMG_Load(Filename.c_str());
    //ImageSurface = SDL_DisplayFormat(Image);
    //SDL_FreeSurface(Image);
}

void Image::Deallocate()
{
    Element::Deallocate();

    SDL_FreeSurface(ImageSurface);
}

void Image::Draw(SDL_Surface* Surface, int X, int Y)
{
    Element::Draw(Surface, X, Y);

    Graphics::ApplySurface(X, Y, ImageSurface, Surface);
}
