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
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <glycerin/AxisAlignedBoundingBox.hxx>
#include <glycerin/Ray.hxx>


/**
 * Unit test for `AxisAlignedBoundingBox`.
 */
class AxisAlignedBoundingBoxTest : public CppUnit::TestFixture {
public:

    // Threshold for floating-point comparisons
    static const double TOLERANCE = 1e-6;

    /**
     * Ensures constructor throws if given invalid X components.
     */
    void testAxisAlignedBoundingBoxVec4Vec4WithInvalidX() {
        const M3d::Vec4 min(+1, 0, 0, 1);
        const M3d::Vec4 max(-1, 0, 0, 1);
        CPPUNIT_ASSERT_THROW(Glycerin::AxisAlignedBoundingBox(min, max), std::invalid_argument);
    }

    /**
     * Ensures constructor throws if given invalid Y components.
     */
    void testAxisAlignedBoundingBoxVec4Vec4WithInvalidY() {
        const M3d::Vec4 min(0, +1, 0, 1);
        const M3d::Vec4 max(0, -1, 0, 1);
        CPPUNIT_ASSERT_THROW(Glycerin::AxisAlignedBoundingBox(min, max), std::invalid_argument);
    }

    /**
     * Ensures constructor throws if given invalid Z components.
     */
    void testAxisAlignedBoundingBoxVec4Vec4WithInvalidZ() {
        const M3d::Vec4 min(0, 0, +1, 1);
        const M3d::Vec4 max(0, 0, -1, 1);
        CPPUNIT_ASSERT_THROW(Glycerin::AxisAlignedBoundingBox(min, max), std::invalid_argument);
    }

    /**
     * Ensures `AxisAlignedBoundingBox::intersect` works with a decreasing ray direction.
     */
    void testIntersectWithDecreasingRayDirection() {

        // Make bounding box
        const M3d::Vec4 min(4, 6, -1.5, 1);
        const M3d::Vec4 max(7, 9, +1.5, 1);
        const Glycerin::AxisAlignedBoundingBox aabb(min, max);

        // Make ray
        const M3d::Vec4 origin(10, 12, 0, 1);
        const M3d::Vec4 direction(-1, -2, 0, 0);
        const Glycerin::Ray ray(origin, direction);

        // Check intersection
        const double t = aabb.intersect(ray);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(3.0, t, TOLERANCE);
    }

    /**
     * Ensures `AxisAlignedBoundingBox::intersect` works with a degenerate box.
     */
    void testIntersectWithDegenerateBox() {

        // Make bounding box
        const M3d::Vec4 min(4, 6, 0, 1);
        const M3d::Vec4 max(7, 9, 0, 1);
        const Glycerin::AxisAlignedBoundingBox aabb(min, max);

        // Make ray
        const M3d::Vec4 origin(3, 2, 0, 1);
        const M3d::Vec4 direction(1, 2, 0, 0);
        const Glycerin::Ray ray(origin, direction);

        // Check intersection
        const double t = aabb.intersect(ray);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(2, t, TOLERANCE);
    }

    /**
     * Ensures `AxisAlignedBoundingBox::intersect` works when all ray direction are increasing.
     */
    void testIntersectWithIncreasingRayDirection() {

        // Make bounding box
        const M3d::Vec4 min(4, 6, -1.5, 1);
        const M3d::Vec4 max(7, 9, +1.5, 1);
        const Glycerin::AxisAlignedBoundingBox aabb(min, max);

        // Make ray
        const M3d::Vec4 origin(3, 2, 0, 1);
        const M3d::Vec4 direction(1, 2, 0, 0);
        const Glycerin::Ray ray(origin, direction);

        // Check intersection
        const double t = aabb.intersect(ray);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, t, TOLERANCE);
    }

    /**
     * Ensures `AxisAlignedBoundingBox::intersect` works with a miss.
     */
    void testIntersectWithMiss() {

        // Make bounding box
        const M3d::Vec4 min(4, 6, -1.5, 1);
        const M3d::Vec4 max(7, 9, +1.5, 1);
        const Glycerin::AxisAlignedBoundingBox aabb(min, max);

        // Make ray
        const M3d::Vec4 origin(3, 2, 0, 1);
        const M3d::Vec4 direction(2, 1, 0, 0);
        const Glycerin::Ray ray(origin, direction);

        // Check intersection
        const double t = aabb.intersect(ray);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, t, TOLERANCE);
    }

    /**
     * Ensures `AxisAlignedBoundingBox::intersect` works when the ray's origin is in the box.
     */
    void testIntersectWithRayOriginInBox() {

        // Make bounding box
        const M3d::Vec4 min(4, 6, -1.5, 1);
        const M3d::Vec4 max(7, 9, +1.5, 1);
        const Glycerin::AxisAlignedBoundingBox aabb(min, max);

        // Make ray
        const M3d::Vec4 origin(5.5, 7.5, 0, 1);
        const M3d::Vec4 direction(2, 1, 0, 0);
        const Glycerin::Ray ray(origin, direction);

        // Check intersection
        const double t = aabb.intersect(ray);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.75, t, TOLERANCE);
    }

    /**
     * Ensures `AxisAlignedBoundingBox::intersect` works with a straight ray direction.
     */
    void testIntersectWithStraightRayDirection() {

        // Make bounding box
        const M3d::Vec4 min(4, 6, -1.5, 1);
        const M3d::Vec4 max(7, 9, +1.5, 1);
        const Glycerin::AxisAlignedBoundingBox aabb(min, max);

        // Make ray
        const M3d::Vec4 origin(5.5, 2, 0, 1);
        const M3d::Vec4 direction(0, 1, 0, 0);
        const Glycerin::Ray ray(origin, direction);

        // Check intersection
        const double t = aabb.intersect(ray);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(4, t, TOLERANCE);
    }

    CPPUNIT_TEST_SUITE(AxisAlignedBoundingBoxTest);
    CPPUNIT_TEST(testAxisAlignedBoundingBoxVec4Vec4WithInvalidX);
    CPPUNIT_TEST(testAxisAlignedBoundingBoxVec4Vec4WithInvalidY);
    CPPUNIT_TEST(testAxisAlignedBoundingBoxVec4Vec4WithInvalidZ);
    CPPUNIT_TEST(testIntersectWithDecreasingRayDirection);
    CPPUNIT_TEST(testIntersectWithDegenerateBox);
    CPPUNIT_TEST(testIntersectWithIncreasingRayDirection);
    CPPUNIT_TEST(testIntersectWithMiss);
    CPPUNIT_TEST(testIntersectWithRayOriginInBox);
    CPPUNIT_TEST(testIntersectWithStraightRayDirection);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(AxisAlignedBoundingBoxTest::suite());
    runner.run();
    return 0;
}
