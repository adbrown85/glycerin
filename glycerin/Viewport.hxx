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
#ifndef GLYCERIN_VIEWPORT_HXX
#define GLYCERIN_VIEWPORT_HXX
#include <iostream>
#include "glycerin/common.h"
namespace Glycerin {


/**
 * Area of window being rendered to.
 */
class Viewport {
public:
// Methods
    Viewport(GLint x, GLint y, GLint width, GLint height);
    static Viewport getViewport();
    GLint height() const;
    bool operator!=(const Viewport& viewport) const;
    bool operator==(const Viewport& viewport) const;
    GLint width() const;
    GLint x() const;
    GLint y() const;
private:
// Attributes
    GLint _x;
    GLint _y;
    GLint _width;
    GLint _height;
};

} /* namespace Glycerin */

std::ostream& operator<<(std::ostream& stream, const Glycerin::Viewport& viewport);

#endif
