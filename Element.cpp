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

#include "Element.hpp"

Element::Element(Element* Owner):
    Left(0),
    Top(0),
    Width(0),
    Height(0),
    Owner(Owner),
    Root(0),
    SelectedElement(0),
    AutoSelect(false),
    CanFocus(false),
    Focused(false),
    Selected(false),
    Visible(true),
    Hovered(false)
{
    memset(Links, 0, sizeof(Links));

    if(Owner != 0)
    {
        Root = Owner->Root;
        Owner->Children.push_back(this);
    }
}

Element::~Element()
{
    /*for(size_t i = 0; i < Children.size(); i++)
    {
        delete Children[i];
    }
*/
    if(Owner != 0)
    {
        // Remove from list
    }
}

void Element::Allocate()
{
    for(size_t i = 0; i < Children.size(); i++ )
        Children[i]->Allocate();
}

void Element::Deallocate()
{
}

void Element::KeyDown(SDLKey Key)
{
    if(Key == SDLK_RETURN)
        Click();
}

void Element::Show()
{
    Visible = true;
}

void Element::Hide()
{
    Visible = false;
}

void Element::Select()
{
    Selected = true;
}

void Element::Deselect()
{
    Selected = false;
}

void Element::Click()
{
    if(AutoSelect)
        Owner->SelectElement(this);
}

void Element::Activate()
{
    Focused = true;
}

void Element::Deactivate()
{
    Focused = false;
}

void Element::MouseLeave()
{
}

void Element::MouseEnter()
{
}

void Element::MouseUp(int X, int Y)
{
    for(size_t i = 0; i < Children.size(); i++)
        Children[i]->MouseUp(X - Left, Y - Top);
}

void Element::MouseDown(int X, int Y, Element** NewFocus)
{
    for(size_t i = 0; i < Children.size(); i++)
        Children[i]->MouseDown(X - Left, Y - Top, NewFocus);

    if(Hovered)
    {
        if(CanFocus)
            *NewFocus = this;

        Click();
    }
}

void Element::Draw(SDL_Surface* Surface, int X, int Y)
{
}

void Element::RedrawElement(Element* Owner)
{
}

void Element::Redraw()
{
    Root->RedrawElement(this);
}

void Element::SelectElement(Element* NewSelection)
{
    if(SelectedElement != 0)
        SelectedElement->Deselect();

    SelectedElement = NewSelection;

    if(SelectedElement != 0)
        SelectedElement->Select();
}

void Element::_MouseLeave()
{
    if(Hovered)
    {
        Hovered = false;

        MouseLeave();

        for(size_t i = 0; i < Children.size(); i++)
            Children[i]->_MouseLeave();
    }
}

void Element::_MouseMove(int X, int Y)
{
    bool Status = Inside(X, Y);

    if(Status)
    {
        for(size_t i = 0; i < Children.size(); i++)
            Children[i]->_MouseMove(X - Left, Y - Top);
    }
    else if(Hovered)
    {
        for(size_t i = 0; i < Children.size(); i++)
            Children[i]->_MouseLeave();
    }

    if(Status != Hovered)
    {
        Hovered = Status;

        if(Hovered)
            MouseEnter();
        else
            MouseLeave();
    }
}

bool Element::Inside(int X, int Y)
{
    if(X < Left)
        return false;

    if(X >= Left + Width)
        return false;

    if(Y < Top)
        return false;

    if(Y >= Top + Height)
        return false;

    return true;
}

void Element::_Draw(SDL_Surface* Surface, int X, int Y)
{
    if(!Visible)
        return;

    X += Left;
    Y += Top;

    Draw(Surface, X, Y);

    for(size_t i = 0; i < Children.size(); i++ )
        Children[i]->_Draw(Surface, X, Y);
}
