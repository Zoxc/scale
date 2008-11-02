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

WindowScreen* Screen = 0;

GLubyte TextureCoordinate[] = {
    0, 1,
    0, 0,
    1, 1,
    1, 0
};

int GetTicks()
{
    #ifdef WIN32
        return GetTickCount();
    #endif
}

void Focus(Element* NewFocus)
{
    if(NewFocus == 0)
        return;

    Element* Owner = NewFocus->Owner;

    while(Owner != 0)
    {
        Window* Root = dynamic_cast<Window*>(Owner);

        if(Root != 0)
        {
            Root->Focus(NewFocus);
            return;
        }

        Owner = Owner->Owner;
    }
}

WindowScreen::WindowScreen(Element* Owner):
    Window(Owner),
    Captured(0),
    Running(false),
    Terminated(false)
{
}

WindowScreen::~WindowScreen()
{
}

Window::Window(Element* Owner):
    Element(Owner),
    Focused(0)
{
    Root = this;
}

Window::~Window()
{
}

void Window::KeyDown(ElementKey Key)
{
    if(Focused != 0)
    {
        Focused->KeyDown(Key);

        if(Focused->Links != 0)
            for (ElementLinks::iterator Link = Focused->Links->begin(); Link != Focused->Links->end(); Link++)
                if(Key == Link->first)
                {
                    Focus(Link->second);
                    break;
                }
    }
}

void Window::KeyUp(ElementKey Key)
{
    if(Focused != 0)
        Focused->KeyUp(Key);
}

void Window::MouseDown(int X, int Y, bool Hovered)
{
    if(Owner != 0 && Owner->Root != 0)
        Owner->Root->Focus(this);

    Element::MouseDown(X, Y, Hovered);
}

void Window::KillFocus()
{
    Element* OldFocus = Focused;

    Focused = 0;

    if(OldFocus != 0)
        OldFocus->Deactivate();
}

void Window::Focus(Element* NewFocus)
{
    if(NewFocus == 0)
        return;

    if(Focused == NewFocus)
        return;

    Element* OldFocus = Focused;

    Focused = NewFocus;

    if(OldFocus != 0)
        OldFocus->Deactivate();

    Focused = OldFocus;

    NewFocus->Activate();

    Focused = NewFocus;
}

Element::Element(Element* Owner):
    Left(0),
    Top(0),
    Width(0),
    Height(0),
    Owner(Owner),
    Root(0),
    Children(0),
    Links(0),
    Animated(false),
    Visible(true),
    Hovered(false),
    AlphaBlend(255)
{
    if(Owner != 0)
    {
        Root = Owner->Root;

        if(Owner->Children == 0)
            Owner->Children = new std::list<Element*>();

        Owner->Children->push_back(this);
    }
}

Element::~Element()
{
    if(Children != 0)
    {
        while(Children->size() > 0)
            delete *Children->begin();
    }

    if(Links != 0)
        delete Links;

    delete Children;

    if(Owner != 0)
        Owner->Children->remove(this);
}

void Element::SetOwner(Element* NewOwner)
{
    if(Owner != 0)
        Owner->Children->remove(this);

    Owner = NewOwner;

    if(Owner != 0)
    {
        Root = Owner->Root;

        if(Owner->Children == 0)
            Owner->Children = new std::list<Element*>();

        Owner->Children->push_back(this);
    }
}

void Element::Allocate()
{
    if(Children == 0)
        return;

    for (std::list<Element*>::iterator Child = Children->begin(); Child != Children->end(); Child++)
        (*Child)->Allocate();
}

void Element::Deallocate()
{
    if(Children == 0)
        return;

    for (std::list<Element*>::iterator Child = Children->begin(); Child != Children->end(); Child++)
        (*Child)->Deallocate();
}

void Element::KeyDown(ElementKey Key)
{
}

void Element::KeyUp(ElementKey Key)
{
}

void Element::Show()
{
    Visible = true;
}

void Element::Hide()
{
    Visible = false;
}

void Element::Activate()
{
}

