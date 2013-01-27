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
#include <limits>
#include <stdexcept>
#include "glycerin/AxisAlignedBoundingBox.hxx"
namespace Glycerin {

/**
 * Constructs an axis-aligned bounding box from minimum and maximum corners.
 *
 * @param min Minimum corner of bounding box
 * @param max Maximum corner of bounding box
 * @throws std::invalid_argument if minimum corner has a component greater than corresponding maximum component
 */
AxisAlignedBoundingBox::AxisAlignedBoundingBox(const M3d::Vec4& min, const M3d::Vec4& max) : min(min), max(max) {
    for (int i = 0; i < 3; ++i) {
        if (min[i] > max[i]) {
            throw std::invalid_argument("[AxisAlignedBoundingBox] Minimum is greater than maximum!");
        }
    }
}

/**
 * Destructs an axis-aligned bounding box.
 */
AxisAlignedBoundingBox::~AxisAlignedBoundingBox() {
    // empty
}

/**
 * Returns the maximum corner of this axis-aligned bounding box.
 *
 * @return Maximum corner of this axis-aligned bounding box
 */
M3d::Vec4 AxisAlignedBoundingBox::getMax() const {
    return max;
}

/**
 * Returns the minimum corner of this axis-aligned bounding box.
 *
 * @return Minimum corner of this axis-aligned bounding box
 */
M3d::Vec4 AxisAlignedBoundingBox::getMin() const {
    return min;
}

double AxisAlignedBoundingBox::intersect(const Ray& ray) const {
    double tMin = -std::numeric_limits<double>::infinity();
    double tMax = +std::numeric_limits<double>::infinity();
    for (int i = 0; i < 3; ++i) {
        const double o = ray.origin[i];
        const double d = ray.direction[i];
        if (fabs(d) > EPSILON) {
            double t1 = (min[i] - o) / d;
            double t2 = (max[i] - o) / d;
            if (t1 > t2) {
                std::swap(t1, t2);
            }
            tMin = std::max(tMin, t1);
            tMax = std::min(tMax, t2);
            if (tMin > tMax) {
                return -1.0;
            }
        } else if ((o < min[i]) || (o > max[i])) {
            return -1.0;
        }
    }
    return (tMin > 0) ? tMin : tMax;
}

} /* namespace Glycerin */
