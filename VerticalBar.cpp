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

#include <iostream>
#include <math.h>
#include "VerticalBar.hpp"
#include "Button.hpp"
#include "Main.hpp"
#include "Graphics.hpp"

namespace Scale
{
    VerticalBar::VerticalBar(Element* AOwner) :
        Element::Element(AOwner),
        Animating(false),
        Activated(false),
        Focused(0)
    {
    }

    VerticalBar::~VerticalBar()
    {
    }

    void VerticalBar::Activate()
    {
        Activated = true;

        Redraw();
    }

    void VerticalBar::Deactivate()
    {
        Activated = false;

        Redraw();
    }

    void VerticalBar::Focus(VerticalBarItem* Item)
    {
        if(Item == Focused)
            return;

        Focused = Item;

        Refresh(false);

        Step = 0;

        if(!Animating)
        {
            Start();
            Animating = true;
        }

        Redraw();
    }

    void VerticalBar::Allocate()
    {
        Element::Allocate();

        int FontHeight;

        ItemFont->Size("Wg", &FontHeight);

        ItemHeight = FontHeight + 30;

        IconLeft = Width - 64 >> 1;

        FontTop = (ItemHeight - FontHeight >> 1) - 4;

        int IconTop = 0;

        for(std::vector<VerticalBarItem*>::iterator Item = Items.begin(); Item != Items.end(); Item++)
        {
            (*Item)->Icon = new OpenGL::Texture();
            (*Item)->Icon->Load((*Item)->IconPath);

            (*Item)->IconTop = IconTop + 18;

            IconTop += ItemHeight;

            (*Item)->Step = 255;

            (*Item)->CaptionLeft = Width - ItemFont->Size((*Item)->Caption, 0) >> 1;
        }

        if(Items.size() > 0)
            Focused = Items[0];

        Refresh(true);
    }

    void VerticalBar::Deallocate()
    {
        Element::Deallocate();

        for(std::vector<VerticalBarItem*>::iterator Item = Items.begin(); Item != Items.end(); Item++)
            delete (*Item)->Icon;
    }

    void VerticalBar::KeyDown(ElementKey Key)
    {
        if(Focused == 0)
            return;

        unsigned int Index = 0;

        for(std::vector<VerticalBarItem*>::iterator Item = Items.begin(); Item != Items.end(); Item++, Index++)
            if(*Item == Focused)
                break;

        switch((int)Key)
        {
            case ElementUp:
                if(Index > 0)
                    Focus(Items[Index - 1]);
                else
                    Element::KeyDown(Key);
                break;

            case ElementDown:
                if(Index < Items.size() -1)
                    Focus(Items[Index + 1]);
                else
                    Element::KeyDown(Key);
                break;

            default:
                Element::KeyDown(Key);
                break;
        }
    }

    void VerticalBar::Refresh(bool Initial)
    {
        int Top = 0;
        int i = 0;

        for(std::vector<VerticalBarItem*>::iterator Item = Items.begin(); Item != Items.end(); Item++, i++)
        {
            unsigned char TargetAlpha;

            if(Focused == (*Item))
            {
                FocusedTarget = Top;

                if(Initial)
                    FocusedCurrent = FocusedTarget;

                FocusedStart = FocusedCurrent;

                Top += 64 + 15;

                TargetAlpha = 255;
            }
            else
                TargetAlpha = 0;

            // Icon Alpha

            if((*Item)->IconTarget != TargetAlpha)
            {
                (*Item)->IconTarget = TargetAlpha;

                if(Initial)
                    (*Item)->IconCurrent = (*Item)->IconTarget;

                (*Item)->IconStart = (*Item)->IconCurrent;

                (*Item)->IconStep = 0;
            }

            // Text Position

            if((*Item)->Target != Top)
            {
                (*Item)->Target = Top;

                if(Initial)
                    (*Item)->Current = (*Item)->Target;

                (*Item)->Start = (*Item)->Current;

                (*Item)->Step = 0;
            }

            Top += ItemHeight;
        }
    }

