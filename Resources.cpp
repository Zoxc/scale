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
#include "Resources.hpp"

namespace Resources
{
    FT_Library FreeType;

    FT_Face FontSmall = 0;
    FT_Face FontNormal = 0;
    FT_Face FontBig = 0;
};

void Resources::Allocate()
{
    FT_Init_FreeType(&FreeType);

    FT_New_Face(FreeType, "resources/FreeSans.ttf", 0, &FontSmall);
    FT_Set_Char_Size(FontSmall, 0, 16 * 64, 96, 96);  // 19pt

    FT_New_Face(FreeType, "resources/FreeSans.ttf", 0, &FontNormal);
    FT_Set_Char_Size(FontNormal, 0, 18 * 64, 96, 96); // 22pt

    FT_New_Face(FreeType, "resources/FreeSans.ttf", 0, &FontBig);
    FT_Set_Char_Size(FontBig, 0, 20 * 64, 96, 96);    // 24pt
}

void Resources::Deallocate()
{
    FT_Done_Face(FontSmall);

    FT_Done_Face(FontNormal);

    FT_Done_Face(FontBig);
}
