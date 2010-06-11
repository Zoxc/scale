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

    Known bugs:
        - Position to item index doesn't work right on horizontal right to left mode.
*/

#pragma once
#include <string>
#include <vector>

#include "Element.hpp"
#include "Graphics.hpp"
#include "Label.hpp"
#include "Scroller.hpp"

#define RightToLeftEnabled

namespace Scale
{
    class List;

    struct ListItem
    {
        void* Data;
        const char* Caption;
        OpenGL::Texture* Icon;
        Font::Buffer *Buffer;

        // Coordinates
        unsigned char CoordCaption;
        unsigned char CoordIcon;
    };

    typedef void (*ListKeyDown)(List* Owner, ElementKey Key);
    typedef void (*ListItemEvent)(List* Owner, ListItem* Item);

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

            void Activate();
            void Deactivate();
            void Allocate();
            void Deallocate();
            void Draw(int X, int Y, unsigned char Alpha);
            void KeyDown(ElementKey Key);
            void MouseUp(int X, int Y, bool Hovered);
            void MouseMove(int X, int Y, bool Hovered);
            void MouseDown(int X, int Y, bool Hovered);
            void Animate(int Delta);

            void Target(int NewTarget);
            void TargetFocused();

            inline int GetItemIndex(ListItem* Item);

            ListItem* Focused;
            ListItem* Items;

            ListKeyDown OnKeyDown;

            ListItemEvent OnItemCreate;
            ListItemEvent OnItemFree;

            ListItemEvent OnItemAllocate;
            ListItemEvent OnItemDeallocate;

            bool Focus(int Index, bool ScrollTo);
            void SetCount(int NewCount);

            DrawExtensionOptions DrawExtension;

            IconPlacement Icons;
            bool Captions;

            #ifdef RightToLeftEnabled
                bool RightToLeft;
            #endif

            void SetMessage(const char* NewMessage);

            void Refresh();

            ScrollDirection Direction;

            Font* ItemFont;

            void* Tag;

            int Position;
            int Min;
            int Max;

            int IconSpacing;
            int Columns;
            int Rows;
            int Count;

        private:
            std::string Message;

            int FocusedIndex;
            inline void DrawItem(ListItem* Item, int X, int Y, unsigned char Alpha);

            void AttachScrollbar();
            void DeattachScrollbar();

            void CalculateMax();

            Scroller* Scrollbar;

            unsigned char CaptionY;
            unsigned char IconY;

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

            int MessageTop;
            int MessageLeft;

            bool Activated;
    };

    inline int List::GetItemIndex(ListItem* Item)
    {
        return ((size_t)Item - (size_t)Items) / sizeof(ListItem);
    }

    inline void List::DrawItem(ListItem* Item, int X, int Y, unsigned char Alpha)
    {
        if(Item == Focused)
        {
            if(Activated)
                Graphics::RoundRect(X, Y, ItemWidth, ItemHeight, 0, 0, 0, Alpha * 7 / 20);
            else
                Graphics::RoundRect(X, Y, ItemWidth, ItemHeight, 0, 0, 0, Alpha * 3 / 20);
        }

        if(Icons != IconNone)
            Graphics::Texture(Item->Icon, X + Item->CoordIcon, Y + IconY, Alpha);

        if(Captions)
        {
            Item->Buffer->Print(ColorBlack, X + Item->CoordCaption + 1, Y + CaptionY + 1, Alpha / 2);
            Item->Buffer->Print(ColorWhite, X + Item->CoordCaption, Y + CaptionY, Alpha);
        }
    }
};
