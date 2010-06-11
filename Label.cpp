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
        Buffer(0),
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
        if(!Buffer)
            Buffer = LabelFont->AllocBuffer(Caption.c_str());

        if(Color == ColorBlack)
        {
            Buffer->Print(ColorWhite, X + 1, Y + 1, Alpha / 3);
            Buffer->Print(ColorBlack, X, Y, Alpha);
        }
        else if(Color == ColorWhite)
        {
            Buffer->Print(ColorBlack, X + 2, Y + 2, Alpha / 2);
            Buffer->Print(ColorWhite, X, Y, Alpha);
        }
        else
            Buffer->Print(Color, X, Y, Alpha);
    }
};
