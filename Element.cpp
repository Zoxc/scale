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
    EventClick(0),
    EventKeyDown(0),
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

void Element::OnKeyDown(SDLKey Key)
{
}

void Element::OnShow()
{
}

void Element::OnHide()
{
}

void Element::OnSelect()
{
}

void Element::OnDeselect()
{
}

void Element::OnClick()
{
}

void Element::OnActivate()
{
}

void Element::OnDeactivate()
{
}

void Element::OnMouseLeave()
{
}

void Element::OnMouseEnter()
{
}

void Element::OnMouseUp(int X, int Y)
{
}

void Element::OnMouseDown(int X, int Y)
{
}

void Element::OnDraw(SDL_Surface* Surface, int X, int Y)
{
}

void Element::RedrawElement(Element* Owner)
{
}

void Element::Redraw()
{
    Root->RedrawElement(this);
}

void Element::Show()
{
    OnShow();

    Visible = true;
}

void Element::Hide()
{
    OnHide();

    Visible = false;
}

void Element::KeyDown(SDLKey Key)
{
    bool Ignore = false;

    if(EventKeyDown != 0)
        EventKeyDown(this, Key, &Ignore);

    if(Ignore)
        return;

    OnKeyDown(Key);

    if(Key == SDLK_RETURN)
        Click();
}

void Element::Select(Element* NewSelection)
{
    if(SelectedElement != 0)
    {
        SelectedElement->Selected = false;
        SelectedElement->OnDeselect();
    }

    SelectedElement = NewSelection;

    if(SelectedElement != 0)
    {
        SelectedElement->Selected = true;
        SelectedElement->OnSelect();
    }

}

void Element::Click()
{
    OnClick();

    if(EventClick != 0)
        EventClick(this);

    if(AutoSelect)
        Owner->Select(this);
}

void Element::MouseLeave()
{
    if(Hovered)
    {
        Hovered = false;

        OnMouseLeave();

        for(size_t i = 0; i < Children.size(); i++)
            Children[i]->MouseLeave();
    }
}

void Element::MouseMove(int X, int Y)
{
    bool Status = InElement(X, Y);

    if(Status)
    {
        for(size_t i = 0; i < Children.size(); i++)
            Children[i]->MouseMove(X - Left, Y - Top);
    }
    else if(Hovered)
    {
        for(size_t i = 0; i < Children.size(); i++)
            Children[i]->MouseLeave();
    }

    if(Status != Hovered)
    {
        Hovered = Status;

        if(Hovered)
            OnMouseEnter();
        else
            OnMouseLeave();
    }
}

void Element::MouseUp(int X, int Y)
{
    OnMouseUp(X, Y);

    for(size_t i = 0; i < Children.size(); i++)
        Children[i]->MouseUp(X - Left, Y - Top);
}

void Element::MouseDown(int X, int Y, Element** Focused)
{
    OnMouseDown(X, Y);

    for(size_t i = 0; i < Children.size(); i++)
        Children[i]->MouseDown(X - Left, Y - Top, Focused);

    if(Hovered)
    {
        if(CanFocus)
            *Focused = this;

        Click();
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
