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

#include "Graphics.hpp"


SDL_Color Black = {0, 0, 0};
SDL_Color White  = {255, 255, 255};

void Graphics::ApplySurface( int x, int y, SDL_Surface* Source, SDL_Surface* Destination )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(Source, 0, Destination, &offset);
}

SDL_Surface* Graphics::ConvertSurface(SDL_Surface* source)
{
    SDL_Surface* result = SDL_CreateRGBSurface(0, source->w, source->h, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);

    SDL_BlitSurface(source, 0, result, 0);

    SDL_FreeSurface(source);

    return result;
}

void Graphics::ApplySurfaceEx(int tx, int ty, SDL_Surface* source, SDL_Surface* dest)
{
    SDL_LockSurface(source);
    SDL_LockSurface(dest);

    Uint32* Pixel = (Uint32*)source->pixels;

    for(int y = 0; y < source->h; y++)
    for(int x = 0; x < source->w; x++)
    {
        Uint32* Dest = (Uint32*)dest->pixels + (y + ty) * dest->w + x + tx;

        unsigned char As = reinterpret_cast<Uint8*>(Pixel)[3];

        if(As == 255)
            *Dest = *Pixel;
        else if(As == 0)
        {
            Pixel++;
            continue;
        }
        else
        {
            unsigned char Ad = reinterpret_cast<Uint8*>(Dest)[3];

            unsigned short Rs = reinterpret_cast<Uint8*>(Pixel)[0] * As;
            unsigned short Gs = reinterpret_cast<Uint8*>(Pixel)[1] * As;
            unsigned short Bs = reinterpret_cast<Uint8*>(Pixel)[2] * As;

            unsigned short Rd = reinterpret_cast<Uint8*>(Dest)[0] * Ad;
            unsigned short Gd = reinterpret_cast<Uint8*>(Dest)[1] * Ad;
            unsigned short Bd = reinterpret_cast<Uint8*>(Dest)[2] * Ad;

            int A = As + Ad - ((Ad * As) / 255);

            Rs = Rs + Rd - ((Rd * As) / 255);
            Rs /= A;

            Gs = Gs + Gd - ((Gd * As) / 255);
            Gs /= A;

            Bs = Bs + Bd - ((Bd * As) / 255);
            Bs /= A;

            reinterpret_cast<Uint8*>(Dest)[0] = Rs;
            reinterpret_cast<Uint8*>(Dest)[1] = Gs;
            reinterpret_cast<Uint8*>(Dest)[2] = Bs;
            reinterpret_cast<Uint8*>(Dest)[3] = A;
        }

        Pixel++;
    }

    SDL_UnlockSurface(dest);
    SDL_UnlockSurface(source);
}

void Graphics::ApplyAlpha(int tx, int ty, SDL_Surface* source, SDL_Surface* dest, unsigned char Alpha)
{
    if(Alpha == 255)
    {
        ApplySurface(tx, ty, source, dest);
        return;
    }
    else if(Alpha == 0)
        return;

    if(source->format->BitsPerPixel != 32 || dest->format->BitsPerPixel != 32)
    {
        ApplySurface(tx, ty, source, dest);

        return;
    }

    SDL_LockSurface(source);
    SDL_LockSurface(dest);

    Uint32* Pixel = (Uint32*)source->pixels;

    for(int y = 0; y < source->h; y++)
    for(int x = 0; x < source->w; x++)
    {
        if(y + ty >= dest->h)
            continue;

        if(x + tx >= dest->w)
            continue;

        Uint32* Dest = (Uint32*)dest->pixels + (y + ty) * dest->w + x + tx;

        unsigned char AlphaBlend = reinterpret_cast<Uint8*>(Pixel)[3];
        AlphaBlend = (unsigned short)AlphaBlend * Alpha / 256;

        reinterpret_cast<Uint8*>(Dest)[0] = (AlphaBlend * (reinterpret_cast<Uint8*>(Pixel)[2] - reinterpret_cast<Uint8*>(Dest)[0])) / 256 + reinterpret_cast<Uint8*>(Dest)[0];
        reinterpret_cast<Uint8*>(Dest)[1] = (AlphaBlend * (reinterpret_cast<Uint8*>(Pixel)[1] - reinterpret_cast<Uint8*>(Dest)[1])) / 256 + reinterpret_cast<Uint8*>(Dest)[1];
        reinterpret_cast<Uint8*>(Dest)[2] = (AlphaBlend * (reinterpret_cast<Uint8*>(Pixel)[0] - reinterpret_cast<Uint8*>(Dest)[2])) / 256 + reinterpret_cast<Uint8*>(Dest)[2];

        Pixel++;
    }

    SDL_UnlockSurface(dest);
    SDL_UnlockSurface(source);
}

void Graphics::CopyAlpha(int tx, int ty, SDL_Surface* source, SDL_Surface* dest)
{
    SDL_LockSurface(source);
    SDL_LockSurface(dest);

    Uint32* Pixel = (Uint32*)source->pixels;

    for(int y = 0; y < source->h; y++)
    for(int x = 0; x < source->w; x++)
    {
        reinterpret_cast<Uint8*>((Uint32*)dest->pixels + (y + ty) * dest->w + x + tx)[3] = reinterpret_cast<Uint8*>(Pixel++)[0];
    }

    SDL_UnlockSurface(dest);
    SDL_UnlockSurface(source);
}

void Graphics::HalfAlpha(SDL_Surface* surface)
{
    SDL_LockSurface(surface);

    Uint32* Pixel = (Uint32*)surface->pixels;
    Uint32* PixelStop = &Pixel[surface->w * surface->h];

    while(Pixel != PixelStop)
    {
        Uint8 Alpha = reinterpret_cast<Uint8*>(Pixel)[3];

        if (Alpha != 0)
            reinterpret_cast<Uint8*>(Pixel)[3] = Alpha >> 1;

        Pixel++;
    }

    SDL_UnlockSurface(surface);
}

SDL_Surface* Graphics::BlurAlpha(SDL_Surface* source)
{
    // Resulting image
    SDL_Surface* surface = SDL_CreateRGBSurface(0, source->w + 4, source->h + 4, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);

    // Color it
    SDL_FillRect(surface, 0, SDL_MapRGB(surface->format, 0, 0, 0));

    SDL_LockSurface(source);
    SDL_LockSurface(surface);

    // Calculate new alpha
    Uint32* pixel = (Uint32*)surface->pixels;

    for(int y = 0; y < surface->h; y++)
    for(int x = 0; x < surface->w; x++)
    {
        int result = 0;

        for(int sy = -4; sy < 0; sy++)
        for(int sx = -4; sx < 0; sx++)
        {
            int ix = x + sx;

            if(ix > 0 && ix < source->w)
            {
                int iy = y + sy;

                if(iy > 0 && iy < source->h)
                    result += reinterpret_cast<Uint8*>((Uint32*)source->pixels + iy * source->w + ix)[3];
            }
        }

        reinterpret_cast<Uint8*>(pixel++)[3] = result >> 4;
    }

    SDL_UnlockSurface(surface);
    SDL_UnlockSurface(source);

    return surface;
}