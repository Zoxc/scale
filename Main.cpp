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

#include "Application.hpp"
#include "Image.hpp"
#include "Button.hpp"
#include "Solid.hpp"
#include "Label.hpp"

struct AppInfo
{
    char* Name;
    char* IconPath;
    Button* button;
};

struct Category
{
    char* Name;
    char* IconPath;
    Button* button;
};

std::vector<AppInfo*> Running;
std::vector<Category*> Categories;

Application Menu;

void PowerClick(Element* Owner)
{
    Menu.Terminated = true;
}

int main( int argc, char* args[] )
{
    AppInfo* App = new AppInfo();
    App->Name = "Package Manager";
    App->IconPath = "installer.png";
    Running.push_back(App);

    App = new AppInfo();
    App->Name = "Filesystem";
    App->IconPath = "folder.png";
    Running.push_back(App);

    App = new AppInfo();
    App->Name = "Internet Relay Chat";
    App->IconPath = "irc.png";
    Running.push_back(App);

    Category* Cat = new Category();
    Cat->Name = "Games";
    Cat->IconPath = "games.png";
    Categories.push_back(Cat);

    Cat = new Category();
    Cat->Name = "Media";
    Cat->IconPath = "media.png";
    Categories.push_back(Cat);

    Cat = new Category();
    Cat->Name = "System";
    Cat->IconPath = "system.png";
    Categories.push_back(Cat);

    Cat = new Category();
    Cat->Name = "Other";
    Cat->IconPath = "other.png";
    Categories.push_back(Cat);

    Image Background(&Menu, "back.png");

    FontSmall = TTF_OpenFont("FreeSans.ttf", 18);
    FontNormal = TTF_OpenFont("FreeSans.ttf", 22);
    FontBig = TTF_OpenFont("FreeSans.ttf", 24);

    Label Welcome(&Menu, "Welcome Zoxc, the time is 5:32 pm", FontSmall, FontColorBlack);
    Welcome.Left = 15;
    Welcome.Top = 15;

    Label RunningLabel(&Menu, "You are currently running:", FontSmall, FontColorBlack);
    RunningLabel.Left = 15;
    RunningLabel.Top = 55;

    // Power Button
    Button Power(&Menu, ButtonTypePush);
    Power.Left = 695;
    Power.Top = 5;
    Power.Width = 100;
    Power.Height = 45;
    Power.EventClick = &PowerClick;

    Image PowerIcon(&Power, "power.png");
    PowerIcon.Left = 5;
    PowerIcon.Top = 5;

    Label PowerLabel(&Power, "Power", FontSmall, FontColorBlack);
    PowerLabel.Left = 36;
    PowerLabel.Top = 10;

    Element Applications(&Menu);
    Applications.Left = 15;
    Applications.Top = 87;
    Applications.Width = 800;
    Applications.Height = 52 * Running.size();

    for(size_t i = 0; i < Running.size(); i++)
    {
        Running[i]->button = new Button(&Applications, ButtonTypePush);
        Running[i]->button->Left = 0;
        Running[i]->button->Top = 52 * i;
        Running[i]->button->Height = 52;


        Image* AppIcon = new Image(Running[i]->button, Running[i]->IconPath);
        AppIcon->Left = 5;
        AppIcon->Top = 2;

        Label* AppLabel = new Label(Running[i]->button, Running[i]->Name, FontNormal, FontColorBlack);
        AppLabel->Left = 5 + 48 + 8;
        AppLabel->Top = 12;

        Running[i]->button->Width = AppLabel->Width + 5 + 8 + AppIcon->Width + 7;
    }

    // Add D-pad bindings
    for(size_t i = 0; i < Running.size(); i++)
    {
        Running[i]->button->Links[ElementRight] = &Power;

        if(i > 0)
            Running[i]->button->Links[ElementUp] = Running[i-1]->button;
        else
            Running[i]->button->Links[ElementUp] = Running[Running.size()-1]->button;

        if(i < Running.size() - 1)
            Running[i]->button->Links[ElementDown] = Running[i+1]->button;
        else
            Running[i]->button->Links[ElementDown] = Running[0]->button;
    }

    if(Running.size() > 0)
    {
        Power.Links[ElementLeft] = Running[0]->button;
        Menu.Focus(Running[0]->button);
    }

    Solid Tabs(&Menu);
    Tabs.Left = 0;
    Tabs.Height = 66;
    Tabs.Top = 480 - Tabs.Height;
    Tabs.Width = 800;

    const int CategorySpacing = 8;
    int CategoryWidth = 800 / Categories.size();

    for(size_t i = 0; i < Categories.size(); i++)
    {
        Categories[i]->button = new Button(&Tabs, ButtonTypeBlock);
        Categories[i]->button->Left = CategoryWidth * i;
        Categories[i]->button->Top = 0;
        Categories[i]->button->Height = Tabs.Height;
        Categories[i]->button->Width = CategoryWidth;

        Label* CatLabel = new Label(Categories[i]->button, Categories[i]->Name, FontBig, FontColorWhite);
        CatLabel->Top = Tabs.Height / 2 - CatLabel->Height / 2;

        Image* CatIcon = new Image(Categories[i]->button, Categories[i]->IconPath);
        CatIcon->Top = Tabs.Height / 2 - CatIcon->Height / 2;

        CatIcon->Left = CategoryWidth / 2 - (CatIcon->Width + CategorySpacing + CatLabel->Width) / 2;
        CatLabel->Left = CatIcon->Left + CategorySpacing + CatIcon->Width;
    }

    Menu.Title = "SDL Demo";

    Menu.Run();

    return 0;
}
