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
#include "Button.hpp"
#include "Main.hpp"

extern SDL_Surface* BorderBL;
extern SDL_Surface* BorderBR;
extern SDL_Surface* BorderTL;
extern SDL_Surface* BorderTR;

Category::Category(Element* AOwner) :
    Element::Element(AOwner),
    Alpha(0),
    TargetAlpha(0),
    Hide(0),
    Show(0)
{
    AutoSelect = false;
}

Category::~Category()
{
}

void Category::Allocate()
{
    Element::Allocate();

    Fill = SDL_CreateRGBSurface(0, Width, Height, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0);

    SDL_FillRect(Fill, 0, SDL_MapRGB(Fill->format, 0, 0, 0));
}

void Category::Deallocate()
{
    Element::Deallocate();

    SDL_FreeSurface(Fill);
}

void Category::Click()
{
    if(Selected)
        Owner->SelectElement(0);
    else
        Owner->SelectElement(this);
}

void Category::Select()
{
    Element::Select();

    TargetAlpha = 150;

    Start();

    Redraw();

    Show->Up();

    if(Hide != 0)
        Hide->Hide();
}

void Category::Deselect()
{
    Element::Deselect();

    TargetAlpha = 0;

    Start();

    Show->Down();

    if(Hide != 0)
        Hide->Show();
}

void Category::Animate(int Delta)
{
   if(TargetAlpha != Alpha)
   {
        if(TargetAlpha > Alpha)
        {
            Alpha += Delta;

            if(Alpha > TargetAlpha)
            {
                Alpha = TargetAlpha;
                Stop();
            }
        }
        else
        {
            Alpha -= Delta;

            if(Alpha < TargetAlpha)
            {
                Alpha = TargetAlpha;
                Stop();
            }
        }
        Redraw();
   }
}

void Category::Draw(SDL_Surface* Surface, int X, int Y, unsigned char Alpha)
{
    SDL_SetAlpha(Fill, SDL_SRCALPHA, Category::Alpha);

    Graphics::ApplySurface(X, Y, Fill, Surface);
}
