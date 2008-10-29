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
#include <string>
#include "Resources.hpp"
#include "Element.hpp"

const unsigned int ColorBlack = 0;
const unsigned int ColorWhite = 0xFFFFFFFF;

class Label:
    public Element
{
    public:
        Label(Element* Owner, std::string ACaption, Resources::Font* AFont, unsigned int AColor);
        virtual ~Label();

        void Draw(int X, int Y, unsigned char Alpha);

        Resources::Font* Font;
        unsigned int Color;

        std::string Caption;
};
