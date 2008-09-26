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

#include "Application.hpp"

Application::Application() : Element::Element(0)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);

    TTF_Init();

    Width = 800;
    Height = 480;

    Root = this;

    Application::Focused = 0;
}

Application::~Application()
{
    Element::Element(0);
}

void Application::Allocate()
{
    Screen = SDL_SetVideoMode(Width, Height, 32, 0);

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

    SDL_Quit();
}

void Application::Draw(SDL_Surface* Surface)
{
    for (Child = Children.begin(); Child != Children.end(); Child++)
        (*Child)->_Draw(Surface, 0, 0, (*Child)->AlphaBlend);

    SDL_Flip(Screen);
}

void Application::_Redraw(Element* Owner)
{
    Redraws.push_back(Owner);
}

void Application::_Start(Element* Owner)
{
    Animations.push_back(Owner);
}

void Application::_Stop(Element* Owner)
{
    if(*Animation == Owner)
            Animation = Animations.erase(Animation);
    else
        Animations.remove(Owner);
}

void Application::KillFocus()
{
    Element* OldFocus = Application::Focused;

    Application::Focused = 0;

    if(OldFocus != 0)
        OldFocus->Deactivate();
}

void Application::Focus(Element* NewFocus)
{
    if(NewFocus == 0)
        return;

    if(Application::Focused == NewFocus)
        return;

    Element* OldFocus = Application::Focused;

    Application::Focused = NewFocus;

    if(OldFocus != 0)
        OldFocus->Deactivate();

    NewFocus->Activate();
}

void Application::MouseDown(int X, int Y)
{
    Element* NewFocus = 0;

    for (ChildBack = Children.rbegin(); ChildBack != Children.rend(); ChildBack++)
    {
        if((*ChildBack)->Hovered)
        {
            (*ChildBack)->MouseDown(X, Y, &NewFocus);
            break;
        }
    }

    if(NewFocus != 0 && NewFocus != Application::Focused)
    {
        Element* OldFocus = Application::Focused;

        Application::Focused = NewFocus;

        if(OldFocus != 0)
            OldFocus->Deactivate();

        if(NewFocus != 0)
            NewFocus->Activate();
    }
}

void Application::Run()
{
    Terminated = false;

    Allocate();

    if(Terminated)
        return;

    SDL_Event event;

    Redraws.push_back(this);

    while(Terminated == false)
    {
        for (Animation = Animations.begin(); Animation != Animations.end(); Animation++)
        {
            int Delta = SDL_GetTicks() - (*Animation)->Frame;

            (*Animation)->Frame = SDL_GetTicks();
            (*Animation)->Animate(Delta);
        }

        if(Redraws.size() > 0)
        {
            Redraws.clear();
            Draw(Screen);
        }

        if(Animations.size() == 0)
            SDL_WaitEvent(0);

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    Terminated = true;
                    break;

                case SDL_KEYDOWN:
                    if(EventKeyDown != 0)
                        EventKeyDown(this, event.key.keysym.sym);

                    if(Application::Focused != 0)
                        switch((int)event.key.keysym.sym)
                        {
                            case SDLK_RETURN:
                                if(Application::Focused != 0)
                                    Application::Focused->Click();
                                break;

                            case SDLK_LEFT:
                                Focus(Application::Focused->Links[ElementLeft]);
                                break;

                            case SDLK_UP:
                                Focus(Application::Focused->Links[ElementUp]);
                                break;

                            case SDLK_RIGHT:
                                Focus(Application::Focused->Links[ElementRight]);
                                break;

                            case SDLK_DOWN:
                                Focus(Application::Focused->Links[ElementDown]);
                                break;
                        }
                    break;

                case SDL_MOUSEMOTION:
                    for (ChildBack = Children.rbegin(); ChildBack != Children.rend(); ChildBack++)
                        (*ChildBack)->_MouseMove(event.motion.x, event.motion.y);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    MouseDown(event.button.x, event.button.y);
                    break;

                case SDL_MOUSEBUTTONUP:
                    for (ChildBack = Children.rbegin(); ChildBack != Children.rend(); ChildBack++)
                    {
                        if((*ChildBack)->Hovered)
                        {
                            (*ChildBack)->MouseUp(event.button.x, event.button.y);
                            break;
                        }
                    }

                    break;
            }

            if(Terminated)
                goto End;
        }

        SDL_Delay(1);
    }

    End:
        Deallocate();
}
