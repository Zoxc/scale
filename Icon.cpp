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

#include "Icon.hpp"
#include "Resources.hpp"
#include "Graphics.hpp"

Icon::Icon(Element* Owner) :
    Button(Owner),
    Down(false),
    Focused(false)
{
}

Icon::~Icon()
{
}

void Icon::Click()
{
}

void Icon::MouseEnter()
{
    if(Down)
        Redraw();
}

void Icon::MouseLeave()
{
    if(Down)
        Redraw();
}

void Icon::MouseUp(int X, int Y, bool Hovered)
{
    if(Down)
    {
        Down = false;

        if(Element::Hovered)
            Redraw();
    }

    Button::MouseUp(X, Y, Hovered);
}

void Icon::MouseDown(int X, int Y, bool Hovered)
{
    if(Hovered)
        if(!Down)
        {
            Down = true;
            Redraw();
        }

    Button::MouseDown(X, Y, Hovered);
}

void Icon::Activate()
{
    Focused = true;

    Redraw();
}

void Icon::Deactivate()
{
    Focused = false;

    Redraw();
}

void Icon::Draw(int X, int Y, unsigned char Alpha)
{
    if(!Focused)
        return;

    if(Down && Hovered)
        Graphics::RoundRect(X, Y, Width, Height, 255, 255, 255, Alpha / 6);
    else
        Graphics::RoundRect(X, Y, Width, Height, 255, 255, 255, Alpha / 4);
}
