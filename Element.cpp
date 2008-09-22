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

Element::Element(Element* AOwner):
    EventClick(0),
    Left(0),
    Top(0),
    Width(0),
    Height(0),
    CanFocus(false),
    Visible(true),
    Hovered(false),
    TargetDown(0),
    Owner(AOwner)
{
    if(Owner != 0)
    {
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

void Element::OnClick()
{
    if(EventClick != 0)
        EventClick(this);
}

void Element::OnActivate(bool* Redraw)
{
}

void Element::OnDeactivate(bool* Redraw)
{
}

void Element::OnMouseLeave(bool* Redraw)
{
}

void Element::OnMouseEnter(bool* Redraw)
{
}

void Element::OnMouseUp(int X, int Y, bool* Redraw)
{
}

void Element::OnMouseDown(int X, int Y, bool* Redraw)
{
}

void Element::MouseLeave(bool* Redraw)
{
    if(Hovered)
    {
        Hovered = false;

        TargetDown = false;

        OnMouseLeave(Redraw);

        for(size_t i = 0; i < Children.size(); i++)
            Children[i]->MouseLeave(Redraw);
    }
}

void Element::MouseMove(int X, int Y, bool* Redraw)
{
    bool Status = InElement(X, Y);

    if(Status)
    {
        for(size_t i = 0; i < Children.size(); i++)
            Children[i]->MouseMove(X - Left, Y - Top, Redraw);
    }
    else if(Hovered)
    {
        for(size_t i = 0; i < Children.size(); i++)
            Children[i]->MouseLeave(Redraw);
    }

    if(Status != Hovered)
    {
        Hovered = Status;

        if(Hovered)
            OnMouseEnter(Redraw);
        else
        {
            TargetDown = false;

            OnMouseLeave(Redraw);
        }
    }
}

void Element::MouseUp(int X, int Y, bool* Redraw)
{
    OnMouseUp(X, Y, Redraw);

    if(TargetDown && Hovered)
        OnClick();

    for(size_t i = 0; i < Children.size(); i++)
        Children[i]->MouseUp(X - Left, Y - Top, Redraw);
}

void Element::MouseDown(int X, int Y, bool* Redraw, Element** Focused)
{
    TargetDown = true;

    OnMouseDown(X, Y, Redraw);

    for(size_t i = 0; i < Children.size(); i++)
        Children[i]->MouseDown(X - Left, Y - Top, Redraw, Focused);

    if(CanFocus && InElement(X, Y))
    {
        *Focused = this;
    }
}

bool Element::InElement(int X, int Y)
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

void Element::OnDraw(SDL_Surface* Surface, int X, int Y)
{

}

void Element::Draw(SDL_Surface* Surface, int X, int Y)
{
    if(!Visible)
        return;

    X += Left;
    Y += Top;
/*
    SDL_Rect OldClip;

    SDL_GetClipRect(Surface, &OldClip);

    SDL_Rect Clip;

    Clip.x = Left + OldClip.x;
    Clip.y = Top + OldClip.y;
    Clip.w = Width;
    Clip.h = Height;

    SDL_SetClipRect(Surface, &Clip);
*/
    OnDraw(Surface, X, Y);

    for(size_t i = 0; i < Children.size(); i++ )
        Children[i]->Draw(Surface, X, Y);

//    SDL_SetClipRect(Surface, &OldClip);
}
