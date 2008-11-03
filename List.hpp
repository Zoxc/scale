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
#include <vector>

#include "Element.hpp"

namespace Scale
{
    struct ListItem
    {
        std::string Caption;
        std::string Icon;

        OpenGL::Texture* IconTexture;
        OpenGL::Texture* CaptionTexture;

        unsigned short X;
        unsigned short Y;
        unsigned short CaptionX;
        unsigned short CaptionY;
        unsigned short IconX;
        unsigned short IconY;
    };

    enum IconPlacement
    {
        IconNone,
        IconLeft,
        IconRight,
        IconAbove,
        IconBelow
    };

    class List:
        public Element
    {
        public:
            List(Element* Owner);
            virtual ~List();

            void Allocate();
            void Deallocate();
            void Draw(int X, int Y, unsigned char Alpha);
            void KeyDown(ElementKey Key);
            void MouseUp(int X, int Y, bool Hovered);
            void MouseMove(int X, int Y, bool Hovered);
            void MouseDown(int X, int Y, bool Hovered);
            void Animate(int Delta);

            void Add(std::string Icon, std::string Caption);

            std::vector<ListItem*> Items;

            ListItem* Focused;

            IconPlacement Icons;
            bool Captions;

            int IconSpacing;
            int Columns;
            int Rows;

        private:
            int FocusedIndex;

            int Position;
            int Min;

            void Target(int X);
            void TargetFocused();

            int DownX;
            unsigned char Mode;
            int MoveOffset;

            bool Released;
            bool Animated;
            int Step;
            float Velocity;
            int PositionStart;
            int PositionTarget;
            int ItemHeight;
            int ItemWidth;
    };
};
