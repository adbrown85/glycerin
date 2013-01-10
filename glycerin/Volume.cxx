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
#include <cassert>
#include <stdexcept>
#include <gloop/TextureTarget.hxx>
#include "glycerin/Volume.hxx"
namespace Glycerin {

/**
 * Constructs an empty volume.
 */
Volume::Volume() : data(NULL) {
    // empty
}

/**
 * Constructs a volume by copying another volume.
 *
 * @param volume Volume to copy
 */
Volume::Volume(const Volume& volume) :
        data(copy(volume.data, volume.getLength())),
        endianness(volume.endianness),
        pitch(volume.pitch),
        size(volume.size),
        type(type) {
    // empty
}

/**
 * Destructs a volume.
 */
Volume::~Volume() {
    delete[] data;
}

/**
 * Creates a new copy of data.
 *
 * @param data Pointer to the data to copy
 * @param len Size of the data in bytes
 * @return Pointer to the new copy of the data, owned by the caller
 */
GLubyte* Volume::copy(const GLubyte* data, const size_t len) {
    if ((data == NULL) || (len == 0)) {
        return NULL;
    } else {
        GLubyte* copy = new GLubyte[len];
        memcpy(copy, data, len);
        return copy;
    }
}

/**
 * Creates a new three-dimensional texture on the current texture unit from this volume's data.
 *
 * @return Handle for the new texture
 */
Gloop::TextureObject Volume::createTexture() const {

    // Create a texture
    const Gloop::TextureObject texture = Gloop::TextureObject::generate();

    // Bind the texture
    const Gloop::TextureTarget texture3d = Gloop::TextureTarget::texture3d();
    texture3d.bind(texture);

    // Store unpack alignment
    const GLenum lastAlignment = getUnpackAlignment();

    // Load the data
    setUnpackAlignment(1);
    texture3d.texImage3d(
            0,           // level
            GL_RED,      // internal format
            size.width,  // width
            size.height, // height
            size.depth,  // depth
            GL_RED,      // format
            type,        // type
            data);       // data

    // Reset unpack alignment
    setUnpackAlignment(lastAlignment);

    // Set the minification and magnification filters
    texture3d.minFilter(GL_NEAREST);
    texture3d.magFilter(GL_NEAREST);

    // Return the texture
    return texture;
}

/**
 * Copies this volume's data to memory.
 *
 * @param ptr Pointer to memory to copy to
 * @throws std::invalid_argument if pointer is `NULL`
 */
void Volume::getData(GLubyte* ptr) const {
    if (ptr == NULL) {
        throw std::invalid_argument("[Volume] Pointer is NULL!");
    }
    memcpy(ptr, data, getLength());
}

/**
 * Returns how many samples this volume has in the Z direction.
 *
 * @return How many samples this volume has in the Z direction
 */
GLsizei Volume::getDepth() const {
    return size.depth;
}

/**
 * Returns the endianness of the data in this volume.
 *
 * @return Endianness of the data in this volume, either _big_ or _little_
 */
std::string Volume::getEndianness() const {
    return endianness;
}

/**
 * Returns how many samples this volume has in the Y direction.
 *
 * @return How many samples this volume has in the Y direction
 */
GLsizei Volume::getHeight() const {
    return size.height;
}

/**
 * Returns the length of an array needed to hold this volume's data.
 *
 * @return Length of an array needed to hold this volume's data
 */
GLsizei Volume::getLength() const {
    return size.width * size.height * size.depth * sizeOf(type);
}

/**
 * Returns the spacing between samples in the X direction.
 *
 * @return Spacing between samples in the X direction
 */
GLfloat Volume::getPitchX() const {
    return pitch.x;
}

/**
 * Returns the spacing between samples in the Y direction.
 *
 * @return Spacing between samples in the Y direction
 */
GLfloat Volume::getPitchY() const {
    return pitch.y;
}

/**
 * Returns the spacing between samples in the Z direction.
 *
 * @return Spacing between samples in the Z direction
 */
GLfloat Volume::getPitchZ() const {
    return pitch.z;
}

/**
 * Returns the type of the data in this volume.
 *
 * @return Type of the data in this volume
 */
GLenum Volume::getType() const {
    return type;
}

/**
 * Returns the current value of `GL_UNPACK_ALIGNMENT`.
 *
 * @return Current value of `GL_UNPACK_ALIGNMENT`
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glGet.xml
 */
GLenum Volume::getUnpackAlignment() {
    GLint value;
    glGetIntegerv(GL_UNPACK_ALIGNMENT, &value);
    return (GLenum) value;
}

/**
 * Returns the number of samples in the X direction.
 *
 * @return Number of samples in the X direction
 */
GLsizei Volume::getWidth() const {
    return size.width;
}

/**
 * Checks if an enumeration represents a valid value for `GL_UNPACK_ALIGNMENT`.
 *
 * @param enumeration Enumeration to check
 * @return `true` if enumeration is a valid value for `GL_UNPACK_ALIGNMENT`
 * @see http://www.opengl.org/sdk/docs/man3/xhtml/glPixelStore.xml
 */
bool Volume::isUnpackAlignment(const GLenum enumeration) {
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
 * Changes the alignment used for reading data from client memory.
 *
 * @param alignment Alignment used for reading data from client memory
 */
void Volume::setUnpackAlignment(const GLenum alignment) {
    assert (isUnpackAlignment(alignment));
    glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
}

/**
 * Computes the size of a data type in bytes.
 *
 * @param type Data type to compute size of
 * @return Size of type in bytes
 * @throws std::runtime_error if type is unexpected
 */
GLsizei Volume::sizeOf(GLenum type) {
    switch (type) {
    case GL_UNSIGNED_BYTE:
        return 1;
    case GL_SHORT:
    case GL_UNSIGNED_SHORT:
        return 2;
    case GL_FLOAT:
        return 4;
    default:
        throw std::runtime_error("[Volume] Unexpected type!");
    }
}

} /* namespace Glycerin */
