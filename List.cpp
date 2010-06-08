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
#include <malloc.h>
#include <iostream>

#include "List.hpp"

namespace Scale
{
    List::List(Element* Owner):
        Element(Owner),
        Focused(0),
        Items(0),
        OnItemCreate(0),
        OnItemFree(0),
        OnItemAllocate(0),
        OnItemDeallocate(0),
        Icons(IconAbove),
        Captions(true),
        #ifdef RightToLeftEnabled
            RightToLeft(false),
        #endif
        Direction(Vertical),
        Position(0),
        Min(0),
        Max(0),
        IconSpacing(10),
        Columns(4),
        Rows(3),
        Count(0),
        FocusedIndex(-1),
        Scrollbar(0),
        Mode(0),
        Allocated(false),
        Released(true),
        Animated(false),
        Activated(false)
    {
        Message = "";
        DrawExtension.Enable = true;
        DrawExtension.Start = 0;
        DrawExtension.End = 0;
    }

    List::~List()
    {
        #ifdef DEBUG
        if(OnItemFree != 0)
        #endif
        for (int i = 0; i < Count; i++)
            OnItemFree(this, &Items[i]);

        if(Items != 0)
            delete[] Items;
    }

    void List::Activate()
    {
        Activated = true;

        Redraw();
    }

    void List::Deactivate()
    {
        Activated = false;

        Redraw();
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
        bool Active = false;

        Step += Delta;

        if(Released)
        {
            if(Step >= 1000)
                Step = 1000;
            else
                Active = true;
        }
        else
        {
            if(Step >= 200)
                Step = 200;
            else
                Active = true;
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
        }


        if(!Active)
        {
            Animated = false;
            Stop();
        }

        Redraw();
    }

    void List::MouseUp(int X, int Y, bool Hovered)
    {
        if(Screen->Captured == this)
        {
            Release();

            Released = true;

            PositionStart = Position;

            Velocity = float(PositionTarget - PositionStart) * (1 - sin(Step / 200.f * M_PI_2));

            if(Velocity > Limit)
                Velocity = Limit;
            else if(Velocity < -Limit)
                Velocity = -Limit;

            Step = 0;
            Mode = 0;
        }

        Element::MouseUp(X, Y, Hovered);
    }

    void List::MouseDown(int X, int Y, bool Hovered)
    {
        if(Hovered)
        {
            Root->Focus(this);

            Capture();

            Mode = 1;

            Target(Position);

            int Column;

            if(Direction == Horizontal)
            {
                #ifdef RightToLeftEnabled
                    if(RightToLeft)
                        Column = -((X - Position) / ItemWidth - Columns + 1);
                    else
                        Column = (X + Position) / ItemWidth;

                #else
                    Column = (X + Position) / ItemWidth;
                #endif

                int Row = Y / ItemHeight;
                int Index = Column * Rows + Row;

                Focus(Index, false);

                TargetDown = X;
                Target(Position);

                #ifdef RightToLeftEnabled
                    if(RightToLeft)
                        MoveOffset = X - Position;
                    else
                        MoveOffset = X + Position;
                #else
                    MoveOffset = X + Position;
                #endif
            }
            else
            {
                #ifdef RightToLeftEnabled
                if(RightToLeft)
                    Column = Columns - 1 - X / ItemWidth;
                else
                    Column = X / ItemWidth;
                #else
                    Column = X / ItemWidth;
                #endif

                int Row = (Y + Position) / ItemHeight;
                int Index = Row * Columns + Column;

                Focus(Index, false);

                TargetDown = Y;
                MoveOffset = Y + Position;
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
        if(Focused == 0)
            return;

        int Index = FocusedIndex;

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
        if(FocusedIndex == -1)
            return;

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
                    #ifdef RightToLeftEnabled
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
                    #endif
                        if(FocusedIndex > Rows - 1)
                            NewIndex -= Rows;
                    #ifdef RightToLeftEnabled
                    }
                    #endif
                    break;

                case ElementRight:
                    #ifdef RightToLeftEnabled
                    if(RightToLeft)
                    {
                       if(NewIndex > Rows - 1)
                            NewIndex -= Rows;
                    }
                    else
                    {
                    #endif
                        if(NewIndex / Rows != (Count - 1) / Rows)
                        {
                            NewIndex += Rows;

                            if(NewIndex + 1 > (int)Count)
                                NewIndex = Count - 1;
                        }
                    #ifdef RightToLeftEnabled
                    }
                    #endif
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
                    #ifdef RightToLeftEnabled
                    if(RightToLeft)
                    {
                        if(FocusedIndex % Columns != Columns - 1)
                            NewIndex++;
                    }
                    else
                    {
                    #endif
                        if(FocusedIndex % Columns != 0)
                            NewIndex--;
                    #ifdef RightToLeftEnabled
                    }
                    #endif
                    break;

                case ElementRight:
                    #ifdef RightToLeftEnabled
                    if(RightToLeft)
                    {
                        if(FocusedIndex % Columns != 0)
                            NewIndex--;
                    }
                    else
                    {
                    #endif
                        if(FocusedIndex % Columns != Columns - 1)
                            NewIndex++;
                    #ifdef RightToLeftEnabled
                    }
                    #endif
                    break;
            }
        }

