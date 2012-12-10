/*
 * Glycerin - Fuel for OpenGL applications
 * Copyright (C) 2012  Andrew Brown
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef GLYCERIN_BITMAPREADER_HPP
#define GLYCERIN_BITMAPREADER_HPP
#include "glycerin/common.h"
#include <fstream>
#include <cstring>
#include <string>
#include "glycerin/Bitmap.hxx"
namespace Glycerin {


/**
 * Reads a bitmap image into memory.
 *
 * To use _BitmapReader_, create one and then pass the path to your image file
 * to [read].
 *
 * ~~~
 * BitmapReader reader;
 * Bitmap bitmap = reader.read("image.bmp");
 * ~~~
 *
 * To use the resulting bitmap, see [bitmap].
 *
 * [bitmap]: @ref Bitmap "Bitmap"
 * [read]: @ref read(const std::string&) "read(const std::string&)"
 */
class BitmapReader {
public:
// Methods
    BitmapReader();
    virtual ~BitmapReader();
    Bitmap read(const std::string& filename);
private:
// Types
    struct FileHeader {
        char bfType[2];
        GLuint bfSize;
        GLushort bfReserved1;
        GLushort bfReserved2;
        GLuint bfOffBits;
    };
    struct InfoHeader {
        GLuint biSize;
        GLuint biWidth;
        GLuint biHeight;
        GLushort biPlanes;
        GLushort biBitCount;
        GLuint biCompression;
        GLuint biSizeImage;
        GLuint biXPelsPerMeter;
        GLuint biYPelsPerMeter;
        GLuint biClrUsed;
        GLuint biClrImportant;
    };
// Constants
    static const GLint ALIGNMENT = 4;
    static const GLenum FORMAT = GL_BGR;
// Methods
    static bool isCompressed(const InfoHeader& infoHeader);
    static bool isTwentyFourBit(const InfoHeader& infoHeader);
    static bool isValidFileHeader(const FileHeader& fileHeader);
    static bool isValidInfoHeader(const InfoHeader& infoHeader);
    static FileHeader readFileHeader(std::ifstream& file);
    static InfoHeader readInfoHeader(std::ifstream& file);
    static GLubyte* readPixels(std::ifstream& file, size_t size);
};

} /* namespace Glycerin */
#endif
