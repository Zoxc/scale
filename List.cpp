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
#include "SDL_ttf.h"
#include "SDL_image.h"

#include "List.hpp"
#include "Label.hpp"
#include "Graphics.hpp"
#include "Resources.hpp"

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

    if(Root->GetTrapped() == this)
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

    ItemFill = Graphics::CreateSurface(ItemWidth, ItemHeight, true);

    SDL_FillRect(ItemFill, 0, SDL_MapRGB(ItemFill->format, 255, 255, 255));

    Graphics::CopyAlpha(0, 0, Resources::RoundTopLeft, ItemFill);
    Graphics::CopyAlpha(ItemFill->w - Resources::RoundTopRight->w, 0, Resources::RoundTopRight, ItemFill);
    Graphics::CopyAlpha(0, ItemFill->h - Resources::RoundBottomLeft->h, Resources::RoundBottomLeft, ItemFill);
    Graphics::CopyAlpha(ItemFill->w - Resources::RoundBottomRight->w, ItemFill->h - Resources::RoundBottomRight->h, Resources::RoundBottomRight, ItemFill);

    Graphics::HalfAlpha(ItemFill, 2);

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
            (*Item)->CaptionSurface = Label::CreateFont(Resources::FontSmall, FontColorBlack, (*Item)->Caption.c_str());

        if(Icons != IconNone)
            (*Item)->IconSurface = Graphics::OptimizeSurface(IMG_Load(std::string("resources/icons_large/" + (*Item)->Icon).c_str()), true);

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
                    (*Item)->CaptionX = X + (ItemWidth - (*Item)->CaptionSurface->w >> 1);
                    (*Item)->CaptionY = Y + (ItemHeight - (*Item)->CaptionSurface->h >> 1);
                    break;

                case IconLeft:
                    (*Item)->IconX = X + (ItemWidth - IconSize - IconSpacing - (*Item)->CaptionSurface->w >> 1);
                    (*Item)->IconY = Y + (ItemHeight - IconSize >> 1);

                    (*Item)->CaptionX = (*Item)->IconX + IconSize + IconSpacing;
                    (*Item)->CaptionY = Y + (ItemHeight - (*Item)->CaptionSurface->h >> 1);
                    break;

                case IconRight:
                    (*Item)->CaptionX = X + (ItemWidth - IconSize - IconSpacing - (*Item)->CaptionSurface->w >> 1);
                    (*Item)->CaptionY = Y + (ItemHeight - (*Item)->CaptionSurface->h >> 1);

                    (*Item)->IconX = (*Item)->CaptionX + (*Item)->CaptionSurface->w + IconSpacing;
                    (*Item)->IconY = Y + (ItemHeight - IconSize >> 1);
                    break;

                case IconAbove:
                    (*Item)->IconX = X + (ItemWidth - IconSize >> 1);
                    (*Item)->IconY = Y + (ItemHeight - IconSize - IconSpacing - FontSize >> 1);

                    (*Item)->CaptionX = X + (ItemWidth - (*Item)->CaptionSurface->w >> 1);
                    (*Item)->CaptionY = (*Item)->IconY + IconSize + IconSpacing;
                    break;

                case IconBelow:
                    (*Item)->CaptionX = X + (ItemWidth - (*Item)->CaptionSurface->w >> 1);
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

    SDL_FreeSurface(ItemFill);

    for (std::vector<ListItem*>::iterator Item = Items.begin(); Item != Items.end(); Item++)
    {
        if(Captions)
            SDL_FreeSurface((*Item)->CaptionSurface);

        if(Icons != IconNone && (*Item)->IconSurface != 0)
            SDL_FreeSurface((*Item)->IconSurface);
    }
}

void List::Draw(SDL_Surface* Surface, int X, int Y, unsigned char Alpha)
{
    X += Position;

    for (std::vector<ListItem*>::iterator Item = Items.begin(); Item != Items.end(); Item++)
    {
        if(Focused == *Item)
            Graphics::ApplyAlpha(X + (*Item)->X, Y + (*Item)->Y, ItemFill, Surface, Alpha);

        if(Captions == false)
        {
            if((*Item)->IconSurface != 0)
                Graphics::ApplyAlpha(X + (*Item)->IconX, Y + (*Item)->IconY, (*Item)->IconSurface, Surface, Alpha);
        }
        else
        {
            if((Icons != IconNone) && ((*Item)->IconSurface != 0))
                Graphics::ApplyAlpha(X + (*Item)->IconX, Y + (*Item)->IconY, (*Item)->IconSurface, Surface, Alpha);

            Graphics::ApplyAlpha(X + (*Item)->CaptionX, Y + (*Item)->CaptionY, (*Item)->CaptionSurface, Surface, Alpha);
        }
    }
}
