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
#include <cassert>
#include <stdexcept>
#include <gloop/TextureTarget.hxx>
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
 * Creates a new OpenGL texture on the current texture unit from this bitmap.
 *
 * Rather than manually creating a texture from the bitmap, it may sometimes be more
 * convenient to simply let the bitmap do it itself.  For that reason
 * `createTexture` will generate a new texture, bind it to the current OpenGL
 * texture unit, and copy the pixel data into the texture.  If `mipmaps` is `true`
 * mipmaps will automatically be generated using `glGenerateMipmap`.  Note that this
 * method will use `glPixelStorei` to specify the correct alignment, but will reset
 * it to what it was originally.  After this method returns, the texture will still
 * be bound to the texture unit.
 *
 * @param mipmaps Whether to automatically generate mipmaps, by default `true`
 * @return Handle for the new OpenGL texture
 * @throws runtime_error if texture could not be generated
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGenerateMipmap.xml
 */
Gloop::TextureObject Bitmap::createTexture(const bool mipmaps) const {

    // Generate a new texture
    const Gloop::TextureObject texture = Gloop::TextureObject::generate();
    assert (texture.id() > 0);

    // Bind texture
    const Gloop::TextureTarget target = Gloop::TextureTarget::texture2d();
    target.bind(texture);

    // Store unpack alignment
    const GLenum lastAlignment = getUnpackAlignment();

    // Load texture data
    setUnpackAlignment(alignment);
    target.texImage2d(
                0,                // level
                GL_RGB,           // internal format
                width,            // width
                height,           // height
                format,           // format
                GL_UNSIGNED_BYTE, // type
                pixels);          // data

    // Reset unpack alignment
    setUnpackAlignment(lastAlignment);

    // Generate mipmaps
    if (mipmaps) {
        target.generateMipmap();
    }

    // Return texture object
    return texture;
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
 * Returns the current value of `GL_UNPACK_ALIGNMENT`.
 *
 * @return Current value of `GL_UNPACK_ALIGNMENT`
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGet.xml
 */
GLenum Bitmap::getUnpackAlignment() {
    GLint value;
    glGetIntegerv(GL_UNPACK_ALIGNMENT, &value);
    return (GLenum) value;
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
 * Checks if an enumeration represents a valid value for `GL_UNPACK_ALIGNMENT`.
 *
 * @param enumeration Enumeration to check
 * @return `true` if enumeration is a valid value for `GL_UNPACK_ALIGNMENT`
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glPixelStore.xml
 */
bool Bitmap::isUnpackAlignment(const GLenum enumeration) {
    switch (enumeration) {
    case 1: // byte alignment
    case 2: // rows aligned to even-numbered bytes
    case 4: // word-alignment
    case 8: // rows start on double-word boundaries
        return true;
    default:
        return false;
    }
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

/**
 * Changes the alignment used for reading data from client memory.
 *
 * @param alignment Alignment used for reading data from client memory
 */
void Bitmap::setUnpackAlignment(const GLenum alignment) {
    assert (isUnpackAlignment(alignment));
    glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
}

} /* namespace Glycerin */
