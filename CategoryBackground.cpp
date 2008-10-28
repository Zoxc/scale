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

#include "CategoryBackground.hpp"
#include "Button.hpp"
#include "Graphics.hpp"

CategoryBackground::CategoryBackground(Element* AOwner):
    Element::Element(AOwner)
{
    AlphaBlend = 0;
    Step = 0;
}

CategoryBackground::~CategoryBackground()
{
}

void CategoryBackground::Allocate()
{
    Element::Allocate();
}

void CategoryBackground::Deallocate()
{
    Element::Deallocate();
}

void CategoryBackground::Up()
{
    Start();
    Show();

    Upping = true;
    Top = 480 - (int)floor(sin(((float)Step / 1000) * M_PI_2) * 480);
    AlphaBlend = Step * 255 / 1000;

    Redraw();
}

void CategoryBackground::Down()
{
    Upping = false;

    Start();
}

void CategoryBackground::Animate(int Delta)
{
    if(Upping)
        Step += Delta * 3;
    else
        Step -= Delta * 3;

    if(Step <= 0)
    {
        Step = 0;
        Stop();
        Hide();
    }
    else if(Step >= 1000)
    {
        Step = 1000;
        Stop();
    }

    Top = 480 - (int)floor(sin(((float)Step / 1000) * M_PI_2) * 480);
    AlphaBlend = Step * 255 / 1000;

    Redraw();
}

void CategoryBackground::Draw(int X, int Y, unsigned char Alpha)
{
    Graphics::Rect(X, Y, Width, Height, 150, 150, 150,  Alpha / 10 * 9);
}
