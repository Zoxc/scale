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

#include <stdarg.h>
#include "png.h"

#include "Graphics.hpp"
#include "Image.hpp"

Image::Image(Element* Owner, std::string Path):
    Element::Element(Owner),
    NeedAlpha(true)
{
    Filename = Path;

    SizeFromFile(Path, &Width, &Height);
}

Image::~Image()
{
}

void Image::SizeFromFile(std::string FileName, int* Width, int* Height)
{
    png_structp PngPtr;
    png_infop InfoPtr;

	char Header[8];

	FILE *File = fopen(FileName.c_str(), "rb");
	if (!File)
	{
		printf("File %s could not be opened for reading\n", FileName.c_str());
		return;
	}

	fread(Header, 1, 8, File);

	if (png_sig_cmp((png_byte*)Header, 0, 8))
		printf("File %s is not recognized as a PNG file\n", FileName.c_str());

	PngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
	if(!PngPtr)
	{
		printf("png_create_read_struct failed on file: %s\n", FileName.c_str());
		return;
	}

	InfoPtr = png_create_info_struct(PngPtr);
	if(!InfoPtr)
	{
		printf("png_create_info_struct failed on file: %s\n", FileName.c_str());
		return;
	}

	if(setjmp(png_jmpbuf(PngPtr)))
	{
		printf("Error during init_io\n");
		return;
	}

	png_init_io(PngPtr, File);
	png_set_sig_bytes(PngPtr, 8);

    png_read_info(PngPtr, InfoPtr);

	*Width = InfoPtr->width;
	*Height = InfoPtr->height;

    png_destroy_read_struct(&PngPtr, &InfoPtr, 0);

    fclose(File);
}

void Image::Allocate()
{
    Element::Allocate();

    Texture = new OpenGL::Texture();
    Texture->Load(Filename.c_str());
}

void Image::Deallocate()
{
    Element::Deallocate();

    delete Texture;
}

void Image::Draw(int X, int Y, unsigned char Alpha)
{
    Graphics::Texture(Texture, X, Y, Alpha);
}
