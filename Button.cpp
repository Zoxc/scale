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

Button::Button(Element* AOwner, ButtonType type) :
    Element::Element(AOwner),
    Down(false),
    Over(false),
    Type(type)
{
    if(Type != ButtonTypePush)
        CanFocus = true;

    if(ButtonCount++ == 0)
    {
        BorderTL = Graphics::ConvertSurface(IMG_Load("resources/border_tl.png"));
        BorderTR = Graphics::ConvertSurface(IMG_Load("resources/border_tr.png"));
        BorderBL = Graphics::ConvertSurface(IMG_Load("resources/border_bl.png"));
        BorderBR = Graphics::ConvertSurface(IMG_Load("resources/border_br.png"));
    }
}

Button::~Button()
{
    if(--ButtonCount == 0)
    {
        SDL_FreeSurface(BorderTL);
        SDL_FreeSurface(BorderTR);
        SDL_FreeSurface(BorderBL);
        SDL_FreeSurface(BorderBR);
    }
}

void Button::OnMouseEnter(bool* Redraw)
{
    if(Down)
        *Redraw = true;
}

void Button::OnMouseLeave(bool* Redraw)
{
    if(Down)
        *Redraw = true;
}

void Button::OnMouseUp(int X, int Y, bool* Redraw)
{
    if(Down)
    {
        Down = false;

        if(Hovered)
            *Redraw = true;
    }

}

void Button::OnMouseDown(int X, int Y, bool* Redraw)
{
    if(!Down)
    {
        Down = true;

        if(Hovered)
            *Redraw = true;
    }
}

void Button::OnDraw(SDL_Surface* Surface, int X, int Y)
{
    switch(Type)
    {
        case ButtonTypePush:
        {
            if(!(Hovered && Down))
                return;

            SDL_Surface* Fill = SDL_CreateRGBSurface(0, Width, Height, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);

            SDL_FillRect(Fill, 0, SDL_MapRGB(Fill->format, 255, 255, 255));

            Graphics::ApplyAlpha(0, 0, BorderTL, Fill);
            Graphics::ApplyAlpha(Fill->w - BorderTR->w, 0, BorderTR, Fill);
            Graphics::ApplyAlpha(0, Fill->h - BorderTR->h, BorderBL, Fill);
            Graphics::ApplyAlpha(Fill->w - BorderTR->w, Fill->h - BorderTR->h, BorderBR, Fill);

            Graphics::HalfAlpha(Fill);
            Graphics::HalfAlpha(Fill);

            Graphics::ApplySurface(X, Y, Fill, Surface);

            SDL_FreeSurface(Fill);
            break;
        }

        case ButtonTypeBlock:
        {
            if(!(Hovered && Down))
                return;

            SDL_Surface* Fill = SDL_CreateRGBSurface(0, Width, Height, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);

            SDL_FillRect(Fill, 0, SDL_MapRGB(Fill->format, 0, 0, 0));

            if(!Down)
                Graphics::HalfAlpha(Fill);

            Graphics::HalfAlpha(Fill);

            Graphics::ApplySurface(X, Y, Fill, Surface);

            SDL_FreeSurface(Fill);
            break;
        }
    }
}
