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
#include <m3d/Math.h>
#include <m3d/Mat4.h>
#include <m3d/Vec3.h>
#include <m3d/Vec4.h>
#include "glycerin/Projection.hxx"
#include "glycerin/Viewport.hxx"
using namespace std;


/**
 * Unit test for Projection.
 */
class ProjectionTest : public CppUnit::TestFixture {
public:

    // Threshold for making floating-point comparisons
    static const double TOLERANCE = 1e-6;

    // Threshold for floating-point comparisons that should be approximate
    static const double LOOSE_TOLERANCE = 1e-2;

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
        M3d::Mat4 mat = Glycerin::Projection::orthographic(width, height);

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
        M3d::Mat4 mat = Glycerin::Projection::perspective(fov, aspect, near, far);

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

    /**
     * Ensures `Projection::unProject` works correctly with identity matrix and back of viewport.
     */
    void testUnProjectWithIdentityAndBack() {

        // Make parameters
        const Glycerin::Viewport viewport(0, 0, 640, 480);
        const M3d::Mat4 imvp(1.0);
        const M3d::Vec3 win(319, 479 - 239, 0.0);

        // Check results
        const M3d::Vec4 actual = Glycerin::Projection::unProject(win, imvp, viewport);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, actual.x, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, actual.y, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, actual.z, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, actual.w, LOOSE_TOLERANCE);
    }

    /**
     * Ensures `Projection::unProject` works correctly with identity matrix and bottom of viewport.
     */
    void testUnProjectWithIdentityAndBottom() {

        // Make parameters
        const Glycerin::Viewport viewport(0, 0, 640, 480);
        const M3d::Mat4 imvp(1.0);
        const M3d::Vec3 win(319, 479 - 479, 0.5);

        // Check results
        const M3d::Vec4 actual = Glycerin::Projection::unProject(win, imvp, viewport);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, actual.x, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, actual.y, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, actual.z, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, actual.w, LOOSE_TOLERANCE);
    }

    /**
     * Ensures `Projection::unProject` works correctly with identity matrix and center of viewport.
     */
    void testUnProjectWithIdentityAndCenter() {

        // Make parameters
        const Glycerin::Viewport viewport(0, 0, 640, 480);
        const M3d::Mat4 imvp(1.0);
        const M3d::Vec3 win(319, 479 - 239, 0.5);

        // Check results
        const M3d::Vec4 actual = Glycerin::Projection::unProject(win, imvp, viewport);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, actual.x, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, actual.y, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, actual.z, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, actual.w, LOOSE_TOLERANCE);
    }

    /**
     * Ensures `Projection::unProject` works correctly with identity matrix and front of viewport.
     */
    void testUnProjectWithIdentityAndFront() {

        // Make parameters
        const Glycerin::Viewport viewport(0, 0, 640, 480);
        const M3d::Mat4 imvp(1.0);
        const M3d::Vec3 win(319, 479 - 239, 1.0);

        // Check results
        const M3d::Vec4 actual = Glycerin::Projection::unProject(win, imvp, viewport);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, actual.x, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, actual.y, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, actual.z, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, actual.w, LOOSE_TOLERANCE);
    }

    /**
     * Ensures `Projection::unProject` works correctly with identity matrix and left side of viewport.
     */
    void testUnProjectWithIdentityAndLeft() {

        // Make parameters
        const Glycerin::Viewport viewport(0, 0, 640, 480);
        const M3d::Mat4 imvp(1.0);
        const M3d::Vec3 win(0, 479 - 239, 0.5);

        // Check results
        const M3d::Vec4 actual = Glycerin::Projection::unProject(win, imvp, viewport);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, actual.x, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, actual.y, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, actual.z, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, actual.w, LOOSE_TOLERANCE);
    }

    /**
     * Ensures `Projection::unProject` works correctly with identity matrix and right side of viewport.
     */
    void testUnProjectWithIdentityAndRight() {

        // Make parameters
        const Glycerin::Viewport viewport(0, 0, 640, 480);
        const M3d::Mat4 imvp(1.0);
        const M3d::Vec3 win(639, 479 - 239, 0.5);

        // Check results
        const M3d::Vec4 actual = Glycerin::Projection::unProject(win, imvp, viewport);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, actual.x, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, actual.y, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, actual.z, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, actual.w, LOOSE_TOLERANCE);
    }

    /**
     * Ensures `Projection::unProject` works correctly with identity matrix and top of viewport.
     */
    void testUnProjectWithIdentityAndTop() {

        // Make parameters
        const Glycerin::Viewport viewport(0, 0, 640, 480);
        const M3d::Mat4 imvp(1.0);
        const M3d::Vec3 win(319, 479 - 0, 0.5);

        // Check results
        const M3d::Vec4 actual = Glycerin::Projection::unProject(win, imvp, viewport);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, actual.x, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, actual.y, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, actual.z, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, actual.w, LOOSE_TOLERANCE);
    }

    /**
     * Ensures `Projection::unProject` works correctly with orthographic matrix and back of viewport.
     */
    void testUnProjectWithOrthographicAndBack() {

        // Make parameters
        const Glycerin::Viewport viewport(0, 0, 640, 480);
        const M3d::Mat4 imvp = M3d::inverse(Glycerin::Projection::orthographic(640, 480));
        const M3d::Vec3 win(319, 479 - 239, 1.0);

        // Check results
        const M3d::Vec4 actual = Glycerin::Projection::unProject(win, imvp, viewport);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(319.0, actual.x, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(240.0, actual.y, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, actual.z, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, actual.w, LOOSE_TOLERANCE);
    }

    /**
     * Ensures `Projection::unProject` works correctly with orthographic matrix and bottom of viewport.
     */
    void testUnProjectWithOrthographicAndBottom() {

        // Make parameters
        const Glycerin::Viewport viewport(0, 0, 640, 480);
        const M3d::Mat4 imvp = M3d::inverse(Glycerin::Projection::orthographic(640, 480));
        const M3d::Vec3 win(319, 479 - 479, 0.5);

        // Check results
        const M3d::Vec4 actual = Glycerin::Projection::unProject(win, imvp, viewport);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(319.0, actual.x, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, actual.y, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, actual.z, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, actual.w, LOOSE_TOLERANCE);
    }

    /**
     * Ensures `Projection::unProject` works correctly with orthographic matrix and center of viewport.
     */
    void testUnProjectWithOrthographicAndCenter() {

        // Make parameters
        const Glycerin::Viewport viewport(0, 0, 640, 480);
        const M3d::Mat4 imvp = M3d::inverse(Glycerin::Projection::orthographic(640, 480));
        const M3d::Vec3 win(319, 479 - 239, 0.5);

        // Check results
        const M3d::Vec4 actual = Glycerin::Projection::unProject(win, imvp, viewport);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(319.0, actual.x, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(240.0, actual.y, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, actual.z, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, actual.w, LOOSE_TOLERANCE);
    }

    /**
     * Ensures `Projection::unProject` works correctly with orthographic matrix and front of viewport.
     */
    void testUnProjectWithOrthographicAndFront() {

        // Make parameters
        const Glycerin::Viewport viewport(0, 0, 640, 480);
        const M3d::Mat4 imvp = M3d::inverse(Glycerin::Projection::orthographic(640, 480));
        const M3d::Vec3 win(319, 479 - 239, 0.0);

        // Check results
        const M3d::Vec4 actual = Glycerin::Projection::unProject(win, imvp, viewport);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(319.0, actual.x, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(240.0, actual.y, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, actual.z, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, actual.w, LOOSE_TOLERANCE);
    }

    /**
     * Ensures `Projection::unProject` works correctly with orthographic matrix and left side of viewport.
     */
    void testUnProjectWithOrthographicAndLeft() {

        // Make parameters
        const Glycerin::Viewport viewport(0, 0, 640, 480);
        const M3d::Mat4 imvp = M3d::inverse(Glycerin::Projection::orthographic(640, 480));
        const M3d::Vec3 win(0, 479 - 239, 0.5);

        // Check results
        const M3d::Vec4 actual = Glycerin::Projection::unProject(win, imvp, viewport);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, actual.x, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(240.0, actual.y, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, actual.z, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, actual.w, LOOSE_TOLERANCE);
    }

    /**
     * Ensures `Projection::unProject` works correctly with orthographic matrix and right side of viewport.
     */
    void testUnProjectWithOrthographicAndRight() {

        // Make parameters
        const Glycerin::Viewport viewport(0, 0, 640, 480);
        const M3d::Mat4 imvp = M3d::inverse(Glycerin::Projection::orthographic(640, 480));
        const M3d::Vec3 win(639, 479 - 239, 0.5);

        // Check results
        const M3d::Vec4 actual = Glycerin::Projection::unProject(win, imvp, viewport);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(639.0, actual.x, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(240.0, actual.y, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, actual.z, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, actual.w, LOOSE_TOLERANCE);
    }

    /**
     * Ensures `Projection::unProject` works correctly with orthographic matrix and top of viewport.
     */
    void testUnProjectWithOrthographicAndTop() {

        // Make parameters
        const Glycerin::Viewport viewport(0, 0, 640, 480);
        const M3d::Mat4 imvp = M3d::inverse(Glycerin::Projection::orthographic(640, 480));
        const M3d::Vec3 win(319, 479 - 0, 0.5);

        // Check results
        const M3d::Vec4 actual = Glycerin::Projection::unProject(win, imvp, viewport);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(319.0, actual.x, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(479.0, actual.y, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, actual.z, LOOSE_TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, actual.w, LOOSE_TOLERANCE);
    }

    CPPUNIT_TEST_SUITE(ProjectionTest);
    CPPUNIT_TEST(testOrthographicWithSixFortyByFourEighty);
    CPPUNIT_TEST(testPerspectiveWithThirtyDegrees);
    CPPUNIT_TEST(testUnProjectWithIdentityAndBack);
    CPPUNIT_TEST(testUnProjectWithIdentityAndBottom);
    CPPUNIT_TEST(testUnProjectWithIdentityAndCenter);
    CPPUNIT_TEST(testUnProjectWithIdentityAndFront);
    CPPUNIT_TEST(testUnProjectWithIdentityAndLeft);
    CPPUNIT_TEST(testUnProjectWithIdentityAndRight);
    CPPUNIT_TEST(testUnProjectWithIdentityAndTop);
    CPPUNIT_TEST(testUnProjectWithOrthographicAndBack);
    CPPUNIT_TEST(testUnProjectWithOrthographicAndBottom);
    CPPUNIT_TEST(testUnProjectWithOrthographicAndCenter);
    CPPUNIT_TEST(testUnProjectWithOrthographicAndFront);
    CPPUNIT_TEST(testUnProjectWithOrthographicAndLeft);
    CPPUNIT_TEST(testUnProjectWithOrthographicAndRight);
    CPPUNIT_TEST(testUnProjectWithOrthographicAndTop);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(ProjectionTest::suite());
    runner.run();
    return 0;
}
