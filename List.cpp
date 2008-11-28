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

#include <math.h>

#include "List.hpp"
#include "Label.hpp"
#include "Resources.hpp"
#include "Graphics.hpp"

namespace Scale
{
    List::List(Element* Owner):
        Element::Element(Owner),
        Focused(0),
        OnItemAllocate(0),
        OnItemImage(0),
        OnItemString(0),
        OnItemFree(0),
        IconSpacing(4),
        Columns(4),
        Rows(3),
        FocusedIndex(-1),
        Items(0),
        Count(0),
        ItemData(sizeof(ListItem)),
        Position(0),
        Min(0),
        Mode(0),
        Allocated(false),
        Released(true),
        Animated(false)
    {
    }

    List::~List()
    {
    }

    const float Limit = 300;

    void List::Target(int X)
    {
        Released = false;

        if(!Animated)
        {
            Start();
            Animated = true;
        }

        PositionStart = Position;

        Step = 0;

        PositionTarget = X;

        // Smooth bounds
        /*
        if(PositionStart + (PositionTarget - PositionStart) < Min)
        {
            PositionTarget = Min;
        }

        if(PositionStart + (PositionTarget - PositionStart) > 0)
        {
            PositionTarget = 0;
        }
        */
        Velocity = PositionTarget - PositionStart;
    }

    void List::Animate(int Delta)
    {
        Step += Delta;

        if(Released)
        {
            if(Step >= 1000)
            {
                Step = 1000;
                Animated = false;
                Stop();
            }
        }
        else
        {
            if(Step >= 200)
            {
                Step = 200;
                Animated = false;
                Stop();
            }
        }

        int NewPosition;

        if(Released)
            NewPosition = PositionStart + (int)floor(Velocity * 1000.f / 200.f * sin(Step / 1000.f * M_PI_2));
        else
            NewPosition = PositionStart + (int)floor(Velocity * sin(Step / 200.f * M_PI_2));

        if(NewPosition < Min)
            NewPosition = Min;
        else if(NewPosition > 0)
            NewPosition = 0;

        if(Position != NewPosition)
        {
            Position = NewPosition;
            Redraw();
        }
    }

    void List::MouseUp(int X, int Y, bool Hovered)
    {
        Released = true;

        PositionStart = Position;

        Velocity = float(PositionTarget - PositionStart) * (1 - sin(Step / 200.f * M_PI_2));

        if(Velocity > Limit)
            Velocity = Limit;
        else if(Velocity < -Limit)
            Velocity = -Limit;

        Step = 0;

        if(Screen->Captured == this)
            Release();

        Mode = 0;

        Element::MouseUp(X, Y, Hovered);
    }

    void List::MouseDown(int X, int Y, bool Hovered)
    {
        if(Hovered)
        {
            Root->Focus(this);

            int Column = (X - Position) / ItemWidth;
            int Row = Y / ItemHeight;
            int Index = Column * Rows + Row;

            if(Index < Count)
            {
                ListItem* NewFocus = GetItem(Index);

                if(NewFocus != Focused)
                {
                    FocusedIndex = Index;
                    Focused = NewFocus;
                    Redraw();
                }
            }

            Capture();

            Mode = 1;
            DownX = X;
            MoveOffset = X - Position;
            Target(X - MoveOffset);
        }

        Element::MouseDown(X, Y, Hovered);
    }

    void List::MouseMove(int X, int Y, bool Hovered)
    {
        if(Mode == 1)
           // if(abs(X - DownX) > 15)
                Mode = 2;

        if(Mode > 1)
            Target(X - MoveOffset);

        Element::MouseMove(X, Y, Hovered);
    }

    void List::TargetFocused()
    {
        if(-Position > Focused->X)
        {
            Target(-Focused->X);
        }
        else if(Width < Focused->X + ItemWidth + Position)
        {
            Target(-Focused->X + Width - ItemWidth);
        }
    }

    void List::KeyDown(ElementKey Key)
    {
        int NewIndex = FocusedIndex;

        switch((int)Key)
        {
            case ElementUp:
                if(FocusedIndex % Rows != 0)
                    NewIndex--;
                break;

            case ElementDown:
                if(FocusedIndex % Rows != Rows - 1)
                    NewIndex++;
                break;

            case ElementLeft:
                if(FocusedIndex > Rows - 1)
                    NewIndex -= Rows;
                break;

            case ElementRight:
                NewIndex += Rows;

                if(NewIndex + 1 > (int)Count)
                    NewIndex = Count - 1;
                break;

        }

        if(NewIndex < (int)Count && NewIndex != FocusedIndex)
        {
            FocusedIndex = NewIndex;
            Focused = GetItem(FocusedIndex);
            TargetFocused();
            Redraw();
        }
    }

