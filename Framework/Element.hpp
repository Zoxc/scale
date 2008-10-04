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
#include <list>
#include <map>

class Element;
class ElementRoot;

typedef void (*ElementNotifyEvent)(Element* Owner);
typedef void (*ElementKeyEvent)(Element* Owner, SDLKey Key);
typedef SDLKey ElementKey;

typedef std::pair<ElementKey, Element*> ElementLink;
typedef std::map<ElementKey, Element*> ElementLinks;

#define ElementUp SDLK_UP
#define ElementDown SDLK_DOWN
#define ElementLeft SDLK_LEFT
#define ElementRight SDLK_RIGHT
#define ElementGo SDLK_RETURN

class Element
{
    public:
        Element(Element* Owner);
        virtual ~Element();

        virtual void Allocate();
        virtual void Deallocate();
        virtual void KeyDown(ElementKey Key);
        virtual void KeyUp(ElementKey Key);
        virtual void Animate(int Delta);
        virtual void MouseEnter();
        virtual void MouseLeave();
        virtual void MouseUp(int X, int Y, bool Hovered);
        virtual void MouseMove(int X, int Y, bool Hovered);
        virtual void MouseDown(int X, int Y, Element** NewFocus, bool Hovered);
        virtual void Activate();
        virtual void Deactivate();
        virtual void Select();
        virtual void Deselect();
        virtual void Show();
        virtual void Hide();
        virtual void Draw(SDL_Surface* Surface, int X, int Y, unsigned char Alpha);

        int Left;
        int Top;
        int Width;
        int Height;
        int Frame;

        void* Tag;

        Element* Owner;
        ElementRoot* Root;
        Element* SelectedElement;

        std::list<Element*>* Children;
        ElementLinks* Links;

        bool Clip;
        bool Animated;
        bool CanSelect;
        bool CanFocus;
        bool Selected;
        bool Visible;
        bool Hovered;
        bool Down;

        unsigned char AlphaBlend;

        void Link(ElementKey Key, Element* Link);
        void SelectElement(Element* NewSelection);
        void SetOwner(Element* NewOwner);
        bool Inside(int X, int Y);

        // Calls to Root
        void Redraw();
        void Start();
        void Stop();
        void Trap();
        void Release();

        // Called by Root
        void _Draw(SDL_Surface* Surface, int X, int Y, unsigned char Alpha);
        void _MouseLeave();
};

class ElementRoot:
    public Element
{
    public:
        ElementRoot(Element* Owner);
        virtual ~ElementRoot();

        Element* Focused;
        Element* Trapped;

        virtual void Redraw() = 0;
        virtual void Start(Element* Owner) = 0;
        virtual void Stop(Element* Owner) = 0;
        virtual void Trap(Element* Owner) = 0;
        virtual void Release() = 0;
};
