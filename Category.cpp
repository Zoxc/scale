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
#include "Button.hpp"
#include "Main.hpp"
#include "Graphics.hpp"

Category::Category(Element* AOwner) :
    Element::Element(AOwner),
    TargetAlpha(0),
    Alpha(0),
    Show(0),
    DoFocus(0)
{
}

Category::~Category()
{
}

void Category::Allocate()
{
    Element::Allocate();
}

void Category::Deallocate()
{
    Element::Deallocate();
}

void Category::MouseDown(int X, int Y, bool Hovered)
{
    if(Hovered)
    {
        if(Root->Focused == this)
            Root->KillFocus();
        else
            Root->Focus(this);
    }

    Element::MouseDown(X, Y, Hovered);
}

void Category::Activate()
{
    TargetAlpha = 150;

    Start();

    Redraw();

    if(DoFocus != 0)
        Focus(DoFocus);

    Show->Up();
}

void Category::Deactivate()
{
    TargetAlpha = 0;

    Start();

    Focus(TaskList);

    Show->Down();
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

void Category::Draw(int X, int Y, unsigned char Alpha)
{
    Graphics::Rect(X, Y, Width, Height, 0, 0, 0, Category::Alpha * Alpha >> 8);
}