    void List::SetFocused(ListItem* Item)
    {
        if(Item == 0)
            return;

        if(Focused != Item)
        {
            FocusedIndex = GetItemIndex(Item);
            Focused = Item;

            Redraw();
        }
    }

    void List::SetItemData(int Size)
    {
        ItemData = sizeof(ListItem) + Size;
    }

    void List::SetCount(int NewCount)
    {
        if(NewCount == Count || NewCount < 0)
            return;

        if(Count > NewCount)
        {
            for (int i = NewCount; i < Count; i++)
            {
                ListItem* Item = GetItem(i);

                if(Allocated)
                    OnItemFree(this, Item);
            }
        }

        if(Items != 0)
            Items = (char*)realloc(Items, NewCount * ItemData);
        else
            Items = (char*)malloc(NewCount * ItemData);

        if(Count < NewCount)
        {
            for (int i = Count; i < NewCount; i++)
            {
                ListItem* Item = GetItem(i);

                if(Allocated)
                    OnItemAllocate(this, Item);
            }
        }

        Count = NewCount;
    }

    void List::Allocate()
    {
        Element::Allocate();

        Allocated = true;

        for (int i = 0; i < Count; i++)
        {
            ListItem* Item = GetItem(i);

            OnItemAllocate(this, Item);
        }

        if(FocusedIndex == -1 && Count > 0)
        {
            FocusedIndex = 0;
            Focused = GetItem(0);
        }

        ItemHeight = Height / Rows;
        ItemWidth = Width / Columns;

        if(Count % Rows > 0)
            Min = Count / Rows + 1;
        else
            Min = Count / Rows;

        Min = (Min * ItemWidth - Width);

        if(Min < 0)
            Min = 0;
        else
            Min *= -1;

        int ItemX = 0;
        int ItemY = 0;

        const int IconSize = 64;
        const int FontSize = 19;

        _IconLeft = ItemWidth - IconSize >> 1;
        _IconTop = ItemHeight - IconSize - IconSpacing - FontSize >> 1;
        _CaptionTop = _IconTop + IconSize + IconSpacing;

        for (int i = 0; i < Count; i++)
        {
            ListItem* Item = GetItem(i);

            const char* Caption = OnItemString(this, Item);

            int FontWidth = 0;
            int FontHeight = 0;

            if(Caption != 0)
                Resources::FontSmall->Size(Caption, &FontWidth, &FontHeight);

            Item->X = ItemWidth * ItemX;
            Item->Y = ItemHeight * ItemY;

            Item->CaptionLeft = ItemWidth - FontWidth >> 1;

            ItemY++;

            if(ItemY == Rows)
            {
                ItemY = 0;
                ItemX++;
            }
        }
    }

    void List::Deallocate()
    {
        Element::Deallocate();

        Allocated = false;

        for (int i = 0; i < Count; i++)
        {
            ListItem* Item = GetItem(i);

            OnItemFree(this, Item);
        }
    }

    void List::Draw(int X, int Y, unsigned char Alpha)
    {
        int ClientItemLeft = X + Position;
        int ClientItemTop = Y;
        int Row = 0;

        for (int i = 0; i < Count; i++)
        {
            if(ClientItemLeft < -ItemWidth)
                goto Continue;

            ListItem* Item = GetItem(i);

            if(Focused == Item)
                Graphics::RoundRect(ClientItemLeft, ClientItemTop, ItemWidth, ItemHeight, 255, 255, 255, Alpha / 3);

            OpenGL::Texture* Icon = OnItemImage(this, Item);

            Graphics::Texture(Icon, ClientItemLeft + _IconLeft, ClientItemTop + _IconTop, Alpha);

            const char* Caption = OnItemString(this, Item);

            Resources::FontSmall->Print(Caption, ColorWhite, ClientItemLeft + Item->CaptionLeft + 1, ClientItemTop + _CaptionTop + 1, Alpha / 3);
            Resources::FontSmall->Print(Caption, ColorBlack, ClientItemLeft + Item->CaptionLeft, ClientItemTop + _CaptionTop, Alpha);

            Continue:
                Row++;
                ClientItemTop += ItemHeight;

                if(Row >= Rows)
                {
                    Row = 0;
                    ClientItemTop = Y;

                    ClientItemLeft += ItemWidth;

                    if(ClientItemLeft > Width)
                        break;
                }
        }
    }
};
