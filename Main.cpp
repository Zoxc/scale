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
#include <sstream>
#include "Main.hpp"
#include "Resources.hpp"
#include "List.hpp"
#include "Switcher.hpp"

std::vector<CatInfo*> Categories;
Application Menu;
Scale::Window* Tabs;
Element* TaskList;

#ifdef FRAME_EVENT
    Label* FPS;
    int LastUpdate = 0;
    int Frames = 0;
#endif

PowerButton::PowerButton(Element* Owner) : Icon(Owner)
{
    PowerIcon = new Image(this, "resources/icons_small/power.png");
    PowerIcon->Left = 5;
    PowerIcon->Top = 5;

    PowerLabel = new Label(this, "Power", Resources::FontNormal, ColorBlack);
    PowerLabel->Left = 36;
    PowerLabel->Top = 8;
}

PowerButton::~PowerButton()
{
    delete PowerLabel;
    delete PowerIcon;
}

void PowerButton::Click()
{
    Menu.Stop();
}

void KeyDown(ElementKey Key)
{
    intptr_t Index = -1;

    if(Tabs->Focused != 0)
        Index = (intptr_t)Tabs->Focused->Tag;

    switch((int)Key)
    {
        case 0x41: // A Key
            if(Index == -1)
                Focus(Categories[Categories.size()-1]->button);
            else if(Index == 0)
                Tabs->KillFocus();
            else
                Focus(Categories[Index-1]->button);
            break;

        case 0x44: // D Key
            if(Index == -1)
                Focus(Categories[0]->button);
            else if(Index == int(Categories.size())-1)
                Tabs->KillFocus();
            else
                Focus(Categories[Index+1]->button);
            break;
    }
}

