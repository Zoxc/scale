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

Image::Image(Element* Owner, std::string Path):
    Element::Element(Owner),
    NeedAlpha(true)
{
    Filename = Path;

    ImageSurface = IMG_Load(Path.c_str());

    if(ImageSurface == 0)
        return;

    Width = ImageSurface->w;
    Height = ImageSurface->h;

    SDL_FreeSurface(ImageSurface);
}

Image::~Image()
{
}

void Image::Allocate()
{
    ImageSurface = Graphics::OptimizeSurface(IMG_Load(Filename.c_str()), NeedAlpha);
}

void Image::Deallocate()
{
    Element::Deallocate();

    SDL_FreeSurface(ImageSurface);
}

void Image::Draw(SDL_Surface* Surface, int X, int Y, unsigned char Alpha)
{
    if(ImageSurface != 0)
        Graphics::ApplyAlpha(X, Y, ImageSurface, Surface, Alpha);
}
