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

#include "CategoryBackground.hpp"
#include "Graphics.hpp"
#include "Button.hpp"

extern SDL_Surface* BorderBL;
extern SDL_Surface* BorderBR;
extern SDL_Surface* BorderTL;
extern SDL_Surface* BorderTR;

CategoryBackground::CategoryBackground(Element* AOwner) :
    Element::Element(AOwner),
    Alpha(0)
{
    CurrentHeight = 0;
}

CategoryBackground::~CategoryBackground()
{
}

void CategoryBackground::Up()
{
    TargetAlpha = 150;
    TargetHeight = 480;

    Start();

    Redraw();
}

void CategoryBackground::Down()
{
    Element::Deselect();

    TargetAlpha = 0;
    TargetHeight = 0;

    Start();
}

void CategoryBackground::Animate(int Delta)
{
   if(TargetHeight != CurrentHeight)
   {
        if(TargetHeight > CurrentHeight)
        {
            CurrentHeight += Delta;

            if(CurrentHeight > TargetHeight)
            {
                CurrentHeight = TargetHeight;
            }
        }
        else
        {
            CurrentHeight -= Delta;

            if(CurrentHeight < TargetHeight)
            {
                CurrentHeight = TargetHeight;
            }
        }
        Redraw();
   }

   if(TargetAlpha != Alpha)
   {
        if(TargetAlpha > Alpha)
        {
            Alpha += Delta / 2;

            if(Alpha > TargetAlpha)
            {
                Alpha = TargetAlpha;
            }
        }
        else
        {
            Alpha -= Delta / 2;

            if(Alpha < TargetAlpha)
            {
                Alpha = TargetAlpha;
            }
        }
        Redraw();
   }

   Height = (int)floor(sin(((float)CurrentHeight / 480) * M_PI_2) * 480);

   Top = 480 - Height;

   if(TargetAlpha == Alpha && TargetHeight == CurrentHeight)
        Stop();
}

void CategoryBackground::Draw(SDL_Surface* Surface, int X, int Y)
{
    Element::Draw(Surface, X, Y);

    if(Alpha == 0)
        return;

    SDL_Surface* Fill = SDL_CreateRGBSurface(0, Width, Height, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0);

    SDL_FillRect(Fill, 0, SDL_MapRGB(Fill->format, 0, 0, 0));

    SDL_SetAlpha(Fill, SDL_SRCALPHA, Alpha);

    Graphics::ApplySurface(X, Y, Fill, Surface);

    SDL_FreeSurface(Fill);
}
