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
#ifndef GLYCERIN_BOUNDING_VOLUME_HXX
#define GLYCERIN_BOUNDING_VOLUME_HXX
#include "glycerin/common.h"
#include "glycerin/Ray.hxx"
namespace Glycerin {


/**
 * Simple shape used for intersection tests.
 */
class BoundingVolume {
public:
// Methods
    BoundingVolume();
    virtual double intersect(const Ray& ray) const = 0;
protected:
// Methods
    virtual ~BoundingVolume();
};

} /* namesapce Glycerin */
#endif
