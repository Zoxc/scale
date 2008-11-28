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
    class List;

    struct ListItem
    {
        unsigned short X;
        unsigned short Y;
        unsigned char CaptionLeft;
    };

    typedef void (*ListItemAllocate)(List* Owner, ListItem* Item);
    typedef OpenGL::Texture* (*ListItemImage)(List* Owner, ListItem* Item);
    typedef const char* (*ListItemString)(List* Owner, ListItem* Item);
    typedef void (*ListItemFree)(List* Owner, ListItem* Item);

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

            inline ListItem* GetItem(int Index);
            inline int GetItemIndex(ListItem* Item);
            inline void* GetItemData(ListItem* Item);

            ListItem* Focused;

            ListItemAllocate OnItemAllocate;
            ListItemImage OnItemImage;
            ListItemString OnItemString;
            ListItemFree OnItemFree;

            void SetFocused(ListItem* Item);
            void SetCount(int NewCount);
            void SetItemData(int Size);

            int IconSpacing;
            int Columns;
            int Rows;

        private:
            int FocusedIndex;
            char* Items;
            int Count;
            int ItemData;

            int _IconLeft;
            int _IconTop;
            int _CaptionTop;

            int Position;
            int Min;

            void Target(int X);
            void TargetFocused();

            int DownX;
            unsigned char Mode;
            int MoveOffset;

            bool Allocated;
            bool Released;
            bool Animated;
            int Step;
            float Velocity;
            int PositionStart;
            int PositionTarget;
            int ItemHeight;
            int ItemWidth;
    };

    inline ListItem* List::GetItem(int Index)
    {
        return (ListItem*)(Items + Index * ItemData);
    }

    inline int List::GetItemIndex(ListItem* Item)
    {
        return ((unsigned int)Item - (unsigned int)Items) / ItemData;
    }

    inline void* List::GetItemData(ListItem* Item)
    {
        return (void*)((char*)Item + sizeof(ListItem));
    }
};
