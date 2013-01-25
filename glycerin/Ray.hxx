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
#ifndef GLYCERIN_RAY_HXX
#define GLYCERIN_RAY_HXX
#include <iostream>
#include <m3d/Vec4.h>
#include "glycerin/common.h"
namespace Glycerin {


/**
 * Direction vector emanating from an origin point.
 */
class Ray {
public:
// Attributes
    M3d::Vec4 origin; ///< Origin point
    M3d::Vec4 direction; ///< Direction vector
// Methods
    Ray();
    Ray(const M3d::Vec4& origin, const M3d::Vec4& direction);
};

} /* namespace Glycerin */

std::ostream& operator<<(std::ostream& stream, const Glycerin::Ray& ray);

#endif
