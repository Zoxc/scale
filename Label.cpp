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

namespace Scale
{
    Label::Label(Element* Owner, std::string ACaption, Font* AFont, unsigned int AColor) :
        Element(Owner),
        LabelFont(AFont),
        Color(AColor)
    {
        Caption = ACaption;

        Width = LabelFont->Size(ACaption.c_str(), &Height);
    }

    Label::~Label()
    {

    }

    void Label::Draw(int X, int Y, unsigned char Alpha)
    {
        if(Color == ColorBlack)
        {
            LabelFont->Print(Caption.c_str(), ColorWhite, X + 1, Y + 1, Alpha / 3);
            LabelFont->Print(Caption.c_str(), ColorBlack, X, Y, Alpha);
        }
        else if(Color == ColorWhite)
        {
            LabelFont->Print(Caption.c_str(), ColorBlack, X + 2, Y + 2, Alpha / 2);
            LabelFont->Print(Caption.c_str(), ColorWhite, X, Y, Alpha);
        }
        else
            LabelFont->Print(Caption.c_str(), Color, X, Y, Alpha);
    }
};
