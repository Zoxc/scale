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

#include "Options.hpp"
#include "Element.hpp"

namespace Scale
{
    typedef void (*KeyEvent)(ElementKey Key);
    #ifdef FRAME_EVENT
    typedef void (*FrameEvent)();
    #endif

    class Application:
        public WindowScreen
    {
        public:
            Application();
            virtual ~Application();

            void Allocate();
            void Deallocate();

            void MouseUp(int X, int Y, bool Hovered);
            void MouseMove(int X, int Y, bool Hovered);
            void MouseDown(int X, int Y, bool Hovered);

            void KeyDown(ElementKey Key);
            void KeyUp(ElementKey Key);

            void Stop();
            void Run();

            Element* GetTrapped();

            #ifdef FRAME_EVENT
            FrameEvent EventFrame;
            #endif

            KeyEvent EventKeyDown;

            std::string Title;

        private:
            EGLDisplay eglDisplay;
            EGLConfig eglConfig;
            EGLSurface eglSurface;
            EGLContext eglContext;
            EGLNativeWindowType eglHandle;

            #ifdef WIN32
                HDC hDC;
                static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
            #endif

            #ifdef X11
                ::Window x11Window;
                Display* x11Display;
                long x11Screen;
                XVisualInfo* x11Visual;
                Colormap x11Colormap;
                static Bool WaitForMapNotify(Display *d, XEvent *e, char *arg);
            #endif

            std::list<Element*> Animations;

            std::list<Element*>::iterator Animation;
            std::list<Element*>::iterator Child;
            std::list<Element*>::reverse_iterator ChildBack;

            int CapturedX;
            int CapturedY;

            void MouseDown(int X, int Y);
            void MouseUp(int X, int Y);
            void MouseMove(int X, int Y);

            void Capture(Element* Owner);
            void Release();
            void Redraw();
            void Start(Element* Owner);
            void Stop(Element* Owner);
    };
};
