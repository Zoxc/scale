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

const float Limit = 400;

void CategoryScroller::Target(int X)
{
    Start();

    LeftStart = Left;

    Step = 0;

    LeftTarget = X;

    Velocity = LeftTarget - LeftStart;

    if(Velocity > Limit)
        Velocity = Limit;
    else if(Velocity < -Limit)
        Velocity = -Limit;

    Released = false;
}

void CategoryScroller::ReleaseTarget()
{
    Released = true;

    LeftStart = Left;

    Velocity = float(LeftTarget - LeftStart) * (1 - sin(Step / 200.f * M_PI_2));

    if(Velocity > Limit)
        Velocity = Limit;
    else if(Velocity < -Limit)
        Velocity = -Limit;

    Step = 0;
}

void CategoryScroller::Animate(int Delta)
{
    Step += Delta;

    if(Released)
    {
        if(Step >= 1000)
        {
            Step = 1000;
            Stop();
        }
    }
    else
    {
        if(Step >= 200)
        {
            Step = 200;
            Stop();
        }
    }

    if(Released)
    {
        float AVelocity = Velocity *  1000.f / 200.f * sin(Step / 1000.f * M_PI_2);
        Left = LeftStart + (int)floor((AVelocity));
    }
    else
        Left = LeftStart + (int)floor(Velocity * sin(Step / 200.f * M_PI_2));

    Redraw();
}