void Element::Deactivate()
{
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

void Element::MouseUp(int X, int Y, bool Hovered)
{
    if(Hovered)
    {
        if(Children != 0)
        {
            bool ChildStatus = false;

            for(std::list<Element*>::reverse_iterator Child = Children->rbegin(); Child != Children->rend(); Child++)
            {
                if(!ChildStatus)
                {
                    if((*Child)->Visible)
                    {
                        ChildStatus = (*Child)->Inside(X, Y);

                        (*Child)->MouseUp(X - (*Child)->Left, Y - (*Child)->Top, ChildStatus);
                    }
                }
                else
                    (*Child)->_MouseLeave();
            }
        }
    }
    else if(Hovered)
    {
        if(Children != 0)
            for (std::list<Element*>::reverse_iterator Child = Children->rbegin(); Child != Children->rend(); Child++)
                (*Child)->_MouseLeave();
    }

    if(Element::Hovered != Hovered)
    {
        Element::Hovered = Hovered;

        if(Hovered)
            MouseEnter();
        else
            MouseLeave();
    }
}

void Element::MouseDown(int X, int Y, bool Hovered)
{
    if(Hovered)
    {
        bool ChildStatus = false;

        if(Children != 0)
            for (std::list<Element*>::reverse_iterator Child = Children->rbegin(); Child != Children->rend(); Child++)
            {
                if(!ChildStatus)
                {
                    if((*Child)->Visible)
                    {
                        ChildStatus = (*Child)->Inside(X, Y);

                        (*Child)->MouseDown(X - (*Child)->Left, Y - (*Child)->Top, ChildStatus);
                    }
                }
                else
                    (*Child)->_MouseLeave();
            }
    }
    else if(Element::Hovered)
    {
        if(Children != 0)
            for (std::list<Element*>::reverse_iterator Child = Children->rbegin(); Child != Children->rend(); Child++)
                (*Child)->_MouseLeave();
    }

    if(Element::Hovered != Hovered)
    {
        Element::Hovered = Hovered;

        if(Hovered)
            MouseEnter();
        else
            MouseLeave();
    }
}

void Element::MouseMove(int X, int Y, bool Hovered)
{
    if(Hovered)
    {
        if(Children != 0)
        {
            bool ChildStatus = false;

            for (std::list<Element*>::reverse_iterator Child = Children->rbegin(); Child != Children->rend(); Child++)
            {
                if(!ChildStatus)
                {
                    if((*Child)->Visible)
                    {
                        ChildStatus = (*Child)->Inside(X, Y);

                        (*Child)->MouseMove(X - (*Child)->Left, Y - (*Child)->Top, ChildStatus);
                    }
                }
                else
                    (*Child)->_MouseLeave();
            }
        }
    }
    else if(Element::Hovered)
    {
        if(Children != 0)
            for (std::list<Element*>::reverse_iterator Child = Children->rbegin(); Child != Children->rend(); Child++)
                (*Child)->_MouseLeave();
    }

    if(Element::Hovered != Hovered)
    {
        Element::Hovered = Hovered;

        if(Hovered)
            MouseEnter();
        else
            MouseLeave();
    }
}

void Element::Draw(int X, int Y, unsigned char Alpha)
{
}

void Element::Capture()
{
    Screen->Capture(this);
}

void Element::Release()
{
    Screen->Release();
}

void Element::Start()
{
    Frame = GetTicks();

    Screen->Start(this);
}

void Element::Stop()
{
    Screen->Stop(this);
}

void Element::Redraw()
{
    Screen->DoRedraw = true;
}

void Element::ToFront()
{
    if(Owner == 0)
        return;

    Owner->Children->remove(this);
    Owner->Children->push_back(this);
}

void Element::ToBack()
{
    if(Owner == 0)
        return;

    Owner->Children->remove(this);
    Owner->Children->push_front(this);
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

void Element::Link(ElementKey Key, Element* Link)
{
    if(Links == 0)
        Links = new ElementLinks();

    Links->insert(ElementLink(Key, Link));
}

void Element::_MouseLeave()
{
    if(Hovered)
    {
        Hovered = false;

        MouseLeave();

        if(Children == 0)
            return;

        for (std::list<Element*>::reverse_iterator Child = Children->rbegin(); Child != Children->rend(); Child++)
                (*Child)->_MouseLeave();
    }
}

void Element::DrawChildren(int X, int Y, unsigned char Alpha)
{
    if(!Visible)
        return;

    X += Left;
    Y += Top;

    Draw(X, Y, Alpha);

    if(Children != 0)
        for (std::list<Element*>::iterator Child = Children->begin(); Child != Children->end(); Child++)
            (*Child)->DrawChildren(X, Y, ((*Child)->AlphaBlend * Alpha) >> 8);
}
