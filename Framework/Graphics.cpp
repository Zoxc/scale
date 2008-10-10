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

SDL_Surface* Graphics::CreateSurface(int Width, int Height, bool Alpha)
{
    SDL_Surface* Video = SDL_GetVideoSurface();

    if(Alpha)
        return SDL_CreateRGBSurface(SDL_HWSURFACE, Width, Height, Video->format->BitsPerPixel, Video->format->Rmask, Video->format->Gmask, Video->format->Bmask, 0xff000000);
    else
        return SDL_CreateRGBSurface(SDL_HWSURFACE, Width, Height, Video->format->BitsPerPixel, Video->format->Rmask, Video->format->Gmask, Video->format->Bmask, 0);
}

void Graphics::ApplySurface( int x, int y, SDL_Surface* Source, SDL_Surface* Destination )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(Source, 0, Destination, &offset);
}

SDL_Surface* Graphics::OptimizeSurface(SDL_Surface* source, bool Alpha)
{
    if(source == 0)
        return 0;

    SDL_Surface* result = CreateSurface(source->w, source->h, Alpha);

    if(Alpha)
        ApplySurfaceEx(0, 0, source, result);
    else
        SDL_BlitSurface(source, 0, result, 0);

    SDL_FreeSurface(source);

    return result;
}

void Graphics::ApplySurfaceEx(int tx, int ty, SDL_Surface* source, SDL_Surface* dest)
{
    if(source->format->BitsPerPixel != 32 || dest->format->BitsPerPixel != 32)
    {
        ApplySurface(tx, ty, source, dest);

        return;
    }

    SDL_LockSurface(source);
    SDL_LockSurface(dest);

    Uint32* Pixel = (Uint32*)source->pixels;

    if(source->format->Rmask == dest->format->Rmask)
    {
        for(int y = 0; y < source->h; y++)
        {
            int yty = y + ty;

            if((yty >= dest->h) || (yty < 0))
                continue;

            for(int x = 0; x < source->w; x++, Pixel++)
            {
                unsigned char As = reinterpret_cast<Uint8*>(Pixel)[3];

                if(As < 5)
                    continue;

                int xtx = x + tx;

                if((xtx >= dest->w) || (xtx < 0))
                    continue;

                Uint32* Dest = (Uint32*)dest->pixels + yty * dest->w + xtx;

                if(As > 250)
                    *Dest = *Pixel;
                else
                {
                    unsigned char Ad = reinterpret_cast<Uint8*>(Dest)[3];

                    unsigned short Rs = reinterpret_cast<Uint8*>(Pixel)[0] * As;
                    unsigned short Gs = reinterpret_cast<Uint8*>(Pixel)[1] * As;
                    unsigned short Bs = reinterpret_cast<Uint8*>(Pixel)[2] * As;

                    unsigned short Rd = reinterpret_cast<Uint8*>(Dest)[0] * Ad;
                    unsigned short Gd = reinterpret_cast<Uint8*>(Dest)[1] * Ad;
                    unsigned short Bd = reinterpret_cast<Uint8*>(Dest)[2] * Ad;

                    unsigned short A = As + Ad - ((Ad * As) >> 8);

                    Rs = Rs + Rd - ((Rd * As) >> 8);
                    Rs /= A;

                    Gs = Gs + Gd - ((Gd * As) >> 8);
                    Gs /= A;

                    Bs = Bs + Bd - ((Bd * As) >> 8);
                    Bs /= A;

                    reinterpret_cast<Uint8*>(Dest)[0] = Rs;
                    reinterpret_cast<Uint8*>(Dest)[1] = Gs;
                    reinterpret_cast<Uint8*>(Dest)[2] = Bs;
                    reinterpret_cast<Uint8*>(Dest)[3] = A;
                }
            }
        }
    }
    else
    {
        for(int y = 0; y < source->h; y++)
        {
            int yty = y + ty;

            if((yty >= dest->h) || (yty < 0))
                continue;

            for(int x = 0; x < source->w; x++, Pixel++)
            {
                unsigned char As = reinterpret_cast<Uint8*>(Pixel)[3];

                if(As < 5)
                    continue;

                int xtx = x + tx;

                if((xtx >= dest->w) || (xtx < 0))
                    continue;

                Uint32* Dest = (Uint32*)dest->pixels + yty * dest->w + xtx;

                if(As > 250)
                {
                    reinterpret_cast<Uint8*>(Dest)[0] = reinterpret_cast<Uint8*>(Pixel)[2];
                    reinterpret_cast<Uint8*>(Dest)[1] = reinterpret_cast<Uint8*>(Pixel)[1];
                    reinterpret_cast<Uint8*>(Dest)[2] = reinterpret_cast<Uint8*>(Pixel)[0];
                    reinterpret_cast<Uint8*>(Dest)[3] = reinterpret_cast<Uint8*>(Pixel)[3];
                }
                else
                {
                    unsigned char Ad = reinterpret_cast<Uint8*>(Dest)[3];

                    unsigned short Rs = reinterpret_cast<Uint8*>(Pixel)[2] * As;
                    unsigned short Gs = reinterpret_cast<Uint8*>(Pixel)[1] * As;
                    unsigned short Bs = reinterpret_cast<Uint8*>(Pixel)[0] * As;

                    unsigned short Rd = reinterpret_cast<Uint8*>(Dest)[0] * Ad;
                    unsigned short Gd = reinterpret_cast<Uint8*>(Dest)[1] * Ad;
                    unsigned short Bd = reinterpret_cast<Uint8*>(Dest)[2] * Ad;

                    unsigned short A = As + Ad - ((Ad * As) >> 8);

                    Rs = Rs + Rd - ((Rd * As) >> 8);
                    Rs /= A;

                    Gs = Gs + Gd - ((Gd * As) >> 8);
                    Gs /= A;

                    Bs = Bs + Bd - ((Bd * As) >> 8);
                    Bs /= A;

                    reinterpret_cast<Uint8*>(Dest)[0] = Rs;
                    reinterpret_cast<Uint8*>(Dest)[1] = Gs;
                    reinterpret_cast<Uint8*>(Dest)[2] = Bs;
                    reinterpret_cast<Uint8*>(Dest)[3] = A;
                }
            }
        }
    }

    SDL_UnlockSurface(dest);
    SDL_UnlockSurface(source);
}

