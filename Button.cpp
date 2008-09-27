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

#include "Button.hpp"
#include "Graphics.hpp"

SDL_Surface* BorderTL = NULL;
SDL_Surface* BorderTR = NULL;
SDL_Surface* BorderBL = NULL;
SDL_Surface* BorderBR = NULL;
int ButtonCount = 0;

Button::Button(Element* Owner) :
    Element::Element(Owner),
    Down(false)
{
    CanFocus = true;
/*
    if(ButtonCount++ == 0)
    {
        BorderTL = Graphics::OptimizeSurface(IMG_Load("resources/border_tl.png"), true);
        BorderTR = Graphics::OptimizeSurface(IMG_Load("resources/border_tr.png"), true);
        BorderBL = Graphics::OptimizeSurface(IMG_Load("resources/border_bl.png"), true);
        BorderBR = Graphics::OptimizeSurface(IMG_Load("resources/border_br.png"), true);
    }*/
}

Button::~Button()
{/*
    if(--ButtonCount == 0)
    {
        SDL_FreeSurface(BorderTL);
        SDL_FreeSurface(BorderTR);
        SDL_FreeSurface(BorderBL);
        SDL_FreeSurface(BorderBR);
    }*/
}

void Button::MouseEnter()
{
    Element::MouseEnter();

    if(Down)
        Redraw();
}

void Button::MouseLeave()
{
    Element::MouseLeave();

    if(Down)
        Redraw();
}

void Button::MouseUp(int X, int Y)
{
    Element::MouseUp(X, Y);

    if(Down)
    {
        Down = false;

        if(Hovered)
            Redraw();
    }

}

void Button::MouseDown(int X, int Y, Element** NewFocus)
{
    Element::MouseDown(X, Y, NewFocus);

    if(!Down)
    {
        Down = true;

        if(Hovered)
            Redraw();
    }
}

void Button::Activate()
{
    Element::Activate();

    Redraw();
}

void Button::Deactivate()
{
    Element::Deactivate();

    Redraw();
}

void Button::Draw(SDL_Surface* Surface, int X, int Y, unsigned char Alpha)
{
    if(!Focused)
        return;

    SDL_Surface* Fill = Graphics::CreateSurface(Width, Height, true);

    SDL_FillRect(Fill, 0, SDL_MapRGB(Fill->format, 255, 255, 255));

    //Graphics::CopyAlpha(0, 0, BorderTL, Fill);
    //Graphics::CopyAlpha(Fill->w - BorderTR->w, 0, BorderTR, Fill);
    //Graphics::CopyAlpha(0, Fill->h - BorderTR->h, BorderBL, Fill);
    //Graphics::CopyAlpha(Fill->w - BorderTR->w, Fill->h - BorderTR->h, BorderBR, Fill);

    Graphics::HalfAlpha(Fill);
    Graphics::HalfAlpha(Fill);

    Graphics::ApplySurface(X, Y, Fill, Surface);

    SDL_FreeSurface(Fill);
}
