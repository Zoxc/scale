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

#include <iostream>

#include "Application.hpp"

namespace Scale
{
    Application::Application():
        WindowScreen(0),
        EventKeyDown(0)
    {
        #ifdef X11
            x11Window = 0;
            x11Display = 0;
            x11Colormap = 0;
        #endif

        if(Screen != 0)
            return;

        #ifdef FRAME_EVENT
            EventFrame = 0;
        #endif

        Width = 800;
        Height = 480;

        Screen = this;

        Children = new std::list<Element*>();
    }

    Application::~Application()
    {
        Screen = 0;
    }

    #ifdef X11
        Bool Application::WaitForMapNotify( Display *d, XEvent *e, char *arg )
        {
            return (e->type == MapNotify) && (e->xmap.window == (::Window)arg);
        }
    #endif

    void Application::Allocate()
    {
        #ifdef WIN32
            WNDCLASS sWC;
            sWC.style = CS_HREDRAW | CS_VREDRAW;
            sWC.lpfnWndProc = WndProc;
            sWC.cbClsExtra = 0;
            sWC.cbWndExtra = 0;
            sWC.hInstance = 0;
            sWC.hIcon = 0;
            sWC.hCursor = 0;
            sWC.lpszMenuName = 0;
            sWC.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
            sWC.lpszClassName = "WindowHandle";
            ATOM registerClass = RegisterClass(&sWC);

            if (!registerClass)
                throw "Failed to register the window class";

            RECT	sRect;
            SetRect(&sRect, 0, 0, Width, Height);
            AdjustWindowRectEx(&sRect, WS_CAPTION | WS_SYSMENU, false, 0);
            eglHandle = CreateWindow("WindowHandle", Title.c_str(), WS_VISIBLE | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, Width + GetSystemMetrics(SM_CXFIXEDFRAME) * 2, Height + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYFIXEDFRAME) * 2, 0, 0, 0, 0);

            hDC = GetDC(eglHandle);
            if (!hDC)
                throw "Failed to create the device context";

            eglDisplay = eglGetDisplay(hDC);
        #endif

        #ifdef X11
            XSetWindowAttributes sWA;
            unsigned int ui32Mask;
            int i32Depth;

            // Initializes the display and screen
            x11Display = XOpenDisplay(0);

            if (!x11Display)
                throw "Error: Unable to open X display";

            x11Screen = XDefaultScreen(x11Display);

            // Gets the window parameters
            i32Depth = DefaultDepth(x11Display, x11Screen);
            x11Visual = new XVisualInfo;
            XMatchVisualInfo(x11Display, x11Screen, i32Depth, TrueColor, x11Visual);

            if (!x11Visual)
                throw "Error: Unable to acquire visual";

            x11Colormap = XCreateColormap(x11Display, RootWindow(x11Display, x11Screen), x11Visual->visual, AllocNone);

            sWA.colormap = x11Colormap;
            sWA.background_pixel = 0xFFFFFFFF;
            sWA.border_pixel = 0;
            sWA.event_mask = StructureNotifyMask | ExposureMask | ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask;

            ui32Mask = CWBackPixel | CWBorderPixel | CWEventMask | CWColormap;

            // Creates the X11 window
            x11Window = XCreateWindow(x11Display, RootWindow(x11Display, x11Screen), 0, 0, Width, Height,
                                         0, CopyFromParent, InputOutput, CopyFromParent, ui32Mask, &sWA);

            XSetStandardProperties(x11Display, x11Window, Title.c_str(), Title.c_str(), None, 0, 0, 0);

            XMapWindow(x11Display, x11Window);

            XEvent event;

            XIfEvent(x11Display, &event, WaitForMapNotify, (char*)x11Window);

            Atom wmDelete = XInternAtom(x11Display, "WM_DELETE_WINDOW", True);
            XSetWMProtocols(x11Display, x11Window, &wmDelete, 1);

            XSetWMColormapWindows(x11Display, x11Window, &x11Window, 1 );

            XFlush(x11Display);

            eglHandle = (EGLNativeWindowType)x11Window;

            eglDisplay = eglGetDisplay((EGLNativeDisplayType)x11Display);
        #endif

        if(eglDisplay == EGL_NO_DISPLAY)
             eglDisplay = eglGetDisplay((EGLNativeDisplayType)EGL_DEFAULT_DISPLAY);

        EGLint iMajorVersion, iMinorVersion;

