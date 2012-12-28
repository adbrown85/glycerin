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
#include "Glycerin/BufferLayout.hxx"
#include "Glycerin/BufferLayoutBuilder.hxx"
#include "Glycerin/BufferRegion.hxx"
using Glycerin::BufferLayout;
using Glycerin::BufferLayoutBuilder;
using Glycerin::BufferRegion;


/**
 * Unit test for BufferRegion.
 */
class BufferRegionTest : public CppUnit::TestFixture {
public:

    /**
     * Ensures 'sizeInBytes' works correctly with a `GL_FLOAT` type.
     */
    void testSizeInBytesWithFloatType() {
        const BufferLayout layout = BufferLayoutBuilder().count(7).type(GL_FLOAT).region("r1").build();
        const BufferRegion region = *(layout.find("r1"));
        CPPUNIT_ASSERT_EQUAL(112, region.sizeInBytes());
    }

    /**
     * Ensures 'sizeInBytes' works with four components.
     */
    void testSizeInBytesWithFourComponents() {
        const BufferLayout layout = BufferLayoutBuilder().count(7).components(4).region("r1").build();
        const BufferRegion region = *(layout.find("r1"));
        CPPUNIT_ASSERT_EQUAL(112, region.sizeInBytes());
    }

    /**
     * Ensures 'sizeInBytes' works correctly with a `GL_INT` type.
     */
    void testSizeInBytesWithIntType() {
        const BufferLayout layout = BufferLayoutBuilder().count(7).type(GL_INT).region("r1").build();
        const BufferRegion region = *(layout.find("r1"));
        CPPUNIT_ASSERT_EQUAL(112, region.sizeInBytes());
    }

    /**
     * Ensures 'sizeInBytes' works with one component.
     */
    void testSizeInBytesWithOneComponent() {
        const BufferLayout layout = BufferLayoutBuilder().count(7).components(1).region("r1").build();
        const BufferRegion region = *(layout.find("r1"));
        CPPUNIT_ASSERT_EQUAL(28, region.sizeInBytes());
    }

    /**
     * Ensures 'sizeInBytes' works with a count of one.
     */
    void testSizeInBytesWithOneCount() {
        const BufferLayout layout = BufferLayoutBuilder().count(1).region("r1").build();
        const BufferRegion region = *(layout.find("r1"));
        CPPUNIT_ASSERT_EQUAL(16, region.sizeInBytes());
    }

    /**
     * Ensures 'sizeInBytes' works with three components.
     */
    void testSizeInBytesWithThreeComponents() {
        const BufferLayout layout = BufferLayoutBuilder().count(7).components(3).region("r1").build();
        const BufferRegion region = *(layout.find("r1"));
        CPPUNIT_ASSERT_EQUAL(84, region.sizeInBytes());
    }

    /**
     * Ensures 'sizeInBytes' works with two components.
     */
    void testSizeInBytesWithTwoComponents() {
        const BufferLayout layout = BufferLayoutBuilder().count(7).components(2).region("r1").build();
        const BufferRegion region = *(layout.find("r1"));
        CPPUNIT_ASSERT_EQUAL(56, region.sizeInBytes());
    }

    /**
     * Ensures 'sizeInBytes' works with a count of two.
     */
    void testSizeInBytesWithTwoCount() {
        const BufferLayout layout = BufferLayoutBuilder().count(2).region("r1").build();
        const BufferRegion region = *(layout.find("r1"));
        CPPUNIT_ASSERT_EQUAL(32, region.sizeInBytes());
    }

    /**
     * Ensures 'sizeInBytes' works correctly with a `GL_UNSIGNED_INT` type.
     */
    void testSizeInBytesWithUnsignedIntType() {
        const BufferLayout layout = BufferLayoutBuilder().count(7).type(GL_UNSIGNED_INT).region("r1").build();
        const BufferRegion region = *(layout.find("r1"));
        CPPUNIT_ASSERT_EQUAL(112, region.sizeInBytes());
    }

    CPPUNIT_TEST_SUITE(BufferRegionTest);
    CPPUNIT_TEST(testSizeInBytesWithFloatType);
    CPPUNIT_TEST(testSizeInBytesWithFourComponents);
    CPPUNIT_TEST(testSizeInBytesWithIntType);
    CPPUNIT_TEST(testSizeInBytesWithOneComponent);
    CPPUNIT_TEST(testSizeInBytesWithOneCount);
    CPPUNIT_TEST(testSizeInBytesWithThreeComponents);
    CPPUNIT_TEST(testSizeInBytesWithTwoComponents);
    CPPUNIT_TEST(testSizeInBytesWithTwoCount);
    CPPUNIT_TEST(testSizeInBytesWithUnsignedIntType);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(BufferRegionTest::suite());
    runner.run();
    return 0;
}
