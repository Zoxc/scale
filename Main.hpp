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
#include <vector>
#include <vector>
#include "Application.hpp"
#include "Image.hpp"
#include "Label.hpp"
#include "Button.hpp"
#include "Solid.hpp"
#include "Category.hpp"

struct AppInfo
{
    char* Name;
    char* IconPath;
    Button* button;
};

struct CatInfo
{
    char* Name;
    char* IconPath;
    Category* button;
};

extern std::vector<AppInfo*> Running;
extern std::vector<CatInfo*> Categories;

extern Application Menu;
extern Solid* Tabs;
extern Element* TaskList;

class PowerButton:
    public Button
{
    public:
        PowerButton(Element* Owner);
        ~PowerButton();

        Label* PowerLabel;
        Image* PowerIcon;

        void Click();
};
