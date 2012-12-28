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
#ifndef GLYCERIN_BUFFERREGION_HXX
#define GLYCERIN_BUFFERREGION_HXX
#include "glycerin/common.h"
namespace Glycerin {


/**
 * Section in a buffer.
 *
 * @ingroup extensions
 */
class BufferRegion {
public:
// Methods
    GLsizei components() const;
    GLuint count() const;
    std::string name() const;
    bool normalized() const;
    GLsizei offset() const;
    GLsizei sizeInBytes() const;
    GLsizei stride() const;
    GLenum type() const;
private:
// Attributes
    GLsizei _components;
    GLuint _count;
    std::string _name;
    bool _normalized;
    GLsizei _offset;
    GLsizei _stride;
    GLenum _type;
// Methods
    static GLsizei sizeOf(GLenum type);
// Friends
    friend class BufferLayout;
    friend class BufferLayoutBuilder;
};

} /* namespace Glycerin */
#endif
