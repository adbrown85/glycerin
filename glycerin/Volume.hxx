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
#ifndef GLYCERIN_VOLUME_HXX
#define GLYCERIN_VOLUME_HXX
#include <string>
#include <gloop/TextureObject.hxx>
#include "glycerin/common.h"
namespace Glycerin {


/**
 * Dataset for a three-dimensional texture.
 */
class Volume {
public:
// Methods
    Volume(const Volume& volume);
    ~Volume();
    Gloop::TextureObject createTexture() const;
    void getData(GLubyte* ptr) const;
    GLsizei getDepth() const;
    std::string getEndianness() const;
    GLsizei getHeight() const;
    GLsizei getLength() const;
    GLfloat getPitchX() const;
    GLfloat getPitchY() const;
    GLfloat getPitchZ() const;
    GLenum getType() const;
    GLsizei getWidth() const;
private:
// Types
    struct Pitch {
        Pitch() : x(0), y(0), z(0) { }
        GLfloat x;
        GLfloat y;
        GLfloat z;
    };
    struct Size {
        Size() : width(0), height(0), depth(0) { }
        GLsizei width;
        GLsizei height;
        GLsizei depth;
    };
// Attributes
    GLubyte* data;
    std::string endianness;
    Pitch pitch;
    Size size;
    GLenum type;
// Methods
    Volume();
    Volume& operator=(const Volume& volume);
    static GLubyte* copy(const GLubyte* source, size_t len);
    static GLenum getUnpackAlignment();
    static bool isUnpackAlignment(GLenum enumeration);
    static void setUnpackAlignment(GLenum unpackAlignment);
    static GLsizei sizeOf(const GLenum type);
// Friends
    friend class VolumeReader;
};

}
#endif
