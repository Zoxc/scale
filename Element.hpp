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
        Element(Element* AOwner);
        virtual ~Element();

        virtual void OnKeyDown(SDLKey Key);
        virtual void OnClick();
        virtual void OnMouseEnter();
        virtual void OnMouseLeave();
        virtual void OnMouseUp(int X, int Y);
        virtual void OnMouseDown(int X, int Y);
        virtual void OnActivate();
        virtual void OnDeactivate();
        virtual void OnSelect();
        virtual void OnDeselect();
        virtual void OnDraw(SDL_Surface* Surface, int X, int Y);

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

        void Select(Element* NewSelection);
        void Redraw();
        void Draw(SDL_Surface* Surface, int X, int Y);
        bool InElement(int X, int Y);
        virtual void Click();
        void KeyDown(SDLKey Key);
        void MouseDown(int X, int Y, Element** Focused);
        void MouseUp(int X, int Y);
        void MouseMove(int X, int Y);
        void MouseLeave();

    private:
        virtual void RedrawElement(Element* Owner);
};
