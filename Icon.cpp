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

#include "SDL_mixer.h"

#include "Icon.hpp"
#include "Resources.hpp"
#include "Graphics.hpp"

Mix_Chunk* SoundSelect = 0;

int IconCount = 0;

Icon::Icon(Element* Owner) :
    Button(Owner),
    Focused(false)
{
}

Icon::~Icon()
{
}

void Icon::Click()
{
}

void Icon::Allocate()
{
    Element::Allocate();

    if(IconCount++ == 0)
    {
        SoundSelect = Mix_LoadWAV("resources/select.ogg");
    }

    Fill = Graphics::CreateSurface(Width, Height, true);

    SDL_FillRect(Fill, 0, SDL_MapRGB(Fill->format, 255, 255, 255));

    Graphics::CopyAlpha(0, 0, Resources::RoundTopLeft, Fill);
    Graphics::CopyAlpha(Fill->w - Resources::RoundTopRight->w, 0, Resources::RoundTopRight, Fill);
    Graphics::CopyAlpha(0, Fill->h - Resources::RoundBottomLeft->h, Resources::RoundBottomLeft, Fill);
    Graphics::CopyAlpha(Fill->w - Resources::RoundBottomRight->w, Fill->h - Resources::RoundBottomRight->h, Resources::RoundBottomRight, Fill);

    Graphics::HalfAlpha(Fill, 2);
}

void Icon::Deallocate()
{
    Element::Deallocate();

    if(--IconCount == 0)
    {
        Mix_FreeChunk(SoundSelect);
    }

    SDL_FreeSurface(Fill);
}

void Icon::Activate()
{
    Focused = true;

    Mix_PlayChannel(-1, SoundSelect, 0);

    Redraw();
}

void Icon::Deactivate()
{
    Focused = false;

    Redraw();
}

void Icon::Draw(SDL_Surface* Surface, int X, int Y, unsigned char Alpha)
{
    if(!Focused)
        return;

    Graphics::ApplyAlpha(X, Y, Fill, Surface, Alpha);
}
