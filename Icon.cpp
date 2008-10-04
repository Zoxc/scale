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

#include "Icon.hpp"
#include "Graphics.hpp"

SDL_Surface* BorderTL = NULL;
SDL_Surface* BorderTR = NULL;
SDL_Surface* BorderBL = NULL;
SDL_Surface* BorderBR = NULL;

int IconCount = 0;

Icon::Icon(Element* Owner) :
    Button(Owner),
    Focused(false)
{
}

Icon::~Icon()
{
}

void Icon::Click()
{
}

void Icon::Allocate()
{
    Element::Allocate();

    if(IconCount++ == 0)
    {
        BorderTL = Graphics::OptimizeSurface(IMG_Load("resources/border_tl.png"), true);
        BorderTR = Graphics::OptimizeSurface(IMG_Load("resources/border_tr.png"), true);
        BorderBL = Graphics::OptimizeSurface(IMG_Load("resources/border_bl.png"), true);
        BorderBR = Graphics::OptimizeSurface(IMG_Load("resources/border_br.png"), true);
    }

    Fill = Graphics::CreateSurface(Width, Height, true);

    SDL_FillRect(Fill, 0, SDL_MapRGB(Fill->format, 255, 255, 255));

    Graphics::CopyAlpha(0, 0, BorderTL, Fill);
    Graphics::CopyAlpha(Fill->w - BorderTR->w, 0, BorderTR, Fill);
    Graphics::CopyAlpha(0, Fill->h - BorderTR->h, BorderBL, Fill);
    Graphics::CopyAlpha(Fill->w - BorderTR->w, Fill->h - BorderTR->h, BorderBR, Fill);

    Graphics::HalfAlpha(Fill, 2);
}

void Icon::Deallocate()
{
    Element::Deallocate();

    if(--IconCount == 0)
    {
        SDL_FreeSurface(BorderTL);
        SDL_FreeSurface(BorderTR);
        SDL_FreeSurface(BorderBL);
        SDL_FreeSurface(BorderBR);
    }

    SDL_FreeSurface(Fill);
}

void Icon::Activate()
{
    Focused = true;

    Redraw();
}

void Icon::Deactivate()
{
    Focused = false;

    Redraw();
}

void Icon::Draw(SDL_Surface* Surface, int X, int Y, unsigned char Alpha)
{
    if(!Focused)
        return;

    Graphics::ApplyAlpha(X, Y, Fill, Surface, Alpha);
}
