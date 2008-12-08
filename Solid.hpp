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

#include "Element.hpp"
//#define SolidEffects

namespace Scale
{
    class Solid:
        public Element
    {
        public:
            Solid(Element* AOwner);
            virtual ~Solid();

            #ifdef SolidEffects
                int Step;
                int Position;
                int Max;

                Solid* Test;

                bool Up;

                void Fade();
                void MouseDown(int X, int Y, bool Hovered);
                void MouseUp(int X, int Y, bool Hovered);
                void Animate(int Delta);
            #endif

            unsigned char R;
            unsigned char G;
            unsigned char B;

            void Draw(int X, int Y, unsigned char Alpha);
    };
};
