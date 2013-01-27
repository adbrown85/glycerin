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
#ifndef GLYCERIN_AXIS_ALIGNED_BOUNDING_BOX_HXX
#define GLYCERIN_AXIS_ALIGNED_BOUNDING_BOX_HXX
#include "glycerin/common.h"
#include "glycerin/BoundingVolume.hxx"
#include "glycerin/Ray.hxx"
namespace Glycerin {


/**
 * Axis-aligned bounding box.
 */
class AxisAlignedBoundingBox : public BoundingVolume {
public:
// Methods
    AxisAlignedBoundingBox(const M3d::Vec4& min, const M3d::Vec4& max);
    virtual ~AxisAlignedBoundingBox();
    M3d::Vec4 getMax() const;
    M3d::Vec4 getMin() const;
    virtual double intersect(const Ray& ray) const;
private:
// Constants
    static const double EPSILON = 1e-6;
// Attributes
    M3d::Vec4 min;
    M3d::Vec4 max;
};

} /* namespace Glycerin */
#endif
