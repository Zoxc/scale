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

namespace Scale
{
    List::List(Element* Owner):
        Element::Element(Owner),
        Focused(0),
        Items(0),
        OnItemCreate(0),
        OnItemImage(0),
        OnItemString(0),
        OnItemFree(0),
        Icons(IconAbove),
        Captions(true),
        RightToLeft(false),
        Direction(Vertical),
        Position(0),
        Min(0),
        Max(0),
        IconSpacing(10),
        Columns(4),
        Rows(3),
        Count(0),
        FocusedIndex(-1),
        Mode(0),
        Allocated(false),
        Released(true),
        Animated(false)
    {
        DrawExtension.Enable = true;
        DrawExtension.Start = 0;
        DrawExtension.End = 0;
    }

    List::~List()
    {
    }

    const float Limit = 300;

    void List::Target(int NewTarget)
    {
        Released = false;

        if(!Animated)
        {
            Start();
            Animated = true;
        }

        PositionStart = Position;

        Step = 0;

        PositionTarget = NewTarget;

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

        if(NewPosition > Max)
            NewPosition = Max;
        else if(NewPosition < 0)
            NewPosition = 0;

        if(Position != NewPosition)
        {
            Position = NewPosition;

            if(Scrollbar != 0)
            {
                Scrollbar->Position = Position;
                Scrollbar->Max = Max;

                if(Direction == Horizontal)
                    Scrollbar->Size = Width;
                else
                    Scrollbar->Size = Height;

                Scrollbar->Redraw();
            }

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

            if(Direction == Horizontal)
            {
                int Column;

                if(RightToLeft)
                    Column = -((X - Position) / ItemWidth - Columns + 1);
                else
                    Column = (X + Position) / ItemWidth;

                int Row = Y / ItemHeight;
                int Index = Column * Rows + Row;

                if(Index < Count)
                {
                    ListItem* NewFocus = &Items[Index];

                    if(NewFocus != Focused)
                    {
                        FocusedIndex = Index;
                        Focused = NewFocus;
                        Redraw();
                    }
                }

                Capture();

                Mode = 1;
                TargetDown = X;
                Target(Position);

                if(RightToLeft)
                    MoveOffset = X - Position;
                else
                    MoveOffset = X + Position;
            }
            else
            {
                int Column;

                if(RightToLeft)
                    Column = Columns - 1 - X / ItemWidth;
                else
                    Column = X / ItemWidth;

                int Row = (Y + Position) / ItemHeight;
                int Index = Row * Columns + Column;

                if(Index < Count)
                {
                    ListItem* NewFocus = &Items[Index];

                    if(NewFocus != Focused)
                    {
                        FocusedIndex = Index;
                        Focused = NewFocus;
                        Redraw();
                    }
                }

                Capture();

                Mode = 1;
                TargetDown = Y;
                MoveOffset = Y + Position;
                Target(Position);
            }
        }

        Element::MouseDown(X, Y, Hovered);
    }

    void List::MouseMove(int X, int Y, bool Hovered)
    {
        if(Mode == 1)
           // if(abs(X - TargetDown) > 15)
                Mode = 2;

        if(Mode > 1)
        {
            if(Direction == Horizontal)
            {
                if(RightToLeft)
                    Target(X - MoveOffset);
                else
                    Target(MoveOffset - X);
            }
            else
                Target(MoveOffset - Y);
        }

        Element::MouseMove(X, Y, Hovered);
    }

    void List::TargetFocused()
    {
        int Index = GetItemIndex(Focused);

        if(Direction == Horizontal)
        {
            int X;

            //if(RightToLeft)
            //    X = (Rows - Index / Rows) * ItemWidth;
            //else
                X = (Index / Rows) * ItemWidth;

            if(Position > X)
            {
                Target(X);
            }
            else if(Position + Width < X + ItemWidth)
            {
                Target(X - Width + ItemWidth);
            }
        }
        else
        {
            int Y = (Index / Columns) * ItemHeight;

            if(Position > Y)
                Target(Y);
            else if(Position + Height < Y + ItemHeight)
            {
                Target(Y - Height + ItemHeight);
            }
        }
    }

