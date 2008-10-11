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

#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include "Application.hpp"

Application::Application():
    Window(0),
    EventKeyDown(0),
    Terminated(false),
    Trapped(0)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();

    #ifdef FRAME_EVENT
    EventFrame = 0;
    #endif

    Width = 800;
    Height = 480;

    Root = this;
    RootElement = this;

    Children = new std::list<Element*>();
}

Application::~Application()
{
}

void Application::Allocate()
{
    if(Mix_OpenAudio(44100, AUDIO_S16SYS, 1, 4096) != 0)
    {
        fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
        return;
    }

    Screen = SDL_SetVideoMode(Width, Height, 32, SDL_DOUBLEBUF | SDL_HWSURFACE);

    if(Screen == NULL)
    {
        Terminated = true;
        return;
    }

    SDL_WM_SetCaption(Title.c_str(), NULL);

    Element::Allocate();
}

void Application::Deallocate()
{
    Element::Deallocate();

    Mix_CloseAudio();

    SDL_Quit();
}

void Application::Draw()
{
    for (Child = Children->begin(); Child != Children->end(); Child++)
        (*Child)->_Draw(Screen, 0, 0, (*Child)->AlphaBlend);

    SDL_Flip(Screen);
}

void Application::Trap(Element* Owner)
{
    Trapped = Owner;

    TrappedX = 0;
    TrappedY = 0;

    Owner = Owner->Owner;

    while(Owner->Owner != 0)
    {
        TrappedX += Owner->Left;
        TrappedY += Owner->Top;

        Owner = Owner->Owner;
    }
}

Element* Application::GetTrapped()
{
    return Trapped;
}

void Application::Release()
{
    Trapped = 0;
}

void Application::Redraw()
{
    FlagRedraw = true;
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

void Application::MouseDown(int X, int Y)
{

}

void Application::Run()
{
    Terminated = false;

    if(Terminated)
        return;

    SDL_Event event;

    FlagRedraw = true;

    while(Terminated == false)
    {
        for (Animation = Animations.begin(); Animation != Animations.end(); Animation++)
        {
            int Ticks = SDL_GetTicks();
            int Delta = Ticks - (*Animation)->Frame;

            if(Delta > 0)
            {
                (*Animation)->Frame = Ticks;
                (*Animation)->Animate(Delta);
            }
        }

        #ifdef NO_FRAME_LIMIT
        FlagRedraw = true;
        #endif

        if(FlagRedraw)
        {
            FlagRedraw = false;

            #ifdef FRAME_EVENT
            if(EventFrame != 0)
                EventFrame();
            #endif

            Draw();
        }

        #ifndef NO_FRAME_LIMIT
        if(Animations.size() == 0)
            SDL_WaitEvent(0);
        #endif

        bool ChildStatus;

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    Terminated = true;
                    break;

                case SDL_KEYDOWN:
                    if(EventKeyDown != 0)
                        EventKeyDown(event.key.keysym.sym);

                    KeyDown(event.key.keysym.sym);
                    break;

                case SDL_KEYUP:
                    KeyUp(event.key.keysym.sym);
                    break;

                case SDL_MOUSEMOTION:
                    if(Trapped != 0)
                        Trapped->MouseMove(event.motion.x - TrappedX - Trapped->Left, event.motion.y - TrappedY - Trapped->Top, Trapped->Inside(event.motion.x - TrappedX, event.motion.y - TrappedY));
                    else
                    {
                        ChildStatus = false;

                        for (std::list<Element*>::reverse_iterator Child = Children->rbegin(); Child != Children->rend(); Child++)
                        {
                            if(!ChildStatus)
                            {
                                ChildStatus = (*Child)->Inside(event.motion.x, event.motion.y);

                                (*Child)->MouseMove(event.motion.x - (*Child)->Left, event.motion.y - (*Child)->Top, ChildStatus);
                            }
                            else
                                (*Child)->_MouseLeave();
                        }
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if(Trapped != 0)
                        Trapped->MouseDown(event.button.x - TrappedX - Trapped->Left, event.button.y - TrappedY - Trapped->Top, Trapped->Inside(event.button.x - TrappedX, event.button.y - TrappedY));
                    else
                    {
                        ChildStatus = false;

                        for (std::list<Element*>::reverse_iterator Child = Children->rbegin(); Child != Children->rend(); Child++)
                        {
                            if(!ChildStatus)
                            {
                                ChildStatus = (*Child)->Inside(event.button.x, event.button.y);

                                (*Child)->MouseDown(event.button.x - (*Child)->Left, event.button.y - (*Child)->Top, ChildStatus);
                            }
                            else
                                (*Child)->_MouseLeave();
                        }
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    if(Trapped != 0)
                        Trapped->MouseUp(event.button.x - TrappedX - Trapped->Left, event.button.y - TrappedY - Trapped->Top, Trapped->Inside(event.button.x - TrappedX, event.button.y - TrappedY));
                    else
                    {
                        ChildStatus = false;

                        for (std::list<Element*>::reverse_iterator Child = Children->rbegin(); Child != Children->rend(); Child++)
                        {
                            if(!ChildStatus)
                            {
                                ChildStatus = (*Child)->Inside(event.button.x, event.button.y);

                                (*Child)->MouseUp(event.button.x - (*Child)->Left, event.button.y - (*Child)->Top, ChildStatus);
                            }
                            else
                                (*Child)->_MouseLeave();
                        }
                    }
                    break;
            }

            if(Terminated)
                goto End;
        }

        #ifndef NO_FRAME_LIMIT
        SDL_Delay(1);
        #endif
    }

    End:
        Deallocate();
}

