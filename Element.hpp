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

#pragma once
#include "SDL.h"
#include <vector>

class Element;

typedef void (*ElementNotifyEvent)(Element* Owner);
typedef void (*ElementKeyEvent)(Element* Owner, SDLKey Key, bool* Ignore);

enum ElementLink
{
    ElementLeft, ElementUp, ElementRight, ElementDown
};

class Element
{
    public:
        Element(Element* Owner);
        virtual ~Element();

        virtual void Allocate();
        virtual void Deallocate();
        virtual void KeyDown(SDLKey Key);
        virtual void Click();
        virtual void MouseEnter();
        virtual void MouseLeave();
        virtual void MouseUp(int X, int Y);
        virtual void MouseDown(int X, int Y, Element** NewFocus);
        virtual void Activate();
        virtual void Deactivate();
        virtual void Select();
        virtual void Deselect();
        virtual void Show();
        virtual void Hide();
        virtual void Draw(SDL_Surface* Surface, int X, int Y);

        ElementNotifyEvent EventClick;
        ElementKeyEvent EventKeyDown;

        int Left;
        int Top;
        int Width;
        int Height;

        void* Tag;

        Element* Links[sizeof(ElementLink)];
        Element* Owner;
        Element* Root;
        Element* SelectedElement;

        std::vector<Element*> Children;

        bool AutoSelect;
        bool CanFocus;
        bool Focused;
        bool Selected;
        bool Visible;
        bool Hovered;

        void SelectElement(Element* NewSelection);
        void Redraw();
        bool Inside(int X, int Y);

        // Local, used by Application
        void _Draw(SDL_Surface* Surface, int X, int Y);
        void _MouseMove(int X, int Y);
        void _MouseLeave();

    private:
        virtual void RedrawElement(Element* Owner);
};