    void List::KeyDown(ElementKey Key)
    {
        int NewIndex = FocusedIndex;

        if(Direction == Horizontal)
        {
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
                    if(RightToLeft)
                    {
                        if(NewIndex / Rows != (Count - 1) / Rows)
                        {
                            NewIndex += Rows;

                            if(NewIndex + 1 > (int)Count)
                                NewIndex = Count - 1;
                        }
                    }
                    else
                    {
                        if(FocusedIndex > Rows - 1)
                            NewIndex -= Rows;
                    }
                    break;

                case ElementRight:
                    if(RightToLeft)
                    {
                       if(FocusedIndex > Rows - 1)
                            NewIndex -= Rows;
                    }
                    else
                    {
                        if(NewIndex / Rows != (Count - 1) / Rows)
                        {
                            NewIndex += Rows;

                            if(NewIndex + 1 > (int)Count)
                                NewIndex = Count - 1;
                        }
                    }
                    break;

            }
        }
        else
        {
            switch((int)Key)
            {
                case ElementUp:
                    if(FocusedIndex > Columns - 1)
                        NewIndex -= Columns;
                    break;

                case ElementDown:
                    if(NewIndex / Columns != (Count - 1) / Columns)
                    {
                        NewIndex += Columns;

                        if(NewIndex + 1 > (int)Count)
                            NewIndex = Count - 1;
                    }
                    break;

                case ElementLeft:
                    if(RightToLeft)
                    {
                        if(FocusedIndex % Columns != Columns - 1)
                            NewIndex++;
                    }
                    else
                    {
                        if(FocusedIndex % Columns != 0)
                            NewIndex--;
                    }
                    break;

                case ElementRight:
                    if(RightToLeft)
                    {
                        if(FocusedIndex % Columns != 0)
                            NewIndex--;
                    }
                    else
                    {
                        if(FocusedIndex % Columns != Columns - 1)
                            NewIndex++;
                    }
                    break;
            }
        }

