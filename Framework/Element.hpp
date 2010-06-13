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
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "EGL/egl.h"
#include "GLES2/gl2.h"
#include "GLES2/gl2ext.h"

#ifdef WIN32
    #include "windows.h"
#endif

#ifdef X11
    #include "X11/Xlib.h"
    #include "X11/Xutil.h"
    #include "X11/keysym.h"
#endif

#include "OpenGL/OpenGL.Texture.hpp"
#include "OpenGL/OpenGL.Shader.hpp"
#include "OpenGL/OpenGL.Program.hpp"
#include "OpenGL/OpenGL.Buffer.hpp"

#include <assert.h>
#include <list>
#include <map>
#include <iostream>

namespace Scale
{
    extern int DrawCalls;

    class Element;
    class Window;

    typedef int ElementKey;

    typedef void (*ElementNotifyEvent)(Element* Owner);
    typedef void (*ElementKeyEvent)(Element* Owner, ElementKey Key);

    typedef std::pair<ElementKey, Element*> ElementLink;
    typedef std::map<ElementKey, Element*> ElementLinks;

    #ifdef WIN32
        #define ElementUp VK_UP
        #define ElementDown VK_DOWN
        #define ElementLeft VK_LEFT
        #define ElementRight VK_RIGHT
        #define ElementGo VK_RETURN
    #endif

	#ifndef M_PI_2
		#define M_PI_2 1.5707963267948966192E0
	#endif

    #ifdef X11
        #define ElementUp XK_Up
        #define ElementDown XK_Down
        #define ElementLeft XK_Left
        #define ElementRight XK_Right
        #define ElementGo XK_Return
    #endif

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
            virtual void MouseDown(int X, int Y, bool Hovered);
            virtual void Activate();
            virtual void Deactivate();
            virtual void Show();
            virtual void Hide();
            virtual void Draw(int X, int Y, unsigned char Alpha);

            int Left;
            int Top;
            int Width;
            int Height;
            int Frame;

            void* Tag;

            Element* Owner;
            Window* Root;

            std::list<Element*>* Children;
            ElementLinks* Links;

            bool Animated;
            bool Visible;
            bool Hovered;
            //bool Down;

            unsigned char AlphaBlend;

            void ToFront();
            void ToBack();

            void Link(ElementKey Key, Element* Link);
            void SelectElement(Element* NewSelection);
            void SetOwner(Element* NewOwner);
            bool Inside(int X, int Y);

            // Calls to Root
            void Redraw();
            void Start();
            void Stop();
            void Capture();
            void Release();

            // Called by Root
            void DrawChildren(int X, int Y, unsigned char Alpha);
            void _MouseLeave();
    };

    void Focus(Element* NewFocus);
    int GetTicks();

    class Window:
        public Element
    {
        public:
            Window(Element* Owner);
            virtual ~Window();

            Element* Focused;

            void KillFocus();
            void Focus(Element* NewFocus);

            void MouseDown(int X, int Y, bool Hovered);
            void KeyDown(ElementKey Key);
            void KeyUp(ElementKey Key);
    };

    class WindowScreen:
        public Window
    {
        public:
            WindowScreen(Element* Owner);
            virtual ~WindowScreen();

            Element* Captured;

            GLuint EffectUniforms[4];
            GLuint EffectOptionsUniforms[4];
            GLuint TextureUniforms[4];
            GLuint ColorUniforms[4];
            GLuint OffsetUniforms[4];

            bool Running;
            bool Terminated;
            bool DoRedraw;

            virtual void ChangeMode(unsigned int Mode) = 0;


            virtual void RaiseGLError() = 0;
            virtual void Capture(Element* Owner) = 0;
            virtual void Release() = 0;
            virtual void Start(Element* Owner) = 0;
            virtual void Stop(Element* Owner) = 0;
    };

    extern WindowScreen* Screen;
    extern GLubyte TextureCoordinate[];
};
