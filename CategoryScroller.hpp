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

class CategoryScroller:
    public Element
{
    public:
        CategoryScroller(Element* AOwner);
        virtual ~CategoryScroller();

        void Target(int X);
        void ReleaseTarget();
        void Animate(int Delta);

        bool Released;
        int Step;
        int LeftTarget;
        int LeftStart;
        float Velocity;
};
