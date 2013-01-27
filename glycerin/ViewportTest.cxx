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
#include <exception>
#include <iostream>
#include <stdexcept>
#include <cppunit/extensions/HelperMacros.h>
#include <GL/glfw.h>
#include "glycerin/Viewport.hxx"

/**
 * Unit test for `Viewport`.
 */
class ViewportTest {
public:

    /**
     * Ensures `Viewport::operator==` returns `false` for two instances with different heights.
     */
    void testEqualityOperatorWithDifferentHeight() {
        const Glycerin::Viewport v1(0, 0, 0, 1);
        const Glycerin::Viewport v2(0, 0, 0, 2);
        CPPUNIT_ASSERT(!(v1 == v2));
    }

    /**
     * Ensures `Viewport::operator==` returns `false` for two instances with different widths.
     */
    void testEqualityOperatorWithDifferentWidth() {
        const Glycerin::Viewport v1(0, 0, 1, 0);
        const Glycerin::Viewport v2(0, 0, 2, 0);
        CPPUNIT_ASSERT(!(v1 == v2));
    }

    /**
     * Ensures `Viewport::operator==` returns `false` for two instances with different X locations.
     */
    void testEqualityOperatorWithDifferentX() {
        const Glycerin::Viewport v1(1, 0, 0, 0);
        const Glycerin::Viewport v2(2, 0, 0, 0);
        CPPUNIT_ASSERT(!(v1 == v2));
    }

    /**
     * Ensures `Viewport::operator==` returns `false` for two instances with different Y locations.
     */
    void testEqualityOperatorWithDifferentY() {
        const Glycerin::Viewport v1(0, 1, 0, 0);
        const Glycerin::Viewport v2(0, 2, 0, 0);
        CPPUNIT_ASSERT(!(v1 == v2));
    }

    /**
     * Ensures `Viewport::operator==` returns `true` for two instances with the same values.
     */
    void testEqualityOperatorWithSameValues() {
        const Glycerin::Viewport v1(1, 2, 3, 4);
        const Glycerin::Viewport v2(1, 2, 3, 4);
        CPPUNIT_ASSERT(v1 == v2);
    }

    /**
     * Ensures `Viewport::getViewport` works correctly.
     */
    void testGetViewport() {

        // Set viewport
        glViewport(1, 2, 3, 4);

        // Get viewport
        const Glycerin::Viewport expected(1, 2, 3, 4);
        const Glycerin::Viewport actual = Glycerin::Viewport::getViewport();
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures `Viewport::height()` returns correct value.
     */
    void testHeight() {
        const Glycerin::Viewport viewport(1, 2, 3, 4);
        CPPUNIT_ASSERT_EQUAL(4, viewport.height());
    }

    /**
     * Ensures `Viewport::operator!=` returns `false` for two instances with different heights.
     */
    void testInequalityOperatorWithDifferentHeight() {
        const Glycerin::Viewport v1(0, 0, 0, 1);
        const Glycerin::Viewport v2(0, 0, 0, 2);
        CPPUNIT_ASSERT(v1 != v2);
    }

    /**
     * Ensures `Viewport::operator!=` returns `false` for two instances with different widths.
     */
    void testInequalityOperatorWithDifferentWidth() {
        const Glycerin::Viewport v1(0, 0, 1, 0);
        const Glycerin::Viewport v2(0, 0, 2, 0);
        CPPUNIT_ASSERT(v1 != v2);
    }

    /**
     * Ensures `Viewport::operator!=` returns `false` for two instances with different X locations.
     */
    void testInequalityOperatorWithDifferentX() {
        const Glycerin::Viewport v1(1, 0, 0, 0);
        const Glycerin::Viewport v2(2, 0, 0, 0);
        CPPUNIT_ASSERT(v1 != v2);
    }

    /**
     * Ensures `Viewport::operator!=` returns `false` for two instances with different Y locations.
     */
    void testInequalityOperatorWithDifferentY() {
        const Glycerin::Viewport v1(0, 1, 0, 0);
        const Glycerin::Viewport v2(0, 2, 0, 0);
        CPPUNIT_ASSERT(v1 != v2);
    }

    /**
     * Ensures `Viewport::operator!=` returns `true` for two instances with the same values.
     */
    void testInequalityOperatorWithSameValues() {
        const Glycerin::Viewport v1(1, 2, 3, 4);
        const Glycerin::Viewport v2(1, 2, 3, 4);
        CPPUNIT_ASSERT(!(v1 != v2));
    }

    /**
     * Ensures `operator<<(ostream&, const Viewport&)` works correctly.
     */
    void testInsertionOperator() {

        // Make viewport
        const Glycerin::Viewport viewport(1, 2, 3, 4);

        // Insert into stream
        std::stringstream stream;
        stream << viewport;

        // Check results
        const std::string expected = "[1, 2, 3, 4]";
        const std::string actual = stream.str();
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures constructor throws if passed a negative height.
     */
    void testViewportWithNegativeHeight() {
        CPPUNIT_ASSERT_THROW(Glycerin::Viewport(0, 0, 512, -1), std::invalid_argument);
    }

    /**
     * Ensures constructor throws if passed a negative width.
     */
    void testViewportWithNegativeWidth() {
        CPPUNIT_ASSERT_THROW(Glycerin::Viewport(0, 0, -1, 512), std::invalid_argument);
    }

    /**
     * Ensures constructor allows a negative X location.
     */
    void testViewportWithNegativeX() {
        Glycerin::Viewport(-1, 0, 512, 512);
    }

    /**
     * Ensures constructor allows a negative Y location.
     */
    void testViewportWithNegativeY() {
        Glycerin::Viewport(0, -1, 512, 512);
    }

    /**
     * Ensures `Viewport::width()` returns correct value.
     */
    void testWidth() {
        const Glycerin::Viewport viewport(1, 2, 3, 4);
        CPPUNIT_ASSERT_EQUAL(3, viewport.width());
    }

    /**
     * Ensures `Viewport::x()` returns correct value.
     */
    void testX() {
        const Glycerin::Viewport viewport(1, 2, 3, 4);
        CPPUNIT_ASSERT_EQUAL(1, viewport.x());
    }

    /**
     * Ensures `Viewport::y()` returns correct value.
     */
    void testY() {
        const Glycerin::Viewport viewport(1, 2, 3, 4);
        CPPUNIT_ASSERT_EQUAL(2, viewport.y());
    }
};

int main(int argc, char* argv[]) {

    // Initialize
    if (!glfwInit()) {
        throw std::runtime_error("Could not initialize GLFW!");
    }

    // Open window
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (!glfwOpenWindow(512, 512, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)) {
        throw std::runtime_error("Could not open window!");
    }

    try {
        ViewportTest test;
        test.testEqualityOperatorWithDifferentHeight();
        test.testEqualityOperatorWithDifferentWidth();
        test.testEqualityOperatorWithDifferentX();
        test.testEqualityOperatorWithDifferentY();
        test.testEqualityOperatorWithSameValues();
        test.testGetViewport();
        test.testHeight();
        test.testInequalityOperatorWithDifferentHeight();
        test.testInequalityOperatorWithDifferentWidth();
        test.testInequalityOperatorWithDifferentX();
        test.testInequalityOperatorWithDifferentY();
        test.testInequalityOperatorWithSameValues();
        test.testInsertionOperator();
        test.testViewportWithNegativeHeight();
        test.testViewportWithNegativeWidth();
        test.testViewportWithNegativeX();
        test.testViewportWithNegativeY();
        test.testWidth();
        test.testX();
        test.testY();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
