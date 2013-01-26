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
#ifndef GLYCERIN_PROJECTION_HXX
#define GLYCERIN_PROJECTION_HXX
#include "glycerin/common.h"
#include <m3d/Mat4.h>
namespace Glycerin {


/**
 * Utility for calculating projection matrices.
 */
class Projection {
public:
// Methods
    static M3d::Mat4 orthographic(int width, int height);
    static M3d::Mat4 perspective(double fovy, double aspect, double zNear, double zFar);
private:
// Methods
    Projection();
};

} /* namespace Glycerin */
#endif
