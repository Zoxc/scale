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

#include <algorithm>

#include "Resources.hpp"

namespace Scale
{
    namespace Resources
    {
        //FT_Library FreeType;

        OpenGL::Texture* RoundCornerTopLeft;
        OpenGL::Texture* RoundCornerTopRight;
        OpenGL::Texture* RoundCornerBottomLeft;
        OpenGL::Texture* RoundCornerBottomRight;

        Font* FontSmall;
        Font* FontNormal;
        Font* FontBig;

        void Init()
        {
            //FT_Init_FreeType(&FreeType);

            RoundCornerTopLeft = new OpenGL::Texture();
            RoundCornerTopRight = new OpenGL::Texture();
            RoundCornerBottomLeft = new OpenGL::Texture();
            RoundCornerBottomRight = new OpenGL::Texture();

            FontSmall = new Font("resources/FreeSans.ttf", 16); // 19pt
            FontNormal = new Font("resources/FreeSans.ttf", 18); // 22pt
            FontBig = new Font("resources/FreeSans.ttf", 20); // 24pt
        }

        void Allocate()
        {
            RoundCornerTopLeft->Load("resources/border_tl.png");
            RoundCornerTopRight->Load("resources/border_tr.png");
            RoundCornerBottomLeft->Load("resources/border_bl.png");
            RoundCornerBottomRight->Load("resources/border_br.png");

            FontSmall->Allocate();
            FontNormal->Allocate();
            FontBig->Allocate();
        }

        void Deallocate()
        {
            delete RoundCornerTopLeft;
            delete RoundCornerTopRight;
            delete RoundCornerBottomLeft;
            delete RoundCornerBottomRight;

            delete FontSmall;
            delete FontNormal;
            delete FontBig;
        }
    };
};
