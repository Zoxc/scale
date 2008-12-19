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

#include <vector>
#include "Element.hpp"
#include "Font.hpp"

namespace Scale
{
    struct VerticalBarItem
    {
        void* Data;
        const char* Caption;
        const char* IconPath;
        OpenGL::Texture* Icon;

        short IconCurrent;
        short IconStart;
        short IconTarget;
        unsigned char IconStep;

        unsigned char Step;

        int IconTop;
        int Start;
        int Current;
        int Target;
        unsigned short CaptionLeft;
    };

    class VerticalBar:
        public Element
    {
        public:
            VerticalBar(Element* AOwner);
            virtual ~VerticalBar();

            void Focus(VerticalBarItem* Item);


            void Allocate();
            void Deallocate();
            void MouseDown(int X, int Y, bool Hovered);
            void KeyDown(ElementKey Key);
            void Draw(int X, int Y, unsigned char Alpha);
            void Activate();
            void Deactivate();
            void Animate(int Delta);

            void Refresh(bool Initial);

            int ItemHeight;
            int FontTop;
            int IconLeft;

            bool Animating;
            bool Activated;

            unsigned char Step;

            int FocusedStart;
            int FocusedCurrent;
            int FocusedTarget;

            VerticalBarItem* Focused;

            std::vector<VerticalBarItem*> Items;

            Font* ItemFont;
    };
};
