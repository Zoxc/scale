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
#include "Graphics.hpp"
#include "Resources.hpp"

List::List(Element* Owner):
    Element::Element(Owner),
    Icons(IconAbove),
    Captions(true),
    IconSpacing(4),
    Columns(4),
    Rows(3),
    Position(0),
    Min(0),
    Mode(0)
{
}

List::~List()
{
}


const float Limit = 300;

void List::Target(int X)
{
    Start();

    PositionStart = Position;

    Step = 0;

    PositionTarget = X;

    Velocity = PositionTarget - PositionStart;

    if(Velocity > Limit)
        Velocity = Limit;
    else if(Velocity < -Limit)
        Velocity = -Limit;

    Released = false;
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
        {
            Position = Min;
            Stop();
        }
        else if(Position > 0)
        {
            Position = 0;
            Stop();
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

    if(Root->GetTrapped() == this)
        Release();

    Mode = 0;

    Element::MouseUp(X, Y, Hovered);
}

void List::MouseDown(int X, int Y, bool Hovered)
{
    if(Hovered)
    {
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

    for (std::list<ListItem*>::iterator Item = Items.begin(); Item != Items.end(); Item++)
    {
        (*Item)->CaptionSurface = Graphics::OptimizeSurface(TTF_RenderText_Blended(Resources::FontSmall, (char*)(*Item)->Caption.c_str(), Black), true);
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

                case IconAbove:
                    (*Item)->IconX = X + (ItemWidth - IconSize >> 1);
                    (*Item)->IconY = Y + (ItemHeight - IconSize - IconSpacing - FontSize >> 1);

                    (*Item)->CaptionX = X + (ItemWidth - (*Item)->CaptionSurface->w >> 1);
                    (*Item)->CaptionY = (*Item)->IconY + IconSize + IconSpacing;
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
}

void List::Draw(SDL_Surface* Surface, int X, int Y, unsigned char Alpha)
{
    X += Position;

    for (std::list<ListItem*>::iterator Item = Items.begin(); Item != Items.end(); Item++)
    {
     /*   if((*Item)->X + ItemWidth < X)
            continue;

        if((*Item)->X + Left >= X + Width)
            break;*/

        //Graphics::ApplyAlpha(X + (*Item)->X, Y + (*Item)->Y, ItemFill, Surface, Alpha);

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
