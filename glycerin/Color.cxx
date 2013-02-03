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
#include <algorithm>
#include <stdexcept>
#include "glycerin/Color.hxx"
namespace Glycerin {

/**
 * Constructs a color from the default values.
 */
Color::Color() : r(DEFAULT_R), g(DEFAULT_G), b(DEFAULT_B), a(DEFAULT_A) {
    // empty
}

/**
 * Constructs a color from red, green, and blue components.
 *
 * @param r Red component
 * @param g Green component
 * @param b Blue component
 */
Color::Color(const GLfloat r, const GLfloat g, const GLfloat b) : r(r), g(g), b(b), a(DEFAULT_A) {
    // empty
}

/**
 * Constructs a color from red, green, blue, and alpha components.
 *
 * @param r Red component
 * @param g Green component
 * @param b Blue component
 * @param a Alpha component
 */
Color::Color(const GLfloat r, const GLfloat g, const GLfloat b, const GLfloat a) : r(r), g(g), b(b), a(a) {
    // empty
}

/**
 * Creates a color by copying the values of an array.
 *
 * @param arr Array to copy values from
 * @return Color with copies of values in array
 */
Color Color::fromArray(const GLfloat arr[4]) {
    return Color(arr[0], arr[1], arr[2], arr[3]);
}

/**
 * Checks if another color does not equal this color exactly.
 *
 * @param color Color to compare to
 * @return `true` if the other color
 */
bool Color::operator!=(const Color& color) const {
    return !((*this) == color);
}

/**
 * Checks if another color equals this color exactly.
 *
 * @param color Color to compare to
 * @return `true` if the other color equals this color exactly
 */
bool Color::operator==(const Color& color) const {
    return (r == color.r) && (g == color.g) && (b == color.b) && (a == color.a);
}

/**
 * Returns the value of a component given its index.
 *
 * @param index Index of component, in the range [0 .. 3]
 * @return Copy of the component
 * @throws std::invalid_argument if index is out of range
 */
GLfloat Color::operator[](const int index) const {
    switch (index) {
    case 0: return r;
    case 1: return g;
    case 2: return b;
    case 3: return a;
    default:
        throw std::invalid_argument("[Color] Index is out of range!");
    }
}

/**
 * Returns a reference to a component given its index.
 *
 * @param index Index of component, in the range [0 .. 3]
 * @return Reference to the component
 * @throws std::invalid_argument if index is out of range
 */
GLfloat& Color::operator[](const int index) {
    switch (index) {
    case 0: return r;
    case 1: return g;
    case 2: return b;
    case 3: return a;
    default:
        throw std::invalid_argument("[Color] Index is out of range!");
    }
}

/**
 * Copies this color's components to an array.
 *
 * @param arr Array to copy to
 */
void Color::toArray(GLfloat arr[4]) const {
    arr[0] = r;
    arr[1] = g;
    arr[2] = b;
    arr[3] = a;
}

} /* namespace Glycerin */

/**
 * Inserts a color into a stream.
 *
 * @param stream Stream to insert color into
 * @param color Color to insert into stream
 * @return Reference to the stream to support chaining
 */
std::ostream& operator<<(std::ostream& stream, const Glycerin::Color& color) {
    stream << '[' << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ']';
    return stream;
}
