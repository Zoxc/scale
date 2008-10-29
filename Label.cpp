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

#include "Label.hpp"

Label::Label(Element* Owner, std::string ACaption, Resources::Font* AFont, unsigned int AColor) :
    Element::Element(Owner),
    Font(AFont),
    Color(AColor)
{
    Caption = ACaption;

    Font->Size(Caption, &Width, &Height);
}

Label::~Label()
{

}

void Label::Draw(int X, int Y, unsigned char Alpha)
{
    if(Color == ColorBlack)
    {
        Font->Print(Caption, ColorWhite, X + 1, Y + 1, Alpha / 2);
        Font->Print(Caption, ColorBlack, X, Y, Alpha);
    }
    else if(Color == ColorWhite)
    {
        Font->Print(Caption, ColorBlack, X + 2, Y + 2, Alpha / 2);
        Font->Print(Caption, ColorWhite, X, Y, Alpha);
    }
    else
        Font->Print(Caption, Color, X, Y, Alpha);
}
