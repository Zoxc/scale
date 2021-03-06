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

#include "Graphics.hpp"
#include "Scroller.hpp"

namespace Scale
{
    Scroller::Scroller(Element* AOwner) :
        Element(AOwner)
    {
    }

    Scroller::~Scroller()
    {
    }

    void Scroller::Draw(int X, int Y, unsigned char Alpha)
    {
        glEnable(GL_SCISSOR_TEST);
        glScissor(X, Screen->Height - Y - Height, Width, Height);

        Graphics::RoundRect(X - 10, Y, Width + 10, Height, 0, 0, 0, Alpha / 8);

        glDisable(GL_SCISSOR_TEST);

        int RSize = Size * Height / (Size + Max);

        if(RSize < 20)
            RSize = 20;

        int RY = (Height - RSize) * Position / Max;

        Graphics::RoundRect(X, Y + RY, Width, RSize, 0, 0, 0, Alpha * 7 / 20);
    }
};
