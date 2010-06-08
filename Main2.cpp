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

#include "Main.hpp"
#include <iostream>
#include <sstream>
#include "Resources.hpp"
#include "Label.hpp"
#include "List.hpp"
#include "ListSearch.hpp"
#include "Switcher.hpp"
#include "VerticalBar.hpp"

Application Menu;

OpenGL::Texture* SharedIcon;

#ifdef FRAME_EVENT
    Label* FPS;
    int LastUpdate = 0;
    int Frames = 0;
#endif

#ifdef FRAME_EVENT
void OnFrame()
{
    Frames++;

    if( GetTicks() - LastUpdate > 300)
    {
            std::stringstream Caption;

            Caption << "FPS: ";

            Caption << Frames / ((GetTicks() - LastUpdate) / 1000.f);

            FPS->Caption = Caption.str();

            LastUpdate = GetTicks();

            Frames = 0;
    }

}
#endif

void ItemCreate(List* Owner, ListItem* Item)
{
}

void ItemFree(List* Owner, ListItem* Item)
{
}

void ItemAllocate(List* Owner, ListItem* Item)
{
    Item->Icon = SharedIcon;
    Item->Caption = "Testing";
}

void ItemDeallocate(List* Owner, ListItem* Item)
{
}

int main()
{
    Resources::Init();

    Image Wallpaper(&Menu, "resources/back2.png");

    Image Bluetooth(&Menu, "resources/bluetooth.png");
    Bluetooth.Left = Scale::Screen->Width - Bluetooth.Width - 4;
    Bluetooth.Top = 4;
    Bluetooth.AlphaBlend = 210;

    Label Time(&Menu, "9:36 pm", Resources::FontBig, ColorWhite);
    Time.Left = Scale::Screen->Width - Time.Width >> 1;
    Time.Top = 8;
    Time.AlphaBlend = 210;

    Label AppTitle(&Menu, "Scale", Resources::FontBig, ColorWhite);
    AppTitle.Left = 10;
    AppTitle.Top = Time.Top;
    AppTitle.AlphaBlend = 210;

    VerticalBar Bar(&Menu);

    Bar.Left = 25;
    Bar.Top = 65;
    Bar.Height = Menu.Height - 25 - 65;
    Bar.Width = 150;
    Bar.ItemFont = Resources::FontSmall;

    VerticalBarItem BarApplications;
    BarApplications.Caption = "Applications";
    BarApplications.IconPath = "resources/icons_large/editor.png";
    Bar.Items.push_back(&BarApplications);

    VerticalBarItem BarGames;
    BarGames.Caption = "Games";
    BarGames.IconPath = "resources/icons_large/games.png";
    Bar.Items.push_back(&BarGames);

    VerticalBarItem BarMedia;
    BarMedia.Caption = "Media";
    BarMedia.IconPath = "resources/icons_large/media.png";
    Bar.Items.push_back(&BarMedia);

    VerticalBarItem BarEmulators;
    BarEmulators.Caption = "Emulators";
    BarEmulators.IconPath = "resources/icons_large/application.png";
    Bar.Items.push_back(&BarEmulators);

    VerticalBarItem BarWeb;
    BarWeb.Caption = "Web";
    BarWeb.IconPath = "resources/icons_large/web-browser.png";
    Bar.Items.push_back(&BarWeb);

    VerticalBarItem BarSytem;
    BarSytem.Caption = "System";
    BarSytem.IconPath = "resources/icons_large/terminal.png";
    Bar.Items.push_back(&BarSytem);

    List ListView(&Menu);

    ListView.Icons = List::IconAbove;
    ListView.Direction = List::Vertical;

    ListView.OnItemCreate = ItemCreate;
    ListView.OnItemFree = ItemFree;
    ListView.OnItemAllocate = ItemAllocate;
    ListView.OnItemDeallocate = ItemDeallocate;

    ListView.Left = Bar.Left + Bar.Width + 25;
    ListView.Top = Bar.Top;
    ListView.Height = Bar.Height;
    ListView.Width = Scale::Screen->Width - 25 - ListView.Left - 3;

    ListView.Link(ElementLeft, &Bar);
    Bar.Link(ElementRight, &ListView);

    std::cout << "x1: " << ListView.Left << "\n"<< "x2: " << (ListView.Left + ListView.Width) << "\n";

    ListView.ItemFont = Resources::FontSmall;

    ListView.SetCount(55);

    Menu.Title = "Scale Demo";

    #ifdef FRAME_EVENT
    FPS = new Label(&Menu, "FPS:       ", Resources::FontSmall, ColorWhite);
    FPS->Left = 800 - 150;
    FPS->Top = 60;

    Menu.EventFrame = &OnFrame;
    #endif

    Menu.Allocate();

    Resources::Allocate();

    SharedIcon = new OpenGL::Texture();
    SharedIcon->Load("resources/icons_large/application.png");

    Menu.Run();

    delete SharedIcon;

    Resources::Deallocate();

    return 0;
}
