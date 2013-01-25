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
#include "glycerin/Ray.hxx"
namespace Glycerin {

/**
 * Constructs a degenerate ray.
 */
Ray::Ray() : origin(0, 0, 0, 1), direction(0, 0, 0, 0) {
    // empty
}

/**
 * Constructs a ray from an origin and direction.
 *
 * @param origin Origin point
 * @param direction Direction vector
 */
Ray::Ray(const M3d::Vec4& origin, const M3d::Vec4& direction) : origin(origin), direction(direction) {
    // empty
}

} /* namespace Glycerin */

/**
 * Inserts a ray's origin and direction into a stream.
 *
 * @param stream Stream to insert ray origin and direction into
 * @param ray Ray to insert
 * @return Reference to the stream to support chaining
 */
std::ostream& operator<<(std::ostream& stream, const Glycerin::Ray& ray) {
    stream << '[';
    stream << ray.origin;
    stream << ", ";
    stream << ray.direction;
    stream << ']';
    return stream;
}
