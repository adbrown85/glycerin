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
#include <m3d/Mat4.h>
#include <stdexcept>
#include "glycerin/MatrixStack.hxx"


/**
 * Unit test for `MatrixStack`.
 */
class MatrixStackTest : public CppUnit::TestFixture {
public:

    // Threshold for floating-point comparisons
    static const double TOLERANCE = 1e-9;

    /**
     * Ensures `MatrixStack::MatrixStack` loads the identity matrix.
     */
    void testMatrixStack() {

        // Make a stack
        const Glycerin::MatrixStack stack;

        // Get top of stack
        const M3d::Mat4 top = stack.top();

        // Check elements
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (i == j) {
                    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, top[j][i], TOLERANCE);
                } else {
                    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, top[j][i], TOLERANCE);
                }
            }
        }
    }

    /**
     * Ensures `MatrixStack::pop` throws an exception if tries to pop off the bottom of the stack.
     */
    void testPopWithBottom() {

        // Make a stack
        Glycerin::MatrixStack stack;

        // Try to pop off only element
        CPPUNIT_ASSERT_THROW(stack.pop(), std::runtime_error);
    }

    /**
     * Ensures `MatrixStack::push` works correctly.
     */
    void testPush() {

        // Make a stack
        Glycerin::MatrixStack stack;

        // Change the top and then push
        stack.top() = M3d::Mat4(2);
        stack.push();

        // Check elements
        const M3d::Mat4 top = stack.top();
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (i == j) {
                    CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, top[j][i], TOLERANCE);
                } else {
                    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, top[j][i], TOLERANCE);
                }
            }
        }
    }

    CPPUNIT_TEST_SUITE(MatrixStackTest);
    CPPUNIT_TEST(testMatrixStack);
    CPPUNIT_TEST(testPopWithBottom);
    CPPUNIT_TEST(testPush);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(MatrixStackTest::suite());
    runner.run();
    return 0;
}
