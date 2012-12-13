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
#include "config.h"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <m3d/Math.hxx>
#include "glycerin/Projection.hxx"
using namespace std;
namespace Glycerin {


/**
 * Unit test for Projection.
 */
class ProjectionTest : public CppUnit::TestFixture {
public:

    // Threshold for making floating-point comparisons
    static const double TOLERANCE = 1e-6;

    /**
     * Ensures that Projection::orthographic works with 640x480 resolution.
     */
    void testOrthographicWithSixFortyByFourEighty() {

        // Define parameters
        const double width = 640.0;
        const double height = 480.0;
        const double right = width;
        const double left = 0.0;
        const double top = 480.0;
        const double bottom = 0.0;
        const double near = -1.0;
        const double far = +1.0;

        // Compute orthographic projection matrix
        M3d::Mat4 mat = Projection::orthographic(width, height);

        // Check first column
        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0 / (right - left), mat[0][0], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mat[0][1], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mat[0][2], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mat[0][3], TOLERANCE);

        // Check second column
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mat[1][0], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0 / (top - bottom), mat[1][1], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mat[1][2], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mat[1][3], TOLERANCE);

        // Check third column
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mat[2][0], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mat[2][1], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-2.0 / (far - near), mat[2][2], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mat[2][3], TOLERANCE);

        // Check fourth column
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-(right + left) / (right - left), mat[3][0], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-(top + bottom) / (top - bottom), mat[3][1], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-(far + near) / (far - near), mat[3][2], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1, mat[3][3], TOLERANCE);

    }

    /**
     * Ensures that Projection::perspective works with thirty degrees.
     */
    void testPerspectiveWithThirtyDegrees() {

        // Define parameters
        const double fov = 30.0;
        const double aspect = 1.5;
        const double near = 10.0;
        const double far = 100.0;

        // Compute perspective projection matrix
        M3d::Mat4 mat = Projection::perspective(fov, aspect, near, far);

        // Compute f, which is the cotangent of field of view divived by 2
        const double f = 1.0 / tan(M3d::toRadians(fov / 2.0));

        // Check first column
        CPPUNIT_ASSERT_DOUBLES_EQUAL(f / aspect, mat[0][0], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mat[0][1], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mat[0][2], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mat[0][3], TOLERANCE);

        // Check second column
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mat[1][0], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(f, mat[1][1], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mat[1][2], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mat[1][3], TOLERANCE);

        // Check third column
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mat[2][0], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mat[2][1], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL((far + near) / (near - far), mat[2][2], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-1, mat[2][3], TOLERANCE);

        // Check fourth column
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mat[3][0], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mat[3][1], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL((2.0 * far * near) / (near - far), mat[3][2], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0, mat[3][3], TOLERANCE);
    }

    CPPUNIT_TEST_SUITE(ProjectionTest);
    CPPUNIT_TEST(testOrthographicWithSixFortyByFourEighty);
    CPPUNIT_TEST(testPerspectiveWithThirtyDegrees);
    CPPUNIT_TEST_SUITE_END();
};

} /* namespace Glycerin */

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(Glycerin::ProjectionTest::suite());
    runner.run();
    return 0;
}
