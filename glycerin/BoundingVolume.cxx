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
#include "glycerin/BoundingVolume.hxx"
namespace Glycerin {

/**
 * Constructs a bounding volume.
 */
BoundingVolume::BoundingVolume() {
    // empty
}

/**
 * Destructs a bounding volume.
 */
BoundingVolume::~BoundingVolume() {
    // empty
}

/**
 * Intersects the bounding volume with a ray.
 *
 * @param ray Ray to intersect with
 * @return Time along ray of closest intersection, or a negative number if none
 */
double BoundingVolume::intersect(const Ray& ray) const {
    throw std::runtime_error("[BoundingVolume] Pure virtual method called!");
}

} /* namespace Glycerin */