#ifdef FRAME_EVENT
void OnFrame()
{
    Frames++;

    if( GetTicks() - LastUpdate > 100)
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

int main()
{
    Resources::Init();

    CatInfo* Cat = new CatInfo();
    Cat->Name = "Games";
    Cat->IconPath = "games.png";
    Categories.push_back(Cat);

    Cat = new CatInfo();
    Cat->Name = "Media";
    Cat->IconPath = "media.png";
    Categories.push_back(Cat);

    Cat = new CatInfo();
    Cat->Name = "Web";
    Cat->IconPath = "web.png";
    Categories.push_back(Cat);

    Cat = new CatInfo();
    Cat->Name = "Other";
    Cat->IconPath = "other.png";
    Categories.push_back(Cat);

    Image Wallpaper(&Menu, "resources/back.png");

    TaskList = new Scale::Window(&Menu);
    TaskList->Width = Menu.Width;
    TaskList->Height = Menu.Height;

    // Power Button
    PowerButton Power(TaskList);
    Power.Left = 686;
    Power.Top = 5;
    Power.Width = 107;
    Power.Height = 45;

    Switcher Tasks(TaskList);
    Tasks.Width = 800;
    Tasks.Top = 53;
    Tasks.Height = TaskList->Height - Tasks.Top - 66;

    Tabs = new Scale::Window(&Menu);
    Tabs->Height = 66;
    Tabs->Top = 480 - Tabs->Height;
    Tabs->Width = 800;

    Solid* TabsBack = new Solid(Tabs);
    TabsBack->Height = 66;
    TabsBack->Width = 800;
    TabsBack->AlphaBlend = 128;

    const int CategorySpacing = 8;
    int CategoryWidth = 800 / Categories.size();

    for(size_t i = 0; i < Categories.size(); i++)
    {
        Categories[i]->button = new Category(Tabs);
        Categories[i]->button->Left = CategoryWidth * i;
        Categories[i]->button->Top = 0;
        Categories[i]->button->Height = Tabs->Height;
        Categories[i]->button->Width = CategoryWidth;
        Categories[i]->button->Tag = (void*)(intptr_t)i;

        Categories[i]->button->Show = new CategoryBackground(&Menu);
        Categories[i]->button->Show->Width = 800;
        Categories[i]->button->Show->Height = 800;
        Categories[i]->button->Show->Hide();

        List* ListView = new List(Categories[i]->button->Show);
        ListView->Top = 64;
        ListView->Height = 480 -ListView->Top - Tabs->Height;
        ListView->Width = 800;

        Categories[i]->button->DoFocus = ListView;

        ListView->Add("game-folder.png", "Emulators");
        ListView->Add("calendar.png", "Calendar");
        ListView->Add("media.png", "MPlayer");

        ListView->Add("installer.png", "Package Manager");
        ListView->Add("games.png", "Poker");
        ListView->Add("terminal.png", "Terminal");

        ListView->Add("editor.png", "Editor");
        ListView->Add("other.png", "This thing is too lon...");
        ListView->Add("file-manager.png", "File Manager");

        ListView->Add("web-browser.png", "Web Browser");
        ListView->Add("internet-group-chat.png", "Internet Relay Chat");
        ListView->Add("calculator.png", "Calculator");

        ListView->Add("game-folder.png", "Emulators");
        ListView->Add("calendar.png", "Calendar");
        ListView->Add("media.png", "MPlayer");

        ListView->Add("installer.png", "Package Manager");
        ListView->Add("games.png", "Poker");
        ListView->Add("terminal.png", "Terminal");

        ListView->Add("game-folder.png", "Emulators");
        ListView->Add("calendar.png", "Calendar");
        //ListView->Add("media.png", "MPlayer");

        ListView->Add("web-browser.png", "Web Browser");
        ListView->Add("internet-group-chat.png", "Internet Relay Chat");
        //ListView->Add("calculator.png", "Calculator");

        Image* Header = new Image(Categories[i]->button->Show, "resources/header.png");
        Header->AlphaBlend = 230;

        Image* CategoryImage = new Image(Categories[i]->button->Show, std::string("resources/icons/") + Categories[i]->IconPath);
        CategoryImage->Left = 8;
        CategoryImage->Top = 2;

        Label* CategoryLabel = new Label(Categories[i]->button->Show, Categories[i]->Name, Resources::FontNormal, ColorWhite);
        CategoryLabel->Left = CategoryImage->Left + 5 + CategoryImage->Width;
        CategoryLabel->Top = CategoryImage->Top + ((CategoryImage->Height - CategoryLabel->Height) >> 1);

        Label* CatLabel = new Label(Categories[i]->button, Categories[i]->Name, Resources::FontBig, ColorWhite);
        CatLabel->Top = (Tabs->Height - CatLabel->Height) >> 1;

        Image* CatIcon = new Image(Categories[i]->button, std::string("resources/icons_large/") + Categories[i]->IconPath);
        CatIcon->Top = (Tabs->Height - CatIcon->Height) >> 1;

        CatIcon->Left = (CategoryWidth - CatIcon->Width - CategorySpacing - CatLabel->Width) >> 1;
        CatLabel->Left = CatIcon->Left + CategorySpacing + CatIcon->Width;
    }

    Tabs->ToFront();

    Focus(TaskList);

    #ifdef FRAME_EVENT
    FPS = new Label(&Menu, "FPS:       ", Resources::FontSmall, ColorWhite);
    FPS->Left = 800 - 150;
    FPS->Top = 60;

    Menu.EventFrame = &OnFrame;
    #endif
/*
    Solid Splash(&Menu);
    Splash.Width = Menu.Width;
    Splash.Height = Menu.Height;
    Splash.AlphaBlend = 128;

    Image SplashImg(&Splash, "resources/logo.png");
    SplashImg.Left = (Menu.Width - SplashImg.Width) >> 1;
    SplashImg.Top = (Menu.Height - SplashImg.Height) >> 1;
*/
    Menu.Title = "Scale Demo";
    Menu.EventKeyDown = &KeyDown;

    Menu.Allocate();

    Resources::Allocate();

    Menu.Run();

    Resources::Deallocate();


    return 0;
}
