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
    Alpha(0),
    DrawHeight(0)
{
}

CategoryBackground::~CategoryBackground()
{
}

void CategoryBackground::Up()
{
    TargetAlpha = 80;
    TargetHeight = Height;

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
   if(TargetHeight != DrawHeight)
   {
        if(TargetHeight > DrawHeight)
        {
            DrawHeight += Delta * 3;

            if(DrawHeight > TargetHeight)
            {
                DrawHeight = TargetHeight;
            }
        }
        else
        {
            DrawHeight -= Delta * 3;

            if(DrawHeight < TargetHeight)
            {
                DrawHeight = TargetHeight;
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

   if(TargetAlpha == Alpha && TargetHeight == DrawHeight)
        Stop();
}

void CategoryBackground::Draw(SDL_Surface* Surface, int X, int Y)
{
    Element::Draw(Surface, X, Y);

    if(Alpha == 0)
        return;

    SDL_Surface* Fill = SDL_CreateRGBSurface(0, Width, DrawHeight, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0);

    SDL_FillRect(Fill, 0, SDL_MapRGB(Fill->format, 255, 255, 255));

    SDL_SetAlpha(Fill, SDL_SRCALPHA, Alpha);

    Graphics::ApplySurface(X, Y + Height - DrawHeight, Fill, Surface);

    SDL_FreeSurface(Fill);
}