        if(!Focus(NewIndex, true))
            Element::KeyDown(Key);
    }

    bool List::Focus(int Index, bool ScrollTo)
    {
        if(Index < 0 || Index >= Count || Index == FocusedIndex)
            return false;

        ListItem* Item = &Items[Index];

        if(Item == 0 || Focused == Item)
            return false;

        FocusedIndex = Index;
        Focused = Item;

        if(ScrollTo)
            TargetFocused();

        if(Allocated)
            Redraw();

        return true;
    }

    void List::SetCount(int NewCount)
    {
        if(NewCount == Count || NewCount < 0)
            return;

        if(Count > NewCount)
            for (int i = NewCount; i < Count; i++)
            {
                if(Allocated)
                    #ifdef DEBUG
                    if(OnItemDeallocate != 0)
                    #endif
                    OnItemDeallocate(this, &Items[i]);

                #ifdef DEBUG
                if(OnItemFree != 0)
                #endif
                OnItemFree(this, &Items[i]);
            }

        if(Items != 0)
            Items = (ListItem*)realloc(Items, NewCount * sizeof(ListItem));
        else
            Items = (ListItem*)malloc(NewCount * sizeof(ListItem));

        if(Count < NewCount)
            for (int i = Count; i < NewCount; i++)
            {
                if(Allocated)
                    #ifdef DEBUG
                    if(OnItemAllocate != 0)
                    #endif
                    OnItemAllocate(this, &Items[i]);

                #ifdef DEBUG
                if(OnItemCreate != 0)
                #endif
                    OnItemCreate(this, &Items[i]);
            }

        Count = NewCount;

        if(Allocated)
        {
            Refresh();
            Redraw();
        }
    }

    void List::Allocate()
    {
        Element::Allocate();

        #ifdef DEBUG
        if(OnItemAllocate != 0)
        #endif
            for (int i = 0; i < Count; i++)
                OnItemAllocate(this, &Items[i]);

        Allocated = true;

        Refresh();
    }

    void List::Deallocate()
    {
        Element::Deallocate();

        Allocated = false;

        #ifdef DEBUG
        if(OnItemDeallocate != 0)
        #endif
            for (int i = 0; i < Count; i++)
                OnItemDeallocate(this, &Items[i]);
    }

    void List::SetMessage(const char* NewMessage)
    {
        Message = NewMessage;

        if(Message != "")
        {
            int MessageWidth;
            int MessageHeight;

            MessageWidth = ItemFont->Size(Message.c_str(), &MessageHeight);

            MessageLeft = Width - MessageWidth >> 1;
            MessageTop = Height - MessageHeight >> 1;
        }
    }

    void List::AttachScrollbar()
    {
        Scrollbar = new Scroller(Owner);
        Scrollbar->Width = 36;
        Scrollbar->Height = Height;
        Scrollbar->Top = Top;

        Width -= Scrollbar->Width;

        #ifdef RightToLeftEnabled
        if(RightToLeft)
        {
            Scrollbar->Left = Left;

            Left += Scrollbar->Width;
        }
        else
        #endif
            Scrollbar->Left = Left + Width;
    }

    void List::DeattachScrollbar()
    {
        Width += Scrollbar->Width;

        #ifdef RightToLeftEnabled
        if(RightToLeft)
            Left -= Scrollbar->Width;
        #endif

        delete Scrollbar;

        Scrollbar = 0;
    }

    void List::CalculateMax()
    {
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
    }

    void List::Refresh()
    {
        if(Count == 0)
        {
            FocusedIndex = -1;
            Focused = 0;
            Max = 0;
            Position = 0;

            if(Scrollbar != 0)
                DeattachScrollbar();

            return;
        }

        if(FocusedIndex >= Count || FocusedIndex < 0)
            Focus(0, true);

        CalculateMax();

        if(Max > 0)
        {
            if(Scrollbar == 0)
            {
                AttachScrollbar();

                CalculateMax();
            }

            Scrollbar->Position = Position;
            Scrollbar->Max = Max;

            if(Direction == Horizontal)
                Scrollbar->Size = Width;
            else
                Scrollbar->Size = Height;
        }
        else if(Scrollbar != 0)
        {
            DeattachScrollbar();
            CalculateMax();
        }

        if(Allocated)
        {
            const int IconSize = 64;
            int FontSize;

            ItemFont->Size("Wg", &FontSize);

            if(Captions == false)
                IconY = ItemHeight - IconSize >> 1;
            else
                switch(Icons)
                {
                    case IconNone:
                        CaptionY = ItemHeight - FontSize >> 1;
                        break;

                    case IconLeft:
                        IconY = ItemHeight - IconSize >> 1;
                        CaptionY = ItemHeight - FontSize >> 1;
                        break;

                    case IconRight:
                        CaptionY = ItemHeight - FontSize >> 1;
                        IconY = ItemHeight - IconSize >> 1;
                        break;

                    case IconAbove:
                        IconY = ItemHeight - IconSize - IconSpacing - FontSize >> 1;
                        CaptionY = IconY + IconSize + IconSpacing;
                        break;

                    case IconBelow:
                        CaptionY = ItemHeight - IconSize - IconSpacing - FontSize >> 1;
                        IconY = CaptionY + FontSize + IconSpacing;
                        break;
                }

            for (int i = 0; i < Count; i++)
            {
                ListItem* Item = &Items[i];

                int FontWidth = 0;

                if(Captions)
                {
                    FontWidth = ItemFont->Size(Item->Caption, 0);

                    switch(Icons)
                    {
                        case IconNone:
                            Item->CoordCaption = ItemWidth - FontWidth >> 1;
                            break;

                        case IconLeft:
                            Item->CoordIcon = ItemWidth - IconSize - IconSpacing - FontWidth >> 1;
                            Item->CoordCaption = Item->CoordIcon + IconSize + IconSpacing;
                            break;

                        case IconRight:
                            Item->CoordCaption = ItemWidth - IconSize - IconSpacing - FontWidth >> 1;
                            Item->CoordIcon = Item->CoordCaption + FontWidth + IconSpacing;
                            break;

                        case IconAbove:
                            Item->CoordIcon = ItemWidth - IconSize >> 1;
                            Item->CoordCaption = ItemWidth - FontWidth >> 1;
                            break;

                        case IconBelow:
                            Item->CoordCaption = ItemWidth - FontWidth >> 1;
                            Item->CoordIcon = ItemWidth - IconSize >> 1;
                            break;
                    }
                }
                else
                    Item->CoordIcon = ItemWidth - IconSize >> 1;
            }
        }
    }

    void List::Draw(int X, int Y, unsigned char Alpha)
    {
        //glUniform1i(Screen->EffectUniform, 1);
        //glUniform2f(Screen->EffectOptionsUniform, Screen->Height - Y - Height, Height);//(GLfloat)(Screen->Height - Y) / Screen->Height, Height);

        if(Message != "")
        {
            ItemFont->Print(Message.c_str(), ColorWhite, X + MessageLeft + 1, Y + MessageTop + 1, Alpha / 3);
            ItemFont->Print(Message.c_str(), ColorBlack, X + MessageLeft, Y + MessageTop, Alpha);
        }

        glEnable(GL_SCISSOR_TEST);

        if(Direction == Horizontal)
        {
            glScissor(X - DrawExtension.Start, Screen->Height - Y - Height, Width + DrawExtension.Start + DrawExtension.End, Height);

            #ifdef RightToLeftEnabled
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
            #endif
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
            #ifdef RightToLeftEnabled
            }
            #endif
        }
        else
        {
            glScissor(X, Screen->Height - Y - Height - DrawExtension.End, Width, Height + DrawExtension.Start + DrawExtension.End);

            #ifdef RightToLeftEnabled
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
            #endif
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
            #ifdef RightToLeftEnabled
            }
            #endif
        }
        glDisable(GL_SCISSOR_TEST);
    }
};
