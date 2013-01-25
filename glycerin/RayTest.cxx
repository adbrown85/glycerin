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
#include <sstream>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include "glycerin/Ray.hxx"


/**
 * Unit test for `Ray`.
 */
class RayTest : public CppUnit::TestFixture {
public:

    /**
     * Ensures `operator<<(ostream&, const Ray&)` works correctly.
     */
    void testInsertionOperator() {

        // Make ray
        const M3d::Vec4 origin(1, 2, 3, 1);
        const M3d::Vec4 direction(10, 20, 30, 0);
        const Glycerin::Ray ray(origin, direction);

        // Insert into stream
        std::stringstream stream;
        stream << ray;

        // Check results
        const std::string expected = "[[1, 2, 3, 1], [10, 20, 30, 0]]";
        const std::string actual = stream.str();
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures `Ray::Ray()` works correctly.
     */
    void testRay() {
        const Glycerin::Ray ray;
        CPPUNIT_ASSERT_EQUAL(M3d::Vec4(0, 0, 0, 1), ray.origin);
        CPPUNIT_ASSERT_EQUAL(M3d::Vec4(0, 0, 0, 0), ray.direction);
    }

    /**
     * Ensures `Ray::Ray(const Vec4&, const Vec4&)` works correctly.
     */
    void testRayVec4Vec4() {
        const M3d::Vec4 origin(1, 2, 3, 4);
        const M3d::Vec4 direction(5, 6, 7, 8);
        const Glycerin::Ray ray(origin, direction);
        CPPUNIT_ASSERT_EQUAL(M3d::Vec4(1, 2, 3, 4), ray.origin);
        CPPUNIT_ASSERT_EQUAL(M3d::Vec4(5, 6, 7, 8), ray.direction);
    }

    CPPUNIT_TEST_SUITE(RayTest);
    CPPUNIT_TEST(testInsertionOperator);
    CPPUNIT_TEST(testRay);
    CPPUNIT_TEST(testRayVec4Vec4);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(RayTest::suite());
    runner.run();
    return 0;
}
