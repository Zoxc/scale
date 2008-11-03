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
#include "Switcher.hpp"

namespace Scale
{
    Switcher::Switcher(Element* AOwner) : Element::Element(AOwner)
    {
    }

    Switcher::~Switcher()
    {
    }

    void Switcher::Allocate()
    {
        Element::Allocate();
    }

    void Switcher::Deallocate()
    {
        Element::Deallocate();
    }

    void Switcher::Draw(int X, int Y, unsigned char Alpha)
    {
        Graphics::Rect(X, Y, Width, Height, 255, 255, 255, Alpha / 2);
    }
};
