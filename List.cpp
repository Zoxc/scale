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

List::List(Element* Owner):
    Element::Element(Owner),
    Focused(0),
    Icons(IconAbove),
    Captions(true),
    IconSpacing(4),
    Columns(4),
    Rows(3),
    FocusedIndex(-1),
    Position(0),
    Min(0),
    Mode(0),
    Released(true)
{
}

List::~List()
{
}


const float Limit = 300;

void List::Target(int X)
{
    Released = false;

    Start();

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
            Stop();
        }
    }
    else
    {
        if(Step >= 200)
        {
            Step = 200;
            Stop();
        }
    }

    int NewPosition;

    if(Released)
        NewPosition = PositionStart + (int)floor(Velocity * 1000.f / 200.f * sin(Step / 1000.f * M_PI_2));
    else
        NewPosition = PositionStart + (int)floor(Velocity * sin(Step / 200.f * M_PI_2));

    if(Position != NewPosition)
    {
        Position = NewPosition;

        if(Position < Min)
            Position = Min;
        else if(Position > 0)
            Position = 0;

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

    if(Screen->Trapped == this)
        Release();

    Mode = 0;

    Element::MouseUp(X, Y, Hovered);
}

void List::MouseDown(int X, int Y, bool Hovered)
{
    if(Hovered)
    {
        Root->Focus(this);

        unsigned int Column = (X - Position) / ItemWidth;
        unsigned int Row = Y / ItemHeight;
        unsigned int Index = Column * Rows + Row;

        if(Index < Items.size())
        {
            ListItem* NewFocus = Items[Index];

            if(NewFocus != Focused)
            {
                FocusedIndex = Index;
                Focused = NewFocus;
                Redraw();
            }
        }

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
        if(abs(X - DownX) > 15)
        {
            Mode = 2;
            Trap();
        }

    if(Mode > 0)
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

            if(NewIndex + 1 > (int)Items.size())
                NewIndex = Items.size() - 1;
            break;

    }

    if(NewIndex < (int)Items.size() && NewIndex != FocusedIndex)
    {
        FocusedIndex = NewIndex;
        Focused = Items[FocusedIndex];
        TargetFocused();
        Redraw();
    }
}

void List::Add(std::string Icon, std::string Caption)
{
    ListItem* New = new ListItem();
    New->Icon = Icon;
    New->Caption = Caption;

    Items.push_back(New);
}

void List::Allocate()
{
    Element::Allocate();

    if(FocusedIndex == -1 && Items.size() > 0)
    {
        FocusedIndex = 0;
        Focused = Items[0];
    }

    ItemHeight = Height / Rows;
    ItemWidth = Width / Columns;

    if(Items.size() % Rows > 0)
        Min = Items.size() / Rows + 1;
    else
        Min = Items.size() / Rows;

    Min = (Min * ItemWidth - Width);

    if(Min < 0)
        Min = 0;
    else
        Min *= -1;

    int ItemX = 0;
    int ItemY = 0;

    const int IconSize = 64;
    const int FontSize = 19;

    for (std::vector<ListItem*>::iterator Item = Items.begin(); Item != Items.end(); Item++)
    {
        if(Captions)
        {
            (*Item)->CaptionTexture = new OpenGL::Texture();

            Resources::FontSmall.Size((*Item)->Caption, &(*Item)->CaptionTexture->Width, &(*Item)->CaptionTexture->Height);
        }

        if(Icons != IconNone)
        {
            (*Item)->IconTexture = new OpenGL::Texture();

            (*Item)->IconTexture->Load(std::string("resources/icons_large/" + (*Item)->Icon).c_str());
        }

        int X = ItemWidth * ItemX;
        int Y = ItemHeight * ItemY;

        (*Item)->X = X;
        (*Item)->Y = Y;

        if(Captions == false)
        {
            (*Item)->IconX = X + (ItemWidth - IconSize >> 1);
            (*Item)->IconY = Y + (ItemHeight - IconSize >> 1);
        }
        else
            switch(Icons)
            {
                case IconNone:
                    (*Item)->CaptionX = X + (ItemWidth - (*Item)->CaptionTexture->Width >> 1);
                    (*Item)->CaptionY = Y + (ItemHeight - (*Item)->CaptionTexture->Height >> 1);
                    break;

                case IconLeft:
                    (*Item)->IconX = X + (ItemWidth - IconSize - IconSpacing - (*Item)->CaptionTexture->Width >> 1);
                    (*Item)->IconY = Y + (ItemHeight - IconSize >> 1);

                    (*Item)->CaptionX = (*Item)->IconX + IconSize + IconSpacing;
                    (*Item)->CaptionY = Y + (ItemHeight - (*Item)->CaptionTexture->Width >> 1);
                    break;

                case IconRight:
                    (*Item)->CaptionX = X + (ItemWidth - IconSize - IconSpacing - (*Item)->CaptionTexture->Width >> 1);
                    (*Item)->CaptionY = Y + (ItemHeight - (*Item)->CaptionTexture->Height >> 1);

                    (*Item)->IconX = (*Item)->CaptionX + (*Item)->CaptionTexture->Width + IconSpacing;
                    (*Item)->IconY = Y + (ItemHeight - IconSize >> 1);
                    break;

                case IconAbove:
                    (*Item)->IconX = X + (ItemWidth - IconSize >> 1);
                    (*Item)->IconY = Y + (ItemHeight - IconSize - IconSpacing - FontSize >> 1);

                    (*Item)->CaptionX = X + (ItemWidth - (*Item)->CaptionTexture->Width >> 1);
                    (*Item)->CaptionY = (*Item)->IconY + IconSize + IconSpacing;
                    break;

                case IconBelow:
                    (*Item)->CaptionX = X + (ItemWidth - (*Item)->CaptionTexture->Width >> 1);
                    (*Item)->CaptionY = Y + (ItemHeight - IconSize - IconSpacing - FontSize >> 1);

                    (*Item)->IconX = X + (ItemWidth - IconSize >> 1);
                    (*Item)->IconY = (*Item)->CaptionY + FontSize + IconSpacing;
                    break;
            }

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


    for (std::vector<ListItem*>::iterator Item = Items.begin(); Item != Items.end(); Item++)
    {
        if(Captions)
            delete (*Item)->CaptionTexture;

        if(Icons != IconNone && (*Item)->IconTexture != 0)
            delete (*Item)->IconTexture;
    }
}

void List::Draw(int X, int Y, unsigned char Alpha)
{
    X += Position;

    for (std::vector<ListItem*>::iterator Item = Items.begin(); Item != Items.end(); Item++)
    {
        if(Focused == *Item)
            Graphics::Rect(X + (*Item)->X, Y + (*Item)->Y, ItemWidth, ItemHeight, 0, 0, 0, Alpha / 4);

        if((Icons != IconNone) && ((*Item)->IconTexture != 0))
            Graphics::Texture((*Item)->IconTexture, X + (*Item)->IconX, Y + (*Item)->IconY, Alpha);

        if(Captions)
        {
            Resources::FontSmall.Print((*Item)->Caption, ColorWhite, X + (*Item)->CaptionX + 1, Y + (*Item)->CaptionY + 1, Alpha / 2);
            Resources::FontSmall.Print((*Item)->Caption, ColorBlack, X + (*Item)->CaptionX, Y + (*Item)->CaptionY, Alpha);
        }
    }
}
