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
#include "Graphics.hpp"
#include "Solid.hpp"

namespace Scale
{
    #define FadeLength 300
    #define Time 250

    Solid::Solid(Element* AOwner) :
        Element::Element(AOwner),
        R(0),
        G(0),
        B(0)
    {
        Position = 0;
    }

    void Solid::Fade()
    {
        Up = true;
        Step = 0;
        Start();
    }

    void Solid::MouseUp(int X, int Y, bool Hovered)
    {
        Element::MouseUp(X, Y, Hovered);

        if(Hovered)
        {
            Up = false;
            Test->Fade();
            Step = 0;
            Start();
        }
    }
    void Solid::MouseDown(int X, int Y, bool Hovered)
    {
        Element::MouseDown(X, Y, Hovered);

        if(Hovered)
        {
            Test->Position = 0;
            Test->Up = true;
            Test->Redraw();

            Position = 0;

            Up = false;

            Redraw();
        }
    }

    void Solid::Animate(int Delta)
    {
        Step += Delta;

        if(Step > Time)
        {
            Step = Time;
            Stop();
        }

        Position = Step * (Height + FadeLength) / Time;

        Redraw();
    }


    Solid::~Solid()
    {
    }

    void Solid::Draw(int X, int Y, unsigned char Alpha)
    {
        if(Up)
        {
            glUniform1i(Screen->EffectUniform, 1);
            glUniform2f(Screen->EffectOptionsUniform, Screen->Height - (Y - Position) - Height, -FadeLength);
        }
        else
        {
            glUniform1i(Screen->EffectUniform, 1);
            glUniform2f(Screen->EffectOptionsUniform, Screen->Height - (Y + FadeLength - Position) - Height, FadeLength);
        }

        Graphics::Rect(X, Y, Width, Height, R, G, B, Alpha);

        glUniform1i(Screen->EffectUniform, 0);
    }
};