    void VerticalBar::MouseDown(int X, int Y, bool Hovered)
    {
        if(Hovered)
        {
            Root->Focus(this);

            int Top = 0;
            int Height;

            for(std::vector<VerticalBarItem*>::iterator Item = Items.begin(); Item != Items.end(); Item++)
            {
                if(Focused == *Item)
                    Height = ItemHeight + 64 + 15;
                else
                    Height = ItemHeight;

                if(Y >= Top && Y < Top + Height)
                {
                    Focus(*Item);

                    break;
                }

                Top += Height;
            }
        }

        Element::MouseDown(X, Y, Hovered);
    }

    void VerticalBar::Animate(int Delta)
    {
        const int Time = 200;

        bool Active = false;

        if(Step >= Time)
            FocusedCurrent = FocusedTarget;
        else
        {
            Step += Delta;

            Active = true;

            float Sin = sin((float)Step / (float)Time * M_PI_2);

            FocusedCurrent = FocusedStart + (int)((FocusedTarget - FocusedStart) * Sin);
        }

        for(std::vector<VerticalBarItem*>::iterator Item = Items.begin(); Item != Items.end(); Item++)
        {
            if((*Item)->IconStep >= Time)
                (*Item)->IconCurrent = (*Item)->IconTarget;
            else
            {
                (*Item)->IconStep += Delta;

                Active = true;

                float Sin = sin((float)(*Item)->IconStep / (float)Time * M_PI_2);

                (*Item)->IconCurrent = (*Item)->IconStart + (int)(((*Item)->IconTarget - (*Item)->IconStart) * Sin);
            }

            if((*Item)->Step >= Time)
                (*Item)->Current = (*Item)->Target;
            else
            {
                (*Item)->Step += Delta;

                Active = true;

                float Sin = sin((float)(*Item)->Step / (float)Time * M_PI_2);

                (*Item)->Current = (*Item)->Start + (int)(((*Item)->Target - (*Item)->Start) * Sin);
            }
        }

        if(!Active)
        {
            Stop();
            Animating = false;
        }

        Redraw();
    }

    void VerticalBar::Draw(int X, int Y, unsigned char Alpha)
    {
        //Graphics::RoundRect(X, Y, Width, Height, 0, 0, 0, Alpha / 4);

        if(Focused != 0)
        {
            int CurrentHeight = ItemHeight + 15 + 64;
            int GlossHeight = CurrentHeight >> 1;
            CurrentHeight = CurrentHeight - GlossHeight;

            //glEnable(GL_SCISSOR_TEST);

            //glScissor(X, Screen->Height - (Y + FocusedCurrent + GlossHeight), Width, GlossHeight);
            //Graphics::RoundRect(X, Y + FocusedCurrent, Width, ItemHeight + 15 + 64, 0, 0, 0, Alpha * 5 / 20);

            //glScissor(X, Screen->Height - (Y + FocusedCurrent + GlossHeight + CurrentHeight) , Width, CurrentHeight);
            if(Activated)
                Graphics::RoundRect(X, Y + FocusedCurrent, Width, ItemHeight + 15 + 64, 0, 0, 0, Alpha * 7 / 20);
            else
                Graphics::RoundRect(X, Y + FocusedCurrent, Width, ItemHeight + 15 + 64, 0, 0, 0, Alpha * 3 / 20);

            //glDisable(GL_SCISSOR_TEST);
        }

        for(std::vector<VerticalBarItem*>::iterator Item = Items.begin(); Item != Items.end(); Item++)
        {
            Graphics::Texture((*Item)->Icon, X + IconLeft, Y + (*Item)->IconTop, (*Item)->IconCurrent * Alpha >> 8);

            ItemFont->Print((*Item)->Caption, 0, X + (*Item)->CaptionLeft + 1, Y + (*Item)->Current + FontTop + 1, Alpha >> 1);
            ItemFont->Print((*Item)->Caption, 0xFFFFFFFF, X + (*Item)->CaptionLeft, Y + (*Item)->Current + FontTop, Alpha);
        }
    }
};
