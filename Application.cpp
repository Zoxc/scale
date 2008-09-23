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
    TTF_Init();

    Root = this;

    Application::Focused = 0;
}

Application::~Application()
{
    SDL_Quit();
}

void Application::Draw(SDL_Surface* Surface, int X, int Y)
{
    for(size_t i = 0; i < Children.size(); i++ )
        Children[i]->Draw(Surface, 0, 0);

    SDL_Flip(Screen);
}

bool Application::Initialize()
{
    Screen = SDL_SetVideoMode(800, 480, 32, 0);

    if(Screen == NULL)
    {
        return false;
    }

    SDL_WM_SetCaption(Title.c_str(), NULL);

    return true;
}

void Application::RedrawElement(Element* Owner)
{
    Redraws.push_back(Owner);
}

void Application::Focus(Element* NewFocus)
{
    if(NewFocus == 0)
        return;

    if(Application::Focused == NewFocus)
        return;

    if(Application::Focused != 0)
    {
        Application::Focused->Focused = false;
        Application::Focused->OnDeactivate();
    }

    NewFocus->Focused = true;
    NewFocus->OnActivate();

    Application::Focused = NewFocus;
}

void Application::MouseDown(int X, int Y)
{
    Element* NewFocus = 0;

    for(size_t i = 0; i < Children.size(); i++ )
        Children[i]->MouseDown(X, Y, &NewFocus);

    if(NewFocus != 0 && NewFocus != Application::Focused)
    {
        if(Application::Focused != 0)
        {
            Application::Focused->Focused = false;
            Application::Focused->OnDeactivate();
        }

        if(NewFocus != 0)
        {
            NewFocus->Focused = true;
            NewFocus->OnActivate();
        }

        Application::Focused = NewFocus;
    }
}

void Application::Run()
{
    if(!Initialize())
        return;

    SDL_Event event;

    Terminated = false;

    Draw(Screen, 0, 0);

    while(Terminated == false)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    Terminated = true;
                    break;

                case SDL_KEYDOWN:
                    if(Application::Focused != 0)
                    {
                        switch(event.key.keysym.sym)
                        {
                            case SDLK_RETURN:
                                if(Application::Focused != 0)
                                {
                                    Application::Focused->OnClick();

                                    if(Application::Focused->EventClick != 0)
                                        Application::Focused->EventClick(this);
                                }
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
                    }
                    break;

                case SDL_MOUSEMOTION:
                    for(size_t i = 0; i < Children.size(); i++ )
                        Children[i]->MouseMove(event.motion.x, event.motion.y);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    MouseDown(event.button.x, event.button.y);
                    break;

                case SDL_MOUSEBUTTONUP:
                    for(size_t i = 0; i < Children.size(); i++ )
                        Children[i]->MouseUp(event.button.x, event.button.y);

                    break;
            }
        }

        if(Redraws.size() > 0)
        {
            Redraws.clear();
            Draw(Screen, 0, 0);
        }

        SDL_Delay(1);
    }
}

