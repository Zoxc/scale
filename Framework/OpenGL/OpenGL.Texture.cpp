#include <iostream>
#include <png.h>
#include <stdarg.h>
#include "OpenGL.Texture.hpp"

OpenGL::Texture::Texture()
{
    glGenTextures(1, &Handle);
}

OpenGL::Texture::~Texture()
{
    glDeleteTextures(1, &Handle);
}

void OpenGL::Texture::Load(const char* FileName)
{
    png_structp PngPtr;
    png_infop InfoPtr;
    png_bytepp RowPointers;
    unsigned char* ImageData;

	char Header[8];

	FILE *File = fopen(FileName, "rb");
	if(!File)
	{
		printf("File %s could not be opened for reading\n", FileName);
		return;
	}

	fread(Header, 1, 8, File);

	if(png_sig_cmp((png_byte*)Header, 0, 8))
		printf("File %s is not recognized as a PNG file\n", FileName);

	PngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);

	if(!PngPtr)
	{
		printf("png_create_read_struct failed on file: %s\n", FileName);
		return;
	}

	InfoPtr = png_create_info_struct(PngPtr);

	if(!InfoPtr)
	{
		printf("png_create_info_struct failed on file: %s\n", FileName);
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

    Width = InfoPtr->width;
    Height = InfoPtr->height;

    // Expand to RGB
    png_set_expand(PngPtr);
    //png_set_filler(PngPtr, 0xFF, PNG_FILLER_AFTER);

    unsigned int RowSize = png_get_rowbytes(PngPtr, InfoPtr);

    ImageData = new unsigned char[RowSize * Height + 4096];

    RowPointers = new png_bytep[RowSize];

    for (int i = 0;  i < Height; i++)
        RowPointers[i] = ImageData + i * RowSize;

    png_read_image(PngPtr, RowPointers);

    delete[] RowPointers;

    glBindTexture(GL_TEXTURE_2D, Handle);

    if(InfoPtr->channels == 4 && InfoPtr->bit_depth == 8)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ImageData);
    else if(InfoPtr->channels == 3 && InfoPtr->bit_depth == 8)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, ImageData);

    delete[] ImageData;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    png_destroy_read_struct(&PngPtr, &InfoPtr, 0);

    fclose(File);
}
