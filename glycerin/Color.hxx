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
#ifndef GLYCERIN_COLOR_HXX
#define GLYCERIN_COLOR_HXX
#include <iostream>
#include "glycerin/common.h"
namespace Glycerin {


/**
 * Four-component color.
 */
class Color {
public:
// Attributes
    GLfloat r; ///< Red component
    GLfloat g; ///< Green component
    GLfloat b; ///< Blue component
    GLfloat a; ///< Alpha component
// Methods
    Color();
    Color(GLfloat r, GLfloat g, GLfloat b);
    Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    static Color fromArray(const GLfloat arr[4]);
    bool operator!=(const Color& color) const;
    bool operator==(const Color& color) const;
    GLfloat operator[](int index) const;
    GLfloat& operator[](int index);
    void toArray(GLfloat arr[4]) const;
private:
// Constants
    static const GLfloat DEFAULT_R = 0.0f;
    static const GLfloat DEFAULT_G = 0.0f;
    static const GLfloat DEFAULT_B = 0.0f;
    static const GLfloat DEFAULT_A = 1.0f;
};

} /* namespace Glycerin */

std::ostream& operator<<(std::ostream& stream, const Glycerin::Color& color);
#endif
