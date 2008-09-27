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

class Button:
    public Element
{
    public:
        Button(Element* Owner);
        virtual ~Button();

        void Draw(SDL_Surface* Surface, int X, int Y, unsigned char Alpha);
        void Activate();
        void Deactivate();
        void MouseEnter();
        void MouseLeave();
        void MouseUp(int X, int Y, bool Status);
        void MouseDown(int X, int Y, Element** NewFocus, bool Status);

        bool Down;
        SDL_Surface* Fill;
};
