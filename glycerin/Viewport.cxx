/*
 * Glycerin - Fuel for OpenGL applications
 * Copyright (C) 2013  Andrew Brown
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
#include "glycerin/Viewport.hxx"
namespace Glycerin {

/**
 * Constructs a viewport from a location and size.
 *
 * @param x Left side of area
 * @param y Top of area
 * @param width Width of area
 * @param height Height of area
 * @throws std::invalid_argument if width or height is negative
 */
Viewport::Viewport(GLint x, GLint y, GLint width, GLint height) : _x(x), _y(y), _width(width), _height(height) {
    if ((width < 0) || (height < 0)) {
        throw std::invalid_argument("[Viewport] Width or height is negative!");
    }
}

/**
 * Returns the current OpenGL viewport.
 *
 * @return Current OpenGL viewport
 */
Viewport Viewport::getViewport() {
    GLint arr[4];
    glGetIntegerv(GL_VIEWPORT, arr);
    return Viewport(arr[0], arr[1], arr[2], arr[3]);
}

/**
 * Returns the height of the viewport.
 *
 * @return Height of the viewport
 */
GLint Viewport::height() const {
    return _height;
}

/**
 * Checks if this viewport has different values than another one.
 *
 * @param viewport Viewport to compare
 * @return `true` if other viewport has different values than this one
 */
bool Viewport::operator!=(const Viewport& viewport) const {
    return !((*this) == viewport);
}

/**
 * Checks if this viewport has the same values as another one.
 *
 * @param viewport Viewport to compare
 * @return `true` if other viewport has the same values as this one
 */
bool Viewport::operator==(const Viewport& viewport) const {
    if ((_x != viewport._x) || (_y != viewport._y)) {
        return false;
    }
    if ((_width != viewport._width) || (_height != viewport._height)) {
        return false;
    }
    return true;
}

/**
 * Returns the width of the viewport.
 *
 * @return Width of the viewport
 */
GLint Viewport::width() const {
    return _width;
}

/**
 * Returns the left side of the viewport.
 *
 * @return Left side of the viewport
 */
GLint Viewport::x() const {
    return _x;
}

/**
 * Returns the top of the viewport.
 *
 * @return Top of the viewport
 */
GLint Viewport::y() const {
    return _y;
}

} /* namespace Glycerin */

std::ostream& operator<<(std::ostream& stream, const Glycerin::Viewport& viewport) {
    stream << '[';
    stream << viewport.x() << ", ";
    stream << viewport.y() << ", ";
    stream << viewport.width() << ", ";
    stream << viewport.height();
    stream << ']';
    return stream;
}