void Graphics::ApplyAlpha(int tx, int ty, SDL_Surface* source, SDL_Surface* dest, unsigned char Alpha)
{
    if(Alpha > 250)
    {
        ApplySurface(tx, ty, source, dest);

        return;
    }
    else if(Alpha < 5)
        return;

    if(source->format->Rmask != dest->format->Rmask || source->format->BitsPerPixel != 32 || dest->format->BitsPerPixel != 32)
    {
        ApplySurface(tx, ty, source, dest);

        return;
    }

    if(tx >= dest->w)
        return;

    if(ty >= dest->h)
        return;

    SDL_LockSurface(source);
    SDL_LockSurface(dest);

    Uint32* Pixel = (Uint32*)source->pixels;

    for(int y = 0; y < source->h; y++)
    {
        int yty = y + ty;

        if((yty >= dest->h) || (yty < 0))
            continue;

        for(int x = 0; x < source->w; x++, Pixel++)
        {
            int xtx = x + tx;

            if((xtx >= dest->w) || (xtx < 0))
                continue;

            Uint32* Dest = (Uint32*)dest->pixels + yty * dest->w + xtx;

            unsigned char AlphaBlend = reinterpret_cast<Uint8*>(Pixel)[3];
            AlphaBlend = (unsigned short)AlphaBlend * Alpha >> 8;

            if(AlphaBlend > 250)
                *Dest = *Pixel;
            else if(AlphaBlend < 5)
                continue;

            if(AlphaBlend <= 123 && AlphaBlend >= 133)
            {
                reinterpret_cast<Uint8*>(Dest)[0] = (reinterpret_cast<Uint8*>(Pixel)[0] + reinterpret_cast<Uint8*>(Dest)[0]) >> 1;
                reinterpret_cast<Uint8*>(Dest)[1] = (reinterpret_cast<Uint8*>(Pixel)[1] + reinterpret_cast<Uint8*>(Dest)[1]) >> 1;
                reinterpret_cast<Uint8*>(Dest)[2] = (reinterpret_cast<Uint8*>(Pixel)[2] + reinterpret_cast<Uint8*>(Dest)[2]) >> 1;
            }
            else
            {
                reinterpret_cast<Uint8*>(Dest)[0] = ((AlphaBlend * (reinterpret_cast<Uint8*>(Pixel)[0] - reinterpret_cast<Uint8*>(Dest)[0])) >> 8) + reinterpret_cast<Uint8*>(Dest)[0];
                reinterpret_cast<Uint8*>(Dest)[1] = ((AlphaBlend * (reinterpret_cast<Uint8*>(Pixel)[1] - reinterpret_cast<Uint8*>(Dest)[1])) >> 8) + reinterpret_cast<Uint8*>(Dest)[1];
                reinterpret_cast<Uint8*>(Dest)[2] = ((AlphaBlend * (reinterpret_cast<Uint8*>(Pixel)[2] - reinterpret_cast<Uint8*>(Dest)[2])) >> 8) + reinterpret_cast<Uint8*>(Dest)[2];
            }
        }
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

void Graphics::HalfAlpha(SDL_Surface* Surface, unsigned char Times)
{
    SDL_LockSurface(Surface);

    Uint32* Pixel = (Uint32*)Surface->pixels;
    Uint32* PixelStop = &Pixel[Surface->w * Surface->h];

    while(Pixel != PixelStop)
    {
        Uint8 Alpha = reinterpret_cast<Uint8*>(Pixel)[3];

        reinterpret_cast<Uint8*>(Pixel++)[3] = Alpha >> Times;
    }

    SDL_UnlockSurface(Surface);
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