        if (!eglInitialize(eglDisplay, &iMajorVersion, &iMinorVersion))
            throw "eglInitialize() failed.";

        const EGLint pi32ConfigAttribs[] = {EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_RENDERABLE_TYPE,EGL_OPENGL_ES2_BIT, EGL_NONE};

        int iConfigs;
        if (!eglChooseConfig(eglDisplay, pi32ConfigAttribs, &eglConfig, 1, &iConfigs) || (iConfigs != 1))
            throw "eglChooseConfig() failed.";

        eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, eglHandle, NULL);

        if(eglSurface == EGL_NO_SURFACE)
        {
            eglGetError();
            eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, NULL, NULL);
        }

        EGLint ai32ContextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };

        eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, ai32ContextAttribs);

        eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glActiveTexture(GL_TEXTURE0);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        Shader = new OpenGL::Program();

        // Fragment and vertex shaders code
        char* FragmentSource = "precision lowp float;\
            varying vec2 VCord;\
            uniform sampler2D Texture;\
            uniform vec4 Color;\
            uniform int Mode;\
            uniform int Effect;\
            uniform vec2 EffectOptions;\
            float Temp;\
            void main (void)\
            {\
                if(Mode == 1)\
                {\
                    gl_FragColor = texture2D(Texture, VCord);\
                    gl_FragColor.a *= Color.a;\
                }\
                else if(Mode == 0)\
                    gl_FragColor = Color;\
                else\
                {\
                    gl_FragColor = Color;\
                    gl_FragColor.a *= texture2D(Texture, VCord).a;\
                }\
                \
                if(Effect == 1)\
                {\
                    Temp = (gl_FragCoord.y - EffectOptions.x) / EffectOptions.y ;\
                    if(Temp < 1.0)\
                        gl_FragColor.a *= Temp;\
                }\
            }";

        char* VertexSource = "precision lowp float;\
            attribute vec2 APoint;\
            attribute vec2 ACord;\
            varying vec2 VCord;\
            void main(void)\
            {\
                gl_Position.x = APoint.x / 400.0 - 1.0;\
                gl_Position.y = -(APoint.y / 240.0 - 1.0);\
                VCord = ACord;\
            }";

        OpenGL::Shader FragmentShader(GL_FRAGMENT_SHADER, FragmentSource);
        OpenGL::Shader VertexShader(GL_VERTEX_SHADER, VertexSource);

        *Shader << FragmentShader;
        *Shader << VertexShader;

        glBindAttribLocation(Shader->Handle, 0, "APoint");
        glBindAttribLocation(Shader->Handle, 1, "ACord");

        Shader->Assign();

        TextureUniform = glGetUniformLocation(Shader->Handle, "Texture");
        ModeUniform = glGetUniformLocation(Shader->Handle, "Mode");
        EffectUniform = glGetUniformLocation(Shader->Handle, "Effect");
        EffectOptionsUniform = glGetUniformLocation(Shader->Handle, "EffectOptions");
        ColorUniform = glGetUniformLocation(Shader->Handle, "Color");
    }

    void Application::Deallocate()
    {
        Element::Deallocate();

        delete Shader;

        eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT) ;
        eglTerminate(eglDisplay);

        #ifdef X11
        if(x11Visual)
            XDestroyWindow(x11Display, x11Window);

        if(x11Colormap)
            XFreeColormap(x11Display, x11Colormap);

        //if (x11Display)
        //    XCloseDisplay(x11Display);

        if(x11Visual)
            XFree((char*)x11Visual);
        #endif
    }

    void Application::Capture(Element* Owner)
    {
        Captured = Owner;

        CapturedX = 0;
        CapturedY = 0;

        Owner = Owner->Owner;

        while(Owner->Owner != 0)
        {
            CapturedX += Owner->Left;
            CapturedY += Owner->Top;

            Owner = Owner->Owner;
        }
    }

    void Application::Release()
    {
        Captured = 0;
    }

    void Application::Start(Element* Owner)
    {
        Animations.push_back(Owner);
    }

    void Application::Stop(Element* Owner)
    {
        if(*Animation == Owner)
                Animation = Animations.erase(Animation);
        else
            Animations.remove(Owner);
    }

    void Application::Stop()
    {
        Running = false;
    }

    void Application::KeyDown(ElementKey Key)
    {
        if(EventKeyDown != 0)
            EventKeyDown(Key);

        Window::KeyDown(Key);
    }

    void Application::KeyUp(ElementKey Key)
    {
        Window::KeyUp(Key);
    }

    void Application::MouseDown(int X, int Y, bool Hovered)
    {
        if(Captured != 0)
            Captured->MouseDown(X - CapturedX - Captured->Left, Y - CapturedY - Captured->Top, Captured->Inside(X - CapturedX, Y - CapturedY));
        else
        {
            bool ChildStatus = false;

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
    }

    void Application::MouseMove(int X, int Y, bool Hovered)
    {
        if(Captured != 0)
            Captured->MouseMove(X - CapturedX - Captured->Left, Y - CapturedY - Captured->Top, Captured->Inside(X - CapturedX, Y - CapturedY));
        else
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

    void Application::MouseUp(int X, int Y, bool Hovered)
    {
        if(Captured != 0)
            Captured->MouseUp(X - CapturedX - Captured->Left, Y - CapturedY - Captured->Top, Captured->Inside(X - CapturedX, Y - CapturedY));
        else
        {
            bool ChildStatus = false;

            for (std::list<Element*>::reverse_iterator Child = Children->rbegin(); Child != Children->rend(); Child++)
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

    #ifdef WIN32
    LRESULT CALLBACK Application::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
            case WM_SYSCOMMAND:
                switch (wParam)
                {
                    case SC_SCREENSAVE:
                    case SC_MONITORPOWER:
                    return 0;
                }
                break;

            case WM_KEYDOWN:
                Screen->KeyDown(wParam);
                break;

            case WM_KEYUP:
                Screen->KeyUp(wParam);
                break;

            case WM_LBUTTONDOWN:
            case WM_RBUTTONDOWN:
            case WM_MBUTTONDOWN:
                Screen->MouseDown(LOWORD(lParam), HIWORD(lParam), 0);
                SetCapture(hWnd);
                break;

            case WM_MOUSEMOVE:
                Screen->MouseMove((short)LOWORD(lParam), (short)HIWORD(lParam), 0);
                break;

            case WM_MOUSELEAVE:
                for (std::list<Element*>::reverse_iterator Child = Screen->Children->rbegin(); Child != Screen->Children->rend(); Child++)
                        (*Child)->_MouseLeave();
                break;

            case WM_LBUTTONUP:
            case WM_RBUTTONUP:
            case WM_MBUTTONUP:
                Screen->MouseUp(LOWORD(lParam), HIWORD(lParam), 0);
                ReleaseCapture();
                break;

            case WM_CLOSE:
                Screen->Running = false;
                PostQuitMessage(0);
                return 1;

            case WM_PAINT:
                Screen->DoRedraw = true;
                break;
        }

        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    #endif

    void Application::Run()
    {
        Element::Allocate();

        Running = true;
        DoRedraw = true;

        #ifdef WIN32
            MSG msg;
        #endif

        while(Running)
        {
            #ifdef WIN32
                while(PeekMessage(&msg, eglHandle, 0, 0, PM_REMOVE))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            #endif

            #ifdef X11
                int i32NumMessages = XPending( x11Display );
                for( int i = 0; i < i32NumMessages; i++ )
                {
                    XEvent	event;
                    XNextEvent( x11Display, &event );

                    switch(event.type)
                    {
                        // Exit on mouse click
                        case ButtonPress:
                        //  Running = false;
                            break;

                        default:
                            break;
                    }
                }
            #endif

            if(!Running)
                break;

            for (Animation = Animations.begin(); Animation != Animations.end(); Animation++)
            {
                int Ticks = GetTicks();
                int Delta = Ticks - (*Animation)->Frame;

                if(Delta > 0)
                {
                    (*Animation)->Frame = Ticks;
                    (*Animation)->Animate(Delta);
                }
            }

            if(!Running)
                break;

            if(DoRedraw)
            {
                glClear(GL_COLOR_BUFFER_BIT);

                for (Child = Children->begin(); Child != Children->end(); Child++)
                    (*Child)->DrawChildren(0, 0, (*Child)->AlphaBlend);

                #ifdef FRAME_EVENT
                if(EventFrame != 0)
                    EventFrame();
                #endif

                eglSwapBuffers(eglDisplay, eglSurface);

                DoRedraw = false;
            }

            #ifdef WIN32
                #ifndef NO_FRAME_LIMIT
                if(Animations.size() == 0)
                    WaitMessage();

                Sleep(1);
                #endif
            #endif
        }

        Deallocate();
    }
};
