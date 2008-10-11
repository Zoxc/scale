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
#include <string>
#include <list>
#include "SDL.h"

#include "Options.hpp"
#include "Element.hpp"

typedef void (*KeyEvent)(SDLKey Key);
#ifdef FRAME_EVENT
typedef void (*FrameEvent)();
#endif

class Application:
    public Window
{
    public:
        Application();
        virtual ~Application();

        void Allocate();
        void Deallocate();
        void Run();
        void Draw();
        Element* GetTrapped();

        #ifdef FRAME_EVENT
        FrameEvent EventFrame;
        #endif
        KeyEvent EventKeyDown;
        std::string Title;
        bool Terminated;
        bool FlagRedraw;
        std::list<Element*> Animations;

    private:
        std::list<Element*>::iterator Animation;
        std::list<Element*>::iterator Child;
        std::list<Element*>::reverse_iterator ChildBack;

        SDL_Surface* Screen;
        void MouseDown(int X, int Y);

        Element* Trapped;

        int TrappedX;
        int TrappedY;

        void Trap(Element* Owner);
        void Release();
        void Redraw();
        void Start(Element* Owner);
        void Stop(Element* Owner);
};
