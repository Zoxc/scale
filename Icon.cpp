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

#include "Icon.hpp"
#include "Resources.hpp"


Icon::Icon(Element* Owner) :
    Button(Owner),
    Focused(false)
{
}

Icon::~Icon()
{
}

void Icon::Click()
{
}

void Icon::Allocate()
{
    Element::Allocate();
}

void Icon::Deallocate()
{
    Element::Deallocate();
}

void Icon::Activate()
{
    Focused = true;

    Redraw();
}

void Icon::Deactivate()
{
    Focused = false;

    Redraw();
}

void Icon::Draw(int X, int Y, unsigned char Alpha)
{
    if(!Focused)
        return;

    GLshort Positions[] = {
        X, Y + Height,
        X, Y,
        X + Width, Y + Height,
        X + Width, Y
    };

    glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, 0, Positions);
    glUniform1i(Screen->TexturedUniform, 0);
    glUniform4f(Screen->ColorUniform, 1, 1, 1, Alpha / 255.0f / 4);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
