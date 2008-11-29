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
#include "Resources.hpp"
#include "Graphics.hpp"
#include "Label.hpp"

namespace Scale
{
    class List;

    struct ListItem
    {
        unsigned short X;
        unsigned short Y;

        unsigned char CaptionX;
        unsigned char CaptionY;
        unsigned char IconX;
        unsigned char IconY;

        void* Data;
    };

    typedef void (*ListItemAllocate)(List* Owner, ListItem* Item);
    typedef OpenGL::Texture* (*ListItemImage)(List* Owner, ListItem* Item);
    typedef const char* (*ListItemString)(List* Owner, ListItem* Item);
    typedef void (*ListItemFree)(List* Owner, ListItem* Item);

    class List:
        public Element
    {
        public:
            enum IconPlacement
            {
                IconNone,
                IconLeft,
                IconRight,
                IconAbove,
                IconBelow
            };

            enum ScrollDirection
            {
                Vertical,
                Horizontal
            };

            struct DrawExtensionOptions
            {
                bool Enable;
                int Start;
                int End;
            };


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

            inline int GetItemIndex(ListItem* Item);

            ListItem* Focused;
            ListItem* Items;

            ListItemAllocate OnItemAllocate;
            ListItemImage OnItemImage;
            ListItemString OnItemString;
            ListItemFree OnItemFree;

            void SetFocused(ListItem* Item);
            void SetCount(int NewCount);

            DrawExtensionOptions DrawExtension;

            IconPlacement Icons;
            bool Captions;
            bool RightToLeft;
            ScrollDirection Direction;

            int IconSpacing;
            int Columns;
            int Rows;

        private:
            int FocusedIndex;
            int Count;

            int Position;
            int Min;

            void Target(int NewTarget);
            void TargetFocused();

            inline void SetupItem(ListItem* Item, int ItemX, int ItemY);
            inline void DrawItem(ListItem* Item, int X, int Y, unsigned char Alpha);

            int TargetDown;
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

    inline int List::GetItemIndex(ListItem* Item)
    {
        return ((unsigned int)Item - (unsigned int)Items) / sizeof(ListItem);
    }

    inline void List::SetupItem(ListItem* Item, int ItemX, int ItemY)
    {
        const int IconSize = 64;
        const int FontSize = 19;

        int FontWidth = 0;
        int FontHeight = 0;

        if(Captions)
        {
            const char* Caption = OnItemString(this, Item);

            if(Caption != 0)
                Resources::FontSmall->Size(Caption, &FontWidth, &FontHeight);
        }

        Item->X = ItemWidth * ItemX;
        Item->Y = ItemHeight * ItemY;

        if(Captions == false)
        {
            Item->IconX = ItemWidth - IconSize >> 1;
            Item->IconY = ItemHeight - IconSize >> 1;
        }
        else
            switch(Icons)
            {
                case IconNone:
                    Item->CaptionX = ItemWidth - FontWidth >> 1;
                    Item->CaptionY = ItemHeight - FontHeight >> 1;
                    break;

                case IconLeft:
                    Item->IconX = ItemWidth - IconSize - IconSpacing - FontWidth >> 1;
                    Item->IconY = ItemHeight - IconSize >> 1;

                    Item->CaptionX = Item->IconX + IconSize + IconSpacing;
                    Item->CaptionY = ItemHeight - FontHeight >> 1;
                    break;

                case IconRight:
                    Item->CaptionX = ItemWidth - IconSize - IconSpacing - FontWidth >> 1;
                    Item->CaptionY = ItemHeight - FontHeight >> 1;

                    Item->IconX = Item->CaptionX + FontWidth + IconSpacing;
                    Item->IconY = ItemHeight - IconSize >> 1;
                    break;

                case IconAbove:
                    Item->IconX = ItemWidth - IconSize >> 1;
                    Item->IconY = ItemHeight - IconSize - IconSpacing - FontSize >> 1;

                    Item->CaptionX = ItemWidth - FontWidth >> 1;
                    Item->CaptionY = Item->IconY + IconSize + IconSpacing;
                    break;

                case IconBelow:
                    Item->CaptionX = ItemWidth - FontWidth >> 1;
                    Item->CaptionY = ItemHeight - IconSize - IconSpacing - FontSize >> 1;

                    Item->IconX = ItemWidth - IconSize >> 1;
                    Item->IconY = Item->CaptionY + FontSize + IconSpacing;
                    break;
            }
    }

    inline void List::DrawItem(ListItem* Item, int X, int Y, unsigned char Alpha)
    {
        if(Focused == Item)
            Graphics::RoundRect(X, Y, ItemWidth, ItemHeight, 255, 255, 255, Alpha / 3);

        if(Icons != IconNone)
        {
            OpenGL::Texture* Icon = OnItemImage(this, Item);

            Graphics::Texture(Icon, X + Item->IconX, Y + Item->IconY, Alpha);
        }

        if(Captions)
        {
            const char* Caption = OnItemString(this, Item);

            Resources::FontSmall->Print(Caption, ColorWhite, X + Item->CaptionX + 1, Y + Item->CaptionY + 1, Alpha / 3);
            Resources::FontSmall->Print(Caption, ColorBlack, X + Item->CaptionX, Y + Item->CaptionY, Alpha);
        }
    }
};
