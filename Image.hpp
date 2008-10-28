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

#include "Element.hpp"

class Image:
    public Element
{
    public:
        Image(Element* Owner, std::string Path);
        virtual ~Image();

        std::string Filename;
        bool NeedAlpha;

        static void SizeFromFile(std::string FileName, int* Width, int* Height);

        void Allocate();
        void Deallocate();
        void Draw(int X, int Y, unsigned char Alpha);

        OpenGL::Texture* Texture;
};
