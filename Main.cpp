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

#include <sstream>
#include "SDL_mixer.h"

#include "Main.hpp"
#include "Resources.hpp"
#include "List.hpp"

std::vector<AppInfo*> Running;
std::vector<CatInfo*> Categories;

Application Menu;
CategoryBackground* Background;
Window* Tabs;
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

    PowerLabel = new Label(this, "Power", Resources::FontNormal, FontColorBlack);
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
    Menu.Terminated = true;
}

void KeyDown(SDLKey Key)
{
    intptr_t Index = -1;

    if(Tabs->Focused != 0)
        Index = (intptr_t)Tabs->Focused->Tag;

    switch((int)Key)
    {
        case SDLK_a:
            if(Index == -1)
                Focus(Categories[Categories.size()-1]->button);
            else if(Index == 0)
                Tabs->KillFocus();
            else
                Focus(Categories[Index-1]->button);
            break;

        case SDLK_d:
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

    if( SDL_GetTicks() - LastUpdate > 100)
    {
            std::stringstream Caption;

            Caption << "FPS: ";

            Caption << Frames / ((SDL_GetTicks() - LastUpdate) / 1000.f);

            FPS->SetCaption(Caption.str());

            LastUpdate = SDL_GetTicks();

            Frames = 0;
    }

}
#endif

void AddIcon(Element* Root, int X, int Y, std::string IconPath, std::string Title)
{
    Icon* IconButton = new Icon(Root);
    IconButton->Width = 190;

    Image* IconIcon = new Image(IconButton, std::string("resources/icons_large/") + IconPath);
    IconIcon->Top = 4;

    Label* IconLabel = new Label(IconButton, Title, Resources::FontSmall, FontColorBlack);
    IconLabel->Top = 4 + 64 + 4;

    IconIcon->Left = (IconButton->Width - IconIcon->Width >> 1);
    IconLabel->Left = (IconButton->Width - IconLabel->Width >> 1);

    IconButton->Top = Y;
    IconButton->Height = 100;
    IconButton->Left = X + (200 - 190) / 2;
}

int main( int argc, char* args[] )
{
    Resources::Allocate();

    AppInfo* App = new AppInfo();
    App->Name = "Package Manager";
    App->IconPath = "resources/icons/installer.png";
    Running.push_back(App);

    App = new AppInfo();
    App->Name = "Filesystem";
    App->IconPath = "resources/icons/folder.png";
    Running.push_back(App);

    App = new AppInfo();
    App->Name = "Internet Relay Chat";
    App->IconPath = "resources/icons/irc.png";
    Running.push_back(App);

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
    Wallpaper.NeedAlpha = false;

    TaskList = new Window(&Menu);
    TaskList->Width = Menu.Width;
    TaskList->Height = Menu.Height;

    Label Welcome(TaskList, "Welcome Zoxc, the time is 5:32 pm", Resources::FontSmall, FontColorBlack);
    Welcome.Left = 15;
    Welcome.Top = 15;

    Label RunningLabel(TaskList, "You are currently running:", Resources::FontSmall, FontColorBlack);
    RunningLabel.Left = 15;
    RunningLabel.Top = 55;

    // Power Button
    PowerButton Power(TaskList);
    Power.Left = 686;
    Power.Top = 5;
    Power.Width = 107;
    Power.Height = 45;

    Element Applications(TaskList);
    Applications.Left = 15;
    Applications.Top = 92;
    Applications.Width = 800;
    Applications.Height = 52 * Running.size();
/*
    Applications.Hide();

    Image Sample(TaskList, "resources/sample.png");
    Sample.Left = (800 - Sample.Width) >> 1;
    Sample.Top = 92;

    Image Sample1(TaskList, "resources/samples.png");
    Sample1.Left = Sample.Left - Sample1.Width - 20;
    Sample1.Top = Sample.Top + Sample.Height - Sample1.Height;
    Sample1.AlphaBlend = 128;

    Image Sample2(TaskList, "resources/samples.png");
    Sample2.Left = Sample.Left + Sample.Width + 20;
    Sample2.Top = Sample.Top + Sample.Height - Sample2.Height;
    Sample2.AlphaBlend = 128;

    Image* AppIcon = new Image(TaskList, "resources/icons/other.png");
    Label* AppLabel = new Label(TaskList, "Demostration Menu", Resources::FontNormal, FontColorBlack);

    AppIcon->Left = (800 - (AppIcon->Width + AppLabel->Width + 8)) >> 1;
    AppIcon->Top = Sample.Top + Sample.Height + 10;

    AppLabel->Left = AppIcon->Left + AppIcon->Width + 8;
    AppLabel->Top = Sample.Top + Sample.Height + 10 + ((AppIcon->Height - AppLabel->Height) >> 1);

    Image ArrowR(TaskList, "resources/arrowr.png");
    ArrowR.Left = AppLabel->Left + AppLabel->Width + 10;
    ArrowR.Top = AppLabel->Top;
    ArrowR.AlphaBlend = 128;

    Image ArrowL(TaskList, "resources/arrowl.png");
    ArrowL.Left = AppIcon->Left - 10 - ArrowL.Width;
    ArrowL.Top = AppLabel->Top;
    ArrowL.AlphaBlend = 128;
*/
    for(size_t i = 0; i < Running.size(); i++)
    {
        Running[i]->button = new Icon(&Applications);
        Running[i]->button->Left = 0;
        Running[i]->button->Top = 52 * i;
        Running[i]->button->Height = 52;


        Image* AppIcon = new Image(Running[i]->button, Running[i]->IconPath);
        AppIcon->Left = 5;
        AppIcon->Top = 2;

        Label* AppLabel = new Label(Running[i]->button, Running[i]->Name, Resources::FontNormal, FontColorBlack);
        AppLabel->Left = 5 + 48 + 8;
        AppLabel->Top = 12;

        Running[i]->button->Width = AppLabel->Width + 5 + 8 + AppIcon->Width + 7;
    }

    Tabs = new Window(&Menu);
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

        Label* CategoryLabel = new Label(Categories[i]->button->Show, Categories[i]->Name, Resources::FontNormal, FontColorWhite);
        CategoryLabel->Left = CategoryImage->Left + 5 + CategoryImage->Width;
        CategoryLabel->Top = CategoryImage->Top + ((CategoryImage->Height - CategoryLabel->Height) >> 1);

        Label* CatLabel = new Label(Categories[i]->button, Categories[i]->Name, Resources::FontBig, FontColorWhite);
        CatLabel->Top = (Tabs->Height - CatLabel->Height) >> 1;

        Image* CatIcon = new Image(Categories[i]->button, std::string("resources/icons_large/") + Categories[i]->IconPath);
        CatIcon->Top = (Tabs->Height - CatIcon->Height) >> 1;

        CatIcon->Left = (CategoryWidth - CatIcon->Width - CategorySpacing - CatLabel->Width) >> 1;
        CatLabel->Left = CatIcon->Left + CategorySpacing + CatIcon->Width;
    }

    Menu.Children->remove(Tabs);
    Menu.Children->push_back(Tabs);

    // Add Links
    for(size_t i = 0; i < Running.size(); i++)
    {
        Running[i]->button->Link(ElementRight, &Power);

        if(i > 0)
            Running[i]->button->Link(ElementUp, Running[i-1]->button);
        else
            Running[i]->button->Link(ElementUp, Running[Running.size()-1]->button);

        if(i < Running.size() - 1)
            Running[i]->button->Link(ElementDown, Running[i+1]->button);
        else
            Running[i]->button->Link(ElementDown, Running[0]->button);
    }

    if(Running.size() > 0)
    {
        Power.Link(ElementLeft, Running[0]->button);
        Focus(Running[0]->button);
    }

    Focus(TaskList);

    #ifdef FRAME_EVENT
    FPS = new Label(&Menu, "FPS:       ", Resources::FontSmall, FontColorWhite);
    FPS->Left = 800 - 50 - FPS->Width;
    FPS->Top = 60;

    Menu.EventFrame = &OnFrame;
    #endif

    Menu.Title = "Scale Demo";
    Menu.EventKeyDown = &KeyDown;

    Menu.Allocate();


    Mix_Chunk* Startup = Mix_LoadWAV("resources/start.ogg");
    Mix_PlayChannel(-1, Startup, 0);

    Menu.Run();
    Resources::Deallocate();

    return 0;
}