        if(NewIndex < (int)Count && NewIndex != FocusedIndex)
        {
            FocusedIndex = NewIndex;
            Focused = &Items[FocusedIndex];
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

            TargetFocused();

            Redraw();
        }
    }

    void List::SetCount(int NewCount)
    {
        if(NewCount == Count || NewCount < 0)
            return;

        if(Count > NewCount)
        {
            for (int i = NewCount; i < Count; i++)
            {
                ListItem* Item = &Items[i];

                if(Allocated)
                    OnItemFree(this, Item);
            }
        }

        if(Items != 0)
            Items = (ListItem*)realloc(Items, NewCount * sizeof(ListItem));
        else
            Items = (ListItem*)malloc(NewCount * sizeof(ListItem));

        if(Count < NewCount)
        {
            for (int i = Count; i < NewCount; i++)
            {
                ListItem* Item = &Items[i];

                if(Allocated)
                    OnItemCreate(this, Item);
            }
        }

        if(Allocated)
            Redraw();

        Count = NewCount;
    }

    void List::Allocate()
    {
        Element::Allocate();

        Allocated = true;

        for (int i = 0; i < Count; i++)
        {
            ListItem* Item = &Items[i];

            OnItemCreate(this, Item);
        }

        if(FocusedIndex == -1 && Count > 0)
        {
            FocusedIndex = 0;
            Focused = &Items[0];
        }

        ItemHeight = Height / Rows;
        ItemWidth = Width / Columns;

        if(Direction == Horizontal)
        {
            if(Count % Rows > 0)
                Max = Count / Rows + 1;
            else
                Max = Count / Rows;

            Max = (Max * ItemWidth - Width);

            if(Max < 0)
                Max = 0;

            if(Position > Max)
                Position = Max;
        }
        else
        {
            if(Count % Columns > 0)
                Max = Count / Columns + 1;
            else
                Max = Count / Columns;

            Max = (Max * ItemHeight - Height);

            if(Max < 0)
                Max = 0;

            if(Position > Max)
                Position = Max;
        }


        if(Scrollbar != 0)
        {
            Scrollbar->Position = Position;
            Scrollbar->Max = Max;

            if(Direction == Horizontal)
                Scrollbar->Size = Width;
            else
                Scrollbar->Size = Height;
        }

        for (int i = 0; i < Count; i++)
            SetupItem(&Items[i]);
    }

    void List::Deallocate()
    {
        Element::Deallocate();

        Allocated = false;

        for (int i = 0; i < Count; i++)
        {
            ListItem* Item = &Items[i];

            OnItemFree(this, Item);
        }
    }

    void List::Draw(int X, int Y, unsigned char Alpha)
    {
        glEnable(GL_SCISSOR_TEST);

        if(Direction == Horizontal)
        {
            glScissor(X - DrawExtension.Start, Screen->Height - Y - Height, Width + DrawExtension.Start + DrawExtension.End, Height);

            if(RightToLeft)
            {
                int ItemLeft = X + Width - ItemWidth + Position;
                int ItemTop = Y;
                int Row = 0;

                for (int i = 0; i < Count; i++)
                {
                    //if(ItemLeft > X - ItemWidth - DrawExtension.Start)
                        DrawItem(&Items[i], ItemLeft, ItemTop, Alpha);

                    Row++;
                    ItemTop += ItemHeight;

                    if(Row >= Rows)
                    {
                        Row = 0;
                        ItemTop = Y;

                        ItemLeft -= ItemWidth;

                        //if(ItemLeft > X + Width + DrawExtension.End)
                        //    break;
                    }
                }

            }
            else
            {
                int ItemLeft = X - Position;
                int ItemTop = Y;
                int Row = 0;

                for (int i = 0; i < Count; i++)
                {
                    if(ItemLeft > X - ItemWidth - DrawExtension.Start)
                        DrawItem(&Items[i], ItemLeft, ItemTop, Alpha);

                    Row++;
                    ItemTop += ItemHeight;

                    if(Row >= Rows)
                    {
                        Row = 0;
                        ItemTop = Y;

                        ItemLeft += ItemWidth;

                        if(ItemLeft > X + Width + DrawExtension.End)
                            break;
                    }
                }
            }
        }
        else
        {
            glScissor(X, Screen->Height - Y - Height - DrawExtension.End, Width, Height + DrawExtension.Start + DrawExtension.End);

            if(RightToLeft)
            {
                int ItemLeft = X + Width - ItemWidth;
                int ItemTop = Y - Position;
                int Column = Columns;

                for (int i = 0; i < Count; i++)
                {
                    if(ItemTop > Y - ItemHeight - DrawExtension.Start)
                        DrawItem(&Items[i], ItemLeft, ItemTop, Alpha);

                    Column--;
                    ItemLeft -= ItemWidth;

                    if(Column == 0)
                    {
                        Column = Columns;

                        ItemLeft = X + Width - ItemWidth;

                        ItemTop += ItemHeight;

                        if(ItemTop > Y + Height + DrawExtension.End)
                            break;
                    }
                }
            }
            else
            {
                int ItemLeft = X;
                int ItemTop = Y - Position;
                int Column = 0;

                for (int i = 0; i < Count; i++)
                {
                    if(ItemTop > Y - ItemHeight - DrawExtension.Start)
                        DrawItem(&Items[i], ItemLeft, ItemTop, Alpha);

                    Column++;
                    ItemLeft += ItemWidth;

                    if(Column >= Columns)
                    {
                        Column = 0;

                        ItemLeft = X;

                        ItemTop += ItemHeight;

                        if(ItemTop > Y + Height + DrawExtension.End)
                            break;
                    }
                }
            }
        }
        glDisable(GL_SCISSOR_TEST);
    }
};
