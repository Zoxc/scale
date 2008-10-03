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
}

Category::~Category()
{
}

void Category::Allocate()
{
    Element::Allocate();

    Fill = Graphics::CreateSurface(Width, Height, false);

    SDL_FillRect(Fill, 0, SDL_MapRGB(Fill->format, 0, 0, 0));
}

void Category::Deallocate()
{
    Element::Deallocate();

    SDL_FreeSurface(Fill);
}

void Category::MouseDown(int X, int Y, Element** NewFocus, bool Hovered)
{
    if(Hovered)
    {
        if(Selected)
            Owner->SelectElement(0);
        else
            Owner->SelectElement(this);
    }

    Element::MouseDown(X, Y, NewFocus, Hovered);
}

void Category::Select()
{
    Element::Select();

    TargetAlpha = 150;

    Start();

    Redraw();

    Menu.KillFocus();

    Show->Up();

    if(Hide != 0)
        Hide->Hide();
}

void Category::Deselect()
{
    Element::Deselect();

    TargetAlpha = 0;

    Menu.Focus(Running[0]->button);

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
