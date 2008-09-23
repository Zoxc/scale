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

#include "Category.hpp"
#include "Graphics.hpp"

Category::Category(Element* AOwner) :
    Element::Element(AOwner),
    Down(false)
{
    CanFocus = true;
    CanSelect = true;
}

Category::~Category()
{
}

void Category::OnSelect()
{
    Redraw();
}

void Category::OnDeselect()
{
    Redraw();
}

void Category::OnMouseEnter()
{
    if(Down)
        Redraw();
}

void Category::OnMouseLeave()
{
    if(Down)
        Redraw();
}

void Category::OnMouseUp(int X, int Y)
{
    if(Down)
    {
        Down = false;

        if(Hovered)
            Redraw();
    }

}

void Category::OnMouseDown(int X, int Y)
{
    if(!Down)
    {
        Down = true;

        if(Hovered)
            Redraw();
    }
}

void Category::OnActivate()
{
    Redraw();
}

void Category::OnDeactivate()
{
    Redraw();
}

void Category::OnDraw(SDL_Surface* Surface, int X, int Y)
{
    if(!Focused && !Selected)
        return;

    SDL_Surface* Fill = SDL_CreateRGBSurface(0, Width, Height, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0);

    SDL_FillRect(Fill, 0, SDL_MapRGB(Fill->format, 0, 0, 0));


    if(Selected && Focused)
        SDL_SetAlpha(Fill, SDL_SRCALPHA, 150);
    else if(Selected)
        SDL_SetAlpha(Fill, SDL_SRCALPHA, 110);
    else if(Focused)
        SDL_SetAlpha(Fill, SDL_SRCALPHA, 80);

    Graphics::ApplySurface(X, Y, Fill, Surface);

    SDL_FreeSurface(Fill);
}
