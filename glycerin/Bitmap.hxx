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
#ifndef GLYCERIN_BITMAP_HXX
#define GLYCERIN_BITMAP_HXX
#include "glycerin/common.h"
#include <fstream>
namespace Glycerin {


/**
 * Bitmap image.
 *
 * To get a _Bitmap_, pass the path of a bitmap file to [read].
 *
 * ~~~
 * BitmapReader reader;
 * Bitmap bitmap = reader.read("image.bmp");
 * ~~~
 *
 * After you have a _Bitmap_, you can determine its dimensions using the
 * [get-width] and [get-height] methods.
 *
 * ~~~
 * GLsizei width = bitmap.getWidth();
 * GLsizei height = bitmap.getHeight();
 * ~~~
 *
 * To get a copy of the bitmap's pixel data, use [get-size] and [get-pixels].
 * You will need to make a new byte array for the bitmap to copy the pixel data
 * into.
 *
 * ~~~
 * GLsizei size = bitmap.getSize();
 * GLubyte* pixels = new GLubyte[size];
 * bitmap.getPixels(pixels, size);
 * ~~~
 *
 * To make a texture out of the bitmap, set the pixel store alignment to that
 * of the bitmap's alignment using [glPixelStore] and [get-alignment] then use
 * [glTexImage2D] to copy the bitmap's pixel data into texture memory.  Use the
 * value returned by [get-format] to specify the format of the pixel data from
 * the image, and `GL_UNSIGNED_BYTE` for its type.  Use [glGenerateMipmap] to
 * automatically generate mipmaps for the texture.
 *
 * ~~~
 * glPixelStorei(GL_UNPACK_ALIGNMENT, bitmap.getAlignment());
 * glTexImage2D(
 *         GL_TEXTURE_2D,       // target
 *         0,                   // level
 *         GL_RGB,              // internal format
 *         width,               // width
 *         height,              // height
 *         0,                   // border
 *         bitmap.getFormat(),  // format
 *         GL_UNSIGNED_BYTE,    // type
 *         pixels);             // data
 * glGenerateMipmap(GL_TEXTURE_2D);
 * ~~~
 *
 * [get-alignment]: @ref getAlignment() const "getAlignment()"
 * [get-format]: @ref getFormat() const "getFormat()"
 * [get-height]: @ref getHeight() const "getHeight()"
 * [get-pixels]: @ref getPixels(GLubyte*, GLsizei) const "getPixels(GLubyte*, GLsizei)"
 * [get-size]: @ref getSize() const "getSize()"
 * [get-width]: @ref getWidth() const "getWidth()"
 * [glGenerateMipmap]: http://http://www.opengl.org/sdk/docs/man3/xhtml/glGenerateMipmap.xml
 * [glPixelStore]: http://www.opengl.org/sdk/docs/man3/xhtml/glPixelStore.xml
 * [glTexImage2D]: http://www.opengl.org/sdk/docs/man3/xhtml/glTexImage2D.xml
 * [read]: @ref BitmapReader::read(const std::string&) "BitmapReader::read(const std::string&)"
 */
class Bitmap {
// Friends
    friend class BitmapReader;
public:
// Methods
    Bitmap(const Bitmap& bitmap);
    virtual ~Bitmap();
    GLint getAlignment() const;
    GLenum getFormat() const;
    GLsizei getWidth() const;
    GLsizei getHeight() const;
    void getPixels(GLubyte* arr, GLsizei size) const;
    GLsizei getSize() const;
    Bitmap& operator=(const Bitmap& bitmap);
private:
// Constants
    static const GLenum DEFAULT_FORMAT = GL_BGR;
    static const GLint DEFAULT_ALIGNMENT = 4;
// Attributes
    GLubyte* pixels;
    GLenum format;
    GLsizei width, height;
    GLsizei size;
    GLint alignment;
// Methods
    Bitmap();
    static GLubyte* copyPixels(const Bitmap& bitmap);
};

} /* namespace Glycerin */
#endif
