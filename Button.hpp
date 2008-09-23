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

#pragma once
#include "SDL.h"
#include "SDL_image.h"

#include "Element.hpp"

enum ButtonType
{
    ButtonTypePush, ButtonTypeBlock
};

class Button:
    public Element
{
    public:
        Button(Element* AOwner, ButtonType type);
        virtual ~Button();

        void OnDraw(SDL_Surface* Surface, int X, int Y);

        void OnActivate();
        void OnDeactivate();
        void OnMouseEnter();
        void OnMouseLeave();
        void OnMouseUp(int X, int Y);
        void OnMouseDown(int X, int Y);

        bool Down;
        bool Over;
        ButtonType Type;
        SDL_Surface* ImageSurface;
};
