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

#include <math.h>

#include "CategoryBackground.hpp"
#include "Graphics.hpp"
#include "Button.hpp"

extern SDL_Surface* BorderBL;
extern SDL_Surface* BorderBR;
extern SDL_Surface* BorderTL;
extern SDL_Surface* BorderTR;

CategoryBackground::CategoryBackground(Element* AOwner):
    Element::Element(AOwner),
    Mode(0),
    Scroller(0)
{
    AlphaBlend = 0;
    Step = 0;
    //Clip = true;
}

CategoryBackground::~CategoryBackground()
{
}

void CategoryBackground::Allocate()
{
    Element::Allocate();

    Fill = Graphics::CreateSurface(Width, 480, false);

    SDL_FillRect(Fill, 0, SDL_MapRGB(Fill->format, 110, 110, 110));
}

void CategoryBackground::Deallocate()
{
    Element::Deallocate();

    SDL_FreeSurface(Fill);
}

void CategoryBackground::MouseUp(int X, int Y, bool Hovered)
{
    if(Scroller != 0)
        Scroller->ReleaseTarget();

    if(Root->GetTrapped() == this)
        Release();

    Mode = 0;

    Element::MouseUp(X, Y, Hovered);
}

void CategoryBackground::MouseDown(int X, int Y, bool Hovered)
{
    if(Hovered && Scroller != 0 && Y > 64)
    {
        Mode = 1;
        DownY = Y;
        MoveOffset = Y - Scroller->Top;
        Scroller->Target(Y - MoveOffset);
    }
    Element::MouseDown(X, Y, Hovered);
}

void CategoryBackground::MouseMove(int X, int Y, bool Hovered)
{
    if(Mode == 1)
        if(abs(Y - DownY) > 15)
        {
            Mode = 2;
            Trap();
        }

    if(Mode > 0)
        Scroller->Target(Y - MoveOffset);

    Element::MouseMove(X, Y, Hovered);
}

void CategoryBackground::Up()
{
    Start();
    Show();

    Upping = true;

    Redraw();
}

void CategoryBackground::Down()
{
    Upping = false;

    Start();
}

void CategoryBackground::Animate(int Delta)
{
    if(Upping)
        Step += Delta * 3;
    else
        Step -= Delta * 3;

    if(Step <= 0)
    {
        Step = 0;
        Stop();
        Hide();
    }
    else if(Step >= 1000)
    {
        Step = 1000;
        Stop();
    }

    Height =  (int)floor(sin(((float)Step / 1000) * M_PI_2) * 480);
    AlphaBlend = Step * 255 / 1000;
    Top = 480 - Height;

    Redraw();
}

void CategoryBackground::Draw(SDL_Surface* Surface, int X, int Y, unsigned char Alpha)
{
    if(AlphaBlend == 0)
        return;

    SDL_SetAlpha(Fill, SDL_SRCALPHA, AlphaBlend / 15 * 14);

    Graphics::ApplySurface(X, Y, Fill, Surface);
}
