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
#include "config.h"
#include "glycerin/common.h"
#include <stdexcept>
#include "glycerin/Bitmap.hxx"
using namespace std;
namespace Glycerin {

/**
 * Constructs an empty bitmap image.
 */
Bitmap::Bitmap() {
    this->pixels = NULL;
    this->format = DEFAULT_FORMAT;
    this->width = 0;
    this->height = 0;
    this->size = 0;
    this->alignment = DEFAULT_ALIGNMENT;
}

/**
 * Constructs a bitmap by copying another bitmap.
 *
 * @param bitmap Bitmap to copy
 */
Bitmap::Bitmap(const Bitmap& bitmap) {
    (*this) = bitmap;
}

/**
 * Destroys the bitmap image.
 */
Bitmap::~Bitmap() {
    if (pixels != NULL) {
        delete[] pixels;
    }
}

/**
 * Copies the pixels of a bitmap.
 *
 * @param bitmap Bitmap to copy pixels of
 * @return Pointer to a newly-allocated array containing the same pixels as the bitmap
 */
GLubyte* Bitmap::copyPixels(const Bitmap& bitmap) {
    GLubyte* const copy = new GLubyte[bitmap.size];
    memcpy(copy, bitmap.pixels, bitmap.size);
    return copy;
}

/**
 * Returns the number of bytes that row length should be multiples of.
 *
 * @return Number of bytes that row length should be multiples of
 */
GLint Bitmap::getAlignment() const {
    return alignment;
}

/**
 * Returns the format of the image, either `GL_RGB` or `GL_RGBA`.
 *
 * @return Format of the image, either `GL_RGB` or `GL_RGBA`
 */
GLenum Bitmap::getFormat() const {
    return format;
}

/**
 * Returns the size of the image in the Y direction.
 *
 * @return Size of the image in the Y direction
 */
GLsizei Bitmap::getHeight() const {
    return height;
}

/**
 * Copies pixel data to an array of bytes.
 *
 * @param arr Pointer to array to store pixel data in
 * @param size Size of the array
 * @throws invalid_argument if array is `NULL` or size is too small
 */
void Bitmap::getPixels(GLubyte* const arr, const GLsizei size) const {

    if (arr == NULL) {
        throw invalid_argument("[BitmapReader] Array is NULL!");
    }

    if (size < this->size) {
        throw invalid_argument("[BitmapReader] Array is too small!");
    }

    memcpy(arr, pixels, this->size);
}

/**
 * Returns the total number of bytes required to hold the pixel data of this image.
 *
 * @return Total number of bytes required to hold the pixel data of this image
 */
GLsizei Bitmap::getSize() const {
    return size;
}

/**
 * Returns the size of the image in the X direction.
 *
 * @return Size of the image in the X direction
 */
GLsizei Bitmap::getWidth() const {
    return width;
}

/**
 * Changes this bitmap to be a copy of another bitmap.
 *
 * @param bitmap Bitmap to copy
 * @return Reference to this bitmap to support chaining
 */
Bitmap& Bitmap::operator=(const Bitmap& bitmap) {
    this->pixels = copyPixels(bitmap);
    this->format = bitmap.format;
    this->width = bitmap.width;
    this->height = bitmap.height;
    this->size = bitmap.size;
    this->alignment = bitmap.alignment;
}

} /* namespace Glycerin */
