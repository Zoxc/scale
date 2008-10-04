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

#include <math.h>

#include "CategoryScroller.hpp"

CategoryScroller::CategoryScroller(Element* AOwner):
    Element::Element(AOwner)
{
    Velocity = 0;
}

CategoryScroller::~CategoryScroller()
{
}

void CategoryScroller::Target(int X)
{
    Start();

    StartX = Left;
    Step = 0;
    TargetX = X;
    Released = false;
    Velocity += ((float)TargetX - (float)StartX) / 1600;
}

void CategoryScroller::ReleaseTarget()
{
}

void CategoryScroller::Animate(int Delta)
{
    Step += Delta * Velocity;

    Velocity = Velocity / 1.02;

    Left = StartX + (int)floor(Step);

    Redraw();
}
