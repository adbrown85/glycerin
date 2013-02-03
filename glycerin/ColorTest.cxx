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
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <stdexcept>
#include "glycerin/Color.hxx"


/**
 * Unit test for `Color`.
 */
class ColorTest : public CppUnit::TestFixture {
public:

    // Threshold for floating-point comparisons
    static const GLfloat TOLERANCE = 1e-6;

    /**
     * Ensures `Color::Color()` sets correct values.
     */
    void testColor() {
        const Glycerin::Color color;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, color.r, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, color.g, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, color.b, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, color.a, TOLERANCE);
    }

    /**
     * Ensures `Color::Color(GLfloat, GLfloat, GLfloat)` sets values correctly.
     */
    void testColorFloatFloatFloat() {
        const Glycerin::Color color(0.1f, 0.2f, 0.3f);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.1f, color.r, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2f, color.g, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3f, color.b, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, color.a, TOLERANCE);
    }

    /**
     * Ensures `Color::Color(GLfloat, GLfloat, GLfloat, GLfloat)` sets values correctly.
     */
    void testColorFloatFloatFloatFloat() {
        const Glycerin::Color color(0.1f, 0.2f, 0.3f, 0.4f);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.1f, color.r, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2f, color.g, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3f, color.b, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.4f, color.a, TOLERANCE);
    }

    /**
     * Ensures `Color::operator==` returns `true` for equal instances.
     */
    void testEqualityOperatorWithEqualInstances() {
        const Glycerin::Color c1(0.0f, 0.0f, 0.0f, 0.0f);
        const Glycerin::Color c2(0.0f, 0.0f, 0.0f, 0.0f);
        CPPUNIT_ASSERT(c1 == c2);
    }

    /**
     * Ensures `Color::operator==` returns `false` for instances with unequal red components.
     */
    void testEqualityOperatorWithUnequalRedComponents() {
        const Glycerin::Color c1(0.0f, 0.0f, 0.0f, 0.0f);
        const Glycerin::Color c2(1.0f, 0.0f, 0.0f, 0.0f);
        CPPUNIT_ASSERT(!(c1 == c2));
    }

    /**
     * Ensures `Color::operator==` returns `false` for instances with unequal green components.
     */
    void testEqualityOperatorWithUnequalGreenComponents() {
        const Glycerin::Color c1(0.0f, 0.0f, 0.0f, 0.0f);
        const Glycerin::Color c2(0.0f, 1.0f, 0.0f, 0.0f);
        CPPUNIT_ASSERT(!(c1 == c2));
    }

    /**
     * Ensures `Color::operator==` returns `false` for instances with unequal blue components.
     */
    void testEqualityOperatorWithUnequalBlueComponents() {
        const Glycerin::Color c1(0.0f, 0.0f, 0.0f, 0.0f);
        const Glycerin::Color c2(0.0f, 0.0f, 1.0f, 0.0f);
        CPPUNIT_ASSERT(!(c1 == c2));
    }

    /**
     * Ensures `Color::operator==` returns `false` for instances with unequal alpha components.
     */
    void testEqualityOperatorWithUnequalAlphaComponents() {
        const Glycerin::Color c1(0.0f, 0.0f, 0.0f, 0.0f);
        const Glycerin::Color c2(0.0f, 0.0f, 0.0f, 1.0f);
        CPPUNIT_ASSERT(!(c1 == c2));
    }

    /**
     * Ensures `Color::fromArray` works correctly.
     */
    void testFromArray() {
        const GLfloat arr[] = { 0.1f, 0.2f, 0.3f, 0.4f };
        const Glycerin::Color color = Glycerin::Color::fromArray(arr);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.1f, color.r, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2f, color.g, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3f, color.b, TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.4f, color.a, TOLERANCE);
    }

    /**
     * Ensures `Color::operator!=` returns `false` for equal instances.
     */
    void testInequalityOperatorWithEqualInstances() {
        const Glycerin::Color c1(0.0f, 0.0f, 0.0f, 0.0f);
        const Glycerin::Color c2(0.0f, 0.0f, 0.0f, 0.0f);
        CPPUNIT_ASSERT(!(c1 != c2));
    }

    /**
     * Ensures `Color::operator!=` returns `true` for instances with unequal red components.
     */
    void testInequalityOperatorWithUnequalRedComponents() {
        const Glycerin::Color c1(0.0f, 0.0f, 0.0f, 0.0f);
        const Glycerin::Color c2(1.0f, 0.0f, 0.0f, 0.0f);
        CPPUNIT_ASSERT(c1 != c2);
    }

    /**
     * Ensures `Color::operator!=` returns `true` for instances with unequal green components.
     */
    void testInequalityOperatorWithUnequalGreenComponents() {
        const Glycerin::Color c1(0.0f, 0.0f, 0.0f, 0.0f);
        const Glycerin::Color c2(0.0f, 1.0f, 0.0f, 0.0f);
        CPPUNIT_ASSERT(c1 != c2);
    }

    /**
     * Ensures `Color::operator!=` returns `true` for instances with unequal blue components.
     */
    void testInequalityOperatorWithUnequalBlueComponents() {
        const Glycerin::Color c1(0.0f, 0.0f, 0.0f, 0.0f);
        const Glycerin::Color c2(0.0f, 0.0f, 1.0f, 0.0f);
        CPPUNIT_ASSERT(c1 != c2);
    }

    /**
     * Ensures `Color::operator!=` returns `true` for instances with unequal alpha components.
     */
    void testInequalityOperatorWithUnequalAlphaComponents() {
        const Glycerin::Color c1(0.0f, 0.0f, 0.0f, 0.0f);
        const Glycerin::Color c2(0.0f, 0.0f, 0.0f, 1.0f);
        CPPUNIT_ASSERT(c1 != c2);
    }

    /**
     * Ensures `operator<<(ostream&, const Color&)` works correctly.
     */
    void testInsertionOperator() {

        // Make a color
        const Glycerin::Color color(0.1f, 0.2f, 0.3f, 0.4f);

        // Insert into stream
        std::stringstream stream;
        stream << color;

        // Check results
        const std::string expected = "[0.1, 0.2, 0.3, 0.4]";
        const std::string actual = stream.str();
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }

    /**
     * Ensures `Color::operator[] const` throws if passed four.
     */
    void testSubscriptOperatorConstWithFour() {
        const Glycerin::Color color;
        CPPUNIT_ASSERT_THROW(color[4], std::invalid_argument);
    }

    /**
     * Ensures `Color::operator[] const` throws if passed negative one.
     */
    void testSubscriptOperatorConstWithNegativeOne() {
        const Glycerin::Color color;
        CPPUNIT_ASSERT_THROW(color[-1], std::invalid_argument);
    }

    /**
     * Ensures `Color::operator[] const` works with one.
     */
    void testSubscriptOperatorConstWithOne() {
        const Glycerin::Color color(0.1f, 0.2f, 0.3f, 0.4f);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2f, color[1], TOLERANCE);
    }

    /**
     * Ensures `Color::operator[] const` works with three.
     */
    void testSubscriptOperatorConstWithThree() {
        const Glycerin::Color color(0.1f, 0.2f, 0.3f, 0.4f);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.4f, color[3], TOLERANCE);
    }

    /**
     * Ensures `Color::operator[] const` works with two.
     */
    void testSubscriptOperatorConstWithTwo() {
        const Glycerin::Color color(0.1f, 0.2f, 0.3f, 0.4f);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3f, color[2], TOLERANCE);
    }

    /**
     * Ensures `Color::operator[] const` works with zero.
     */
    void testSubscriptOperatorConstWithZero() {
        const Glycerin::Color color(0.1f, 0.2f, 0.3f, 0.4f);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.1f, color[0], TOLERANCE);
    }

    /**
     * Ensures `Color::operator[]` throws if passed four.
     */
    void testSubscriptOperatorWithFour() {
        Glycerin::Color color;
        CPPUNIT_ASSERT_THROW(color[4], std::invalid_argument);
    }

    /**
     * Ensures `Color::operator[]` throws if passed negative one.
     */
    void testSubscriptOperatorWithNegativeOne() {
        Glycerin::Color color;
        CPPUNIT_ASSERT_THROW(color[-1], std::invalid_argument);
    }

    /**
     * Ensures `Color::operator[]` works with one.
     */
    void testSubscriptOperatorWithOne() {
        Glycerin::Color color(0.1f, 0.2f, 0.3f, 0.4f);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2f, color[1], TOLERANCE);
        color[1] = 1.0f;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, color[1], TOLERANCE);
    }

    /**
     * Ensures `Color::operator[]` works with three.
     */
    void testSubscriptOperatorWithThree() {
        Glycerin::Color color(0.1f, 0.2f, 0.3f, 0.4f);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.4f, color[3], TOLERANCE);
        color[3] = 1.0f;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, color[3], TOLERANCE);
    }

    /**
     * Ensures `Color::operator[]` works with two.
     */
    void testSubscriptOperatorWithTwo() {
        Glycerin::Color color(0.1f, 0.2f, 0.3f, 0.4f);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3f, color[2], TOLERANCE);
        color[2] = 1.0f;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, color[2], TOLERANCE);
    }

    /**
     * Ensures `Color::operator[]` works with zero.
     */
    void testSubscriptOperatorWithZero() {
        Glycerin::Color color(0.1f, 0.2f, 0.3f, 0.4f);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.1f, color[0], TOLERANCE);
        color[0] = 1.0f;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, color[0], TOLERANCE);
    }

    /**
     * Ensures `Color::toArray` works correctly.
     */
    void testToArray() {
        const Glycerin::Color color(0.1f, 0.2f, 0.3f, 0.4f);
        GLfloat arr[4];
        color.toArray(arr);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.1f, arr[0], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2f, arr[1], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3f, arr[2], TOLERANCE);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.4f, arr[3], TOLERANCE);
    }

    CPPUNIT_TEST_SUITE(ColorTest);
    CPPUNIT_TEST(testColor);
    CPPUNIT_TEST(testColorFloatFloatFloat);
    CPPUNIT_TEST(testColorFloatFloatFloatFloat);
    CPPUNIT_TEST(testEqualityOperatorWithEqualInstances);
    CPPUNIT_TEST(testEqualityOperatorWithUnequalRedComponents);
    CPPUNIT_TEST(testEqualityOperatorWithUnequalGreenComponents);
    CPPUNIT_TEST(testEqualityOperatorWithUnequalBlueComponents);
    CPPUNIT_TEST(testEqualityOperatorWithUnequalAlphaComponents);
    CPPUNIT_TEST(testFromArray);
    CPPUNIT_TEST(testInequalityOperatorWithEqualInstances);
    CPPUNIT_TEST(testInequalityOperatorWithUnequalRedComponents);
    CPPUNIT_TEST(testInequalityOperatorWithUnequalGreenComponents);
    CPPUNIT_TEST(testInequalityOperatorWithUnequalBlueComponents);
    CPPUNIT_TEST(testInequalityOperatorWithUnequalAlphaComponents);
    CPPUNIT_TEST(testInsertionOperator);
    CPPUNIT_TEST(testSubscriptOperatorConstWithFour);
    CPPUNIT_TEST(testSubscriptOperatorConstWithNegativeOne);
    CPPUNIT_TEST(testSubscriptOperatorConstWithOne);
    CPPUNIT_TEST(testSubscriptOperatorConstWithThree);
    CPPUNIT_TEST(testSubscriptOperatorConstWithTwo);
    CPPUNIT_TEST(testSubscriptOperatorConstWithZero);
    CPPUNIT_TEST(testSubscriptOperatorWithFour);
    CPPUNIT_TEST(testSubscriptOperatorWithNegativeOne);
    CPPUNIT_TEST(testSubscriptOperatorWithOne);
    CPPUNIT_TEST(testSubscriptOperatorWithThree);
    CPPUNIT_TEST(testSubscriptOperatorWithTwo);
    CPPUNIT_TEST(testSubscriptOperatorWithZero);
    CPPUNIT_TEST(testToArray);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(ColorTest::suite());
    runner.run();
    return 0;
}
