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

#include "Button.hpp"
#include "Graphics.hpp"

Button::Button(Element* Owner) : Element::Element(Owner)
{
}

Button::~Button()
{
}

void Button::KeyDown(ElementKey Key)
{
    if(Key == ElementGo)
        Click();
}

void Button::MouseUp(int X, int Y, bool Hovered)
{
    if(Hovered/* && Root->Trapped == this*/)
        Click();

    //Release();

    Element::MouseUp(X, Y, Hovered);
}

void Button::MouseDown(int X, int Y, bool Hovered)
{
    if(Hovered)
        Root->Focus(this);

    Element::MouseDown(X, Y, Hovered);
}
