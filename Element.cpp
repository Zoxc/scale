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
    AlphaBlend(255),
    Clip(false),
    Animated(false),
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
    for (std::list<Element*>::iterator Child = Children.begin(); Child != Children.end(); Child++)
        (*Child)->Allocate();
}

void Element::Deallocate()
{
    for (std::list<Element*>::iterator Child = Children.begin(); Child != Children.end(); Child++)
        (*Child)->Deallocate();
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

void Element::Animate(int Delta)
{
}

void Element::MouseEnter()
{
}

void Element::MouseUp(int X, int Y)
{
    for (std::list<Element*>::iterator Child = Children.begin(); Child != Children.end(); Child++)
        (*Child)->MouseUp(X - Left, Y - Top);
}

void Element::MouseDown(int X, int Y, Element** NewFocus)
{
    for (std::list<Element*>::iterator Child = Children.begin(); Child != Children.end(); Child++)
        (*Child)->MouseDown(X - Left, Y - Top, NewFocus);

    if(Hovered)
    {
        if(CanFocus)
            *NewFocus = this;

        Click();
    }
}

void Element::Draw(SDL_Surface* Surface, int X, int Y, unsigned char Alpha)
{
}

void Element::_Redraw(Element* Owner)
{
}

void Element::_Start(Element* Owner)
{
}

void Element::_Stop(Element* Owner)
{
}

void Element::Start()
{
    Frame = SDL_GetTicks();
    if(!Animated)
    {
        Animated = true;
        Root->_Start(this);
    }
}

void Element::Stop()
{
    if(Animated)
    {
        Animated = true;
        Root->_Stop(this);
    }
}

void Element::Redraw()
{
    Root->_Redraw(this);
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

        for (std::list<Element*>::iterator Child = Children.begin(); Child != Children.end(); Child++)
            (*Child)->_MouseLeave();
    }
}

void Element::_MouseMove(int X, int Y)
{
    bool Status = Inside(X, Y);

    if(Status)
    {
        for (std::list<Element*>::iterator Child = Children.begin(); Child != Children.end(); Child++)
            (*Child)->_MouseMove(X - Left, Y - Top);
    }
    else if(Hovered)
    {
        for (std::list<Element*>::iterator Child = Children.begin(); Child != Children.end(); Child++)
            (*Child)->_MouseLeave();
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

void Element::_Draw(SDL_Surface* Surface, int X, int Y, unsigned char Alpha)
{
    if(!Visible)
        return;

    X += Left;
    Y += Top;

    if(Clip)
    {
        SDL_Rect OldClip;

        SDL_GetClipRect(Surface, &OldClip);

        SDL_Rect ClipRect;

        ClipRect.x = X;
        ClipRect.y = Y;

        if(Owner->Width - Left < 0)
            ClipRect.w = 0;
        else
            ClipRect.w = Owner->Width - Left;

        if(Owner->Height - Top < 0)
            ClipRect.h = 0;
        else
            ClipRect.h = Owner->Height - Top;

        SDL_SetClipRect(Surface, &ClipRect);

        Draw(Surface, X, Y, Alpha);

        for (std::list<Element*>::iterator Child = Children.begin(); Child != Children.end(); Child++)
            (*Child)->_Draw(Surface, X, Y, (*Child)->AlphaBlend * Alpha / 256);

        SDL_SetClipRect(Surface, &OldClip);
    }
    else
    {
        Draw(Surface, X, Y, Alpha);

        for (std::list<Element*>::iterator Child = Children.begin(); Child != Children.end(); Child++)
            (*Child)->_Draw(Surface, X, Y, (*Child)->AlphaBlend * Alpha / 256);
    }
}
