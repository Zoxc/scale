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

#include "SDL_mixer.h"

#include "Category.hpp"
#include "Graphics.hpp"
#include "Button.hpp"
#include "Main.hpp"

extern SDL_Surface* BorderBL;
extern SDL_Surface* BorderBR;
extern SDL_Surface* BorderTL;
extern SDL_Surface* BorderTR;

Mix_Chunk* SoundUp = 0;
Mix_Chunk* SoundDown = 0;

Category::Category(Element* AOwner) :
    Element::Element(AOwner),
    Alpha(0),
    TargetAlpha(0),
    Hide(0),
    Show(0)
{
}

Category::~Category()
{
}

void Category::Allocate()
{
    Element::Allocate();

    Fill = Graphics::CreateSurface(Width, Height, false);

    SDL_FillRect(Fill, 0, SDL_MapRGB(Fill->format, 0, 0, 0));
}

void Category::Deallocate()
{
    Element::Deallocate();

    SDL_FreeSurface(Fill);
}

void Category::MouseDown(int X, int Y, bool Hovered)
{
    if(Hovered)
    {
        if(Root->Focused == this)
            Root->KillFocus();
        else
            Root->Focus(this);
    }

    Element::MouseDown(X, Y, Hovered);
}

void Category::Activate()
{
    if(SoundUp == 0)
        SoundUp = Mix_LoadWAV("resources/up.wav");

    Mix_PlayChannel(-1, SoundUp, 0);

    TargetAlpha = 150;

    Start();

    Redraw();

    Menu.KillFocus();

    Show->Up();

    if(Hide != 0)
        Hide->Hide();
}

void Category::Deactivate()
{
    if(SoundDown == 0)
        SoundDown = Mix_LoadWAV("resources/down.wav");

    if(Root->Focused == 0)
        Mix_PlayChannel(-1, SoundDown, 0);

    TargetAlpha = 0;

    Start();

    Focus(TaskList);

    Show->Down();

    if(Hide != 0)
        Hide->Show();
}

void Category::Animate(int Delta)
{
   if(TargetAlpha != Alpha)
   {
        if(TargetAlpha > Alpha)
        {
            Alpha += Delta;

            if(Alpha > TargetAlpha)
            {
                Alpha = TargetAlpha;
                Stop();
            }
        }
        else
        {
            Alpha -= Delta;

            if(Alpha < TargetAlpha)
            {
                Alpha = TargetAlpha;
                Stop();
            }
        }
        Redraw();
   }
}

void Category::Draw(SDL_Surface* Surface, int X, int Y, unsigned char Alpha)
{
    SDL_SetAlpha(Fill, SDL_SRCALPHA, Category::Alpha);

    Graphics::ApplySurface(X, Y, Fill, Surface);
}
