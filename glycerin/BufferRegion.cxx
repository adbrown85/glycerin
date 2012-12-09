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
#include <stdexcept>
#include "glycerin/BufferRegion.hxx"
using namespace std;
namespace Glycerin {

/**
 * Returns the number of components per vector in the region, in the range one to four.
 */
GLsizei BufferRegion::components() const {
    return _components;
}

/**
 * Returns the total number of vectors in the region, numbering at least one.
 */
GLuint BufferRegion::count() const {
    return _count;
}

/**
 * Returns the name of the region.
 */
string BufferRegion::name() const {
    return _name;
}

/**
 * Returns whether vector components in the region should be normalized.
 */
bool BufferRegion::normalized() const {
    return _normalized;
}

/**
 * Returns the number of bytes before the first vector in the region.
 */
GLsizei BufferRegion::offset() const {
    return _offset;
}

/**
 * Returns the number of bytes between consecutive vectors in the region.
 */
GLsizei BufferRegion::stride() const {
    return _stride;
}

/**
 * Returns the base type of the components in each vector in the region, such as `GL_FLOAT`.
 */
GLenum BufferRegion::type() const {
    return _type;
}

} /* namespace Glycerin */
