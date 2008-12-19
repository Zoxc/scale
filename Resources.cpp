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
        #ifndef NO_FREETYPE
        FT_Library FreeType;
        #endif

        OpenGL::Texture* RoundCornerTopLeft;
        OpenGL::Texture* RoundCornerTopRight;
        OpenGL::Texture* RoundCornerBottomLeft;
        OpenGL::Texture* RoundCornerBottomRight;

        AdvancedFont* FontSmallAdv;

        Font* FontSmall;
        Font* FontNormal;
        Font* FontBig;

        void Init()
        {
            #ifndef NO_FREETYPE
            FT_Init_FreeType(&FreeType);
            #endif

            RoundCornerTopLeft = new OpenGL::Texture();
            RoundCornerTopRight = new OpenGL::Texture();
            RoundCornerBottomLeft = new OpenGL::Texture();
            RoundCornerBottomRight = new OpenGL::Texture();

            FontSmallAdv = new AdvancedFont("resources/FreeSans.ttf", "resources/FreeSansBold.ttf", 16); // 19pt

            FontSmall = new Font("resources/FreeSans.ttf", 16); // 19pt
            FontNormal = new Font("resources/FreeSans.ttf", 18); // 22pt
            FontBig = new Font("resources/FreeSans.ttf", 14); // 24pt
        }

        void Allocate()
        {
            RoundCornerTopLeft->Load("resources/border_tl.png");
            RoundCornerTopRight->Load("resources/border_tr.png");
            RoundCornerBottomLeft->Load("resources/border_bl.png");
            RoundCornerBottomRight->Load("resources/border_br.png");

            FontSmallAdv->Allocate();

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

            delete FontSmallAdv;

            delete FontSmall;
            delete FontNormal;
            delete FontBig;
        }
    };
};
