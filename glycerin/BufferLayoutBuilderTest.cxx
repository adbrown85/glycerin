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
#include <stdexcept>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include "glycerin/BufferLayout.hxx"
#include "glycerin/BufferLayoutBuilder.hxx"
using namespace std;
namespace Glycerin {


/**
 * Unit test for BufferLayoutBuilder.
 */
class BufferLayoutBuilderTest : public CppUnit::TestFixture {
public:

    /**
     * Ensures offsets returned by an interleaved layout are correct.
     */
    void testBuildOffsetWithInterleaved() {

        // Create a layout
        BufferLayoutBuilder builder;
        builder.interleaved(true).count(10);

        // Add two regions
        builder.type(GL_FLOAT).components(3).region("MCVertex");
        builder.type(GL_FLOAT).components(2).region("TexCoord0");

        // Build the layout
        const BufferLayout layout = builder.build();

        // Check offset of first region
        GLsizei expect = 0;
        GLsizei result = layout.find("MCVertex")->offset();
        CPPUNIT_ASSERT_EQUAL(expect, result);

        // Check offset of second region
        expect = 4 * 3;
        result = layout.find("TexCoord0")->offset();
        CPPUNIT_ASSERT_EQUAL(expect, result);
    }

    /**
     * Ensures offsets returned by a non-interleaved layout are correct.
     */
    void testBuildOffsetWithNonInterleaved() {

        // Create a layout
        BufferLayoutBuilder builder;
        builder.interleaved(false).count(10);

        // Add two regions
        builder.type(GL_FLOAT).components(3).region("MCVertex");
        builder.type(GL_FLOAT).components(2).region("TexCoord0");

        // Build the layout
        const BufferLayout layout = builder.build();

        // Check offset of first region
        GLsizei expect = 0;
        GLsizei result = layout.find("MCVertex")->offset();
        CPPUNIT_ASSERT_EQUAL(expect, result);

        // Check offset of second region
        expect = sizeof(GLfloat) * 3 * 10;
        result = layout.find("TexCoord0")->offset();
        CPPUNIT_ASSERT_EQUAL(expect, result);
    }

    /**
     * Ensures strides returned by an interleaved layout are correct.
     */
    void testBuildStrideWithInterleaved() {

        // Create a layout
        BufferLayoutBuilder builder;
        builder.interleaved(true).count(10);

        // Add two regions
        builder.type(GL_FLOAT).components(3).region("MCVertex");
        builder.type(GL_FLOAT).components(2).region("TexCoord0");

        // Build the layout
        const BufferLayout layout = builder.build();

        // Check stride of first region
        GLsizei expect = (sizeof(GLfloat) * 3) + (sizeof(GLfloat) * 2);
        GLsizei result = layout.find("MCVertex")->stride();
        CPPUNIT_ASSERT_EQUAL(expect, result);

        // Check stride of second region
        result = layout.find("TexCoord0")->stride();
        CPPUNIT_ASSERT_EQUAL(expect, result);
    }

    /**
     * Ensures strides returned by a non-interleaved layout are correct.
     */
    void testBuildStrideWithNonInterleaved() {

        // Create a layout
        BufferLayoutBuilder builder;
        builder.interleaved(false).count(10);

        // Add two regions
        builder.type(GL_FLOAT).components(3).region("MCVertex");
        builder.type(GL_FLOAT).components(2).region("TexCoord");

        // Build the layout
        const BufferLayout layout = builder.build();

        // Check stride of first region
        GLsizei expect = sizeof(GLfloat) * 3;
        GLsizei result = layout.find("MCVertex")->stride();
        CPPUNIT_ASSERT_EQUAL(expect, result);

        // Check stride of second region
        expect = sizeof(GLfloat) * 2;
        result = layout.find("TexCoord")->stride();
        CPPUNIT_ASSERT_EQUAL(expect, result);
    }

    /**
     * Ensures components returned by the layout are correct.
     */
    void testComponents() {

        // Create builder
        BufferLayoutBuilder builder;
        builder.interleaved(false).count(10);

        // Add first region
        builder.components(3).region("MCVertex");

        // Add second region
        builder.components(2).region("TexCoord0");

        // Make layout
        const BufferLayout layout = builder.build();

        // Check components of first region
        GLsizei expect = 3;
        GLsizei result = layout.find("MCVertex")->components();
        CPPUNIT_ASSERT_EQUAL(expect, result);

        // Check components of second region
        expect = 2;
        result = layout.find("TexCoord0")->components();
        CPPUNIT_ASSERT_EQUAL(expect, result);
    }

    /**
     * Ensure setting builder's components to less than one throws an exception.
     */
    void testComponentsWithTooFew() {
        BufferLayoutBuilder builder;
        CPPUNIT_ASSERT_THROW(builder.components(0), invalid_argument);
    }

    /**
     * Ensures setting builder's components to more than four throws an exception.
     */
    void testComponentsWithTooMany() {
        BufferLayoutBuilder builder;
        CPPUNIT_ASSERT_THROW(builder.components(5), invalid_argument);
    }

    /**
     * Ensures setting different counts for an interleaved buffer throws an exception.
     */
    void testCountWithInterleavedAndDifferentCounts() {

        // Make an interleaved builder
        BufferLayoutBuilder builder;
        builder.interleaved(true);

        // Set the count and add a region
        builder.count(3).region("MCVertex");

        // Try to set the count again
        CPPUNIT_ASSERT_THROW(builder.count(6), logic_error);
    }

    /**
     * Ensures setting the builder's count to zero throws an exception.
     */
    void testCountWithZero() {
        BufferLayoutBuilder builder;
        CPPUNIT_ASSERT_THROW(builder.count(0), logic_error);
    }

    /**
     * Ensures interleaving regions with different counts throws an exception.
     */
    void testInterleavedWithDifferentCounts() {

        // Make a builder
        BufferLayoutBuilder builder;
        builder.interleaved(false);

        // Add two regions with different counts
        builder.count(12).region("MCVertex");
        builder.count(15).region("TexCoord0");

        // Now try to make it interleaved
        CPPUNIT_ASSERT_THROW(builder.interleaved(true), logic_error);
    }

    /**
     * Ensures interleaved returns true for an interleaved layout.
     */
    void testInterleavedWithInterleaved() {

        // Create a builder
        BufferLayoutBuilder builder;
        builder.interleaved(true);

        // Add first region
        builder.count(1).region("MCVertex");

        // Check if interleaved
        const BufferLayout layout = builder.build();
        CPPUNIT_ASSERT_EQUAL(true, layout.interleaved());
    }

    /**
     * Ensures interleaved return false for a non-interleaved layout.
     */
    void testInterleavedWithNonInterleaved() {

        // Create a builder
        BufferLayoutBuilder builder;
        builder.interleaved(false);

        // Add first region
        builder.count(1).region("MCVertex");

        // Check if interleaved
        const BufferLayout layout = builder.build();
        CPPUNIT_ASSERT_EQUAL(false, layout.interleaved());
    }

    /**
     * Ensures interleaving regions with same counts does not throw an exception.
     */
    void testInterleavedWithSameCounts() {

        // Create a layout
        BufferLayoutBuilder builder;
        builder.interleaved(true);

        // Add first region
        builder.count(10).region("MCVertex");

        // Add second region
        builder.count(10).region("TexCoord0");
    }

    /**
     * Ensures normalized values returned by the layout are correct.
     */
    void testNormalized() {

        // Create a layout
        BufferLayoutBuilder builder;
        builder.interleaved(false).count(10);

        // Add two regions
        builder.components(3).normalized(false).region("MCVertex");
        builder.components(2).normalized(true).region("TexCoord0");

        // Build the layout
        const BufferLayout layout = builder.build();

        // Check normalized flags
        CPPUNIT_ASSERT_EQUAL(false, layout.find("MCVertex")->normalized());
        CPPUNIT_ASSERT_EQUAL(true, layout.find("TexCoord0")->normalized());
    }

    /**
     * Ensures names returned by the layout are correct.
     */
    void testRegion() {

        // Create a layout
        BufferLayoutBuilder builder;
        builder.interleaved(false).count(10);

        // Add two regions
        builder.components(3).region("MCVertex");
        builder.components(2).region("TexCoord0");

        // Builder layout
        const BufferLayout layout = builder.build();

        // Check names
        BufferLayout::const_iterator r = layout.begin();
        CPPUNIT_ASSERT_EQUAL(string("MCVertex"), (r++)->name());
        CPPUNIT_ASSERT_EQUAL(string("TexCoord0"), (r++)->name());
        CPPUNIT_ASSERT(r == layout.end());
    }

    /**
     * Ensures adding a region before setting count throws an exception.
     */
    void testRegionBeforeCount() {
        BufferLayoutBuilder builder;
        CPPUNIT_ASSERT_THROW(builder.region("MCVertex"), logic_error);
    }

    /**
     * Ensures attempting to add a region with an empty name throws an exception.
     */
    void testRegionWithEmptyName() {

        // Create a layout
        BufferLayoutBuilder builder;
        builder.interleaved(false);

        // Try to add a region with an empty name
        builder.count(10);
        CPPUNIT_ASSERT_THROW(builder.region(""), invalid_argument);
    }

    /**
     * Ensures adding a region with the same name as another throws an exception.
     */
    void testRegionWithSameName() {

        // Create a layout
        BufferLayoutBuilder builder;
        builder.interleaved(false);

        // Add first region
        builder.count(10).region("MCVertex");

        // Try to add another region with the same name
        builder.count(20);
        CPPUNIT_ASSERT_THROW(builder.region("MCVertex"), invalid_argument);
    }

    /**
     * Ensures types returned by the layout are correct.
     */
    void testType() {

        // Create a layout
        BufferLayoutBuilder builder;
        builder.interleaved(false).count(10);

        // Add two regions
        builder.type(GL_FLOAT).components(3).region("MCVertex");
        builder.type(GL_INT).components(2).region("TexCoord0");

        // Build the layout
        const BufferLayout layout = builder.build();

        // Check result for first region
        GLenum expect = GL_FLOAT;
        GLenum result = layout.find("MCVertex")->type();
        CPPUNIT_ASSERT_EQUAL(expect, result);

        // Check result for second region
        expect = GL_INT;
        result = layout.find("TexCoord0")->type();
        CPPUNIT_ASSERT_EQUAL(expect, result);
    }

    /**
     * Ensures giving the builder an invalid type throws an exception.
     */
    void testTypeWithInvalidEnumeration() {
        BufferLayoutBuilder builder;
        CPPUNIT_ASSERT_THROW(builder.type(GL_VERSION), invalid_argument);
    }

    CPPUNIT_TEST_SUITE(BufferLayoutBuilderTest);
    CPPUNIT_TEST(testBuildOffsetWithInterleaved);
    CPPUNIT_TEST(testBuildOffsetWithNonInterleaved);
    CPPUNIT_TEST(testBuildStrideWithInterleaved);
    CPPUNIT_TEST(testBuildStrideWithNonInterleaved);
    CPPUNIT_TEST(testComponents);
    CPPUNIT_TEST(testComponentsWithTooFew);
    CPPUNIT_TEST(testComponentsWithTooMany);
    CPPUNIT_TEST(testCountWithInterleavedAndDifferentCounts);
    CPPUNIT_TEST(testCountWithZero);
    CPPUNIT_TEST(testInterleavedWithDifferentCounts);
    CPPUNIT_TEST(testInterleavedWithInterleaved);
    CPPUNIT_TEST(testInterleavedWithNonInterleaved);
    CPPUNIT_TEST(testInterleavedWithSameCounts);
    CPPUNIT_TEST(testNormalized);
    CPPUNIT_TEST(testRegion);
    CPPUNIT_TEST(testRegionBeforeCount);
    CPPUNIT_TEST(testRegionWithEmptyName);
    CPPUNIT_TEST(testRegionWithSameName);
    CPPUNIT_TEST(testType);
    CPPUNIT_TEST(testTypeWithInvalidEnumeration);
    CPPUNIT_TEST_SUITE_END();
};

} /* namespace Glycerin */

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(Glycerin::BufferLayoutBuilderTest::suite());
    runner.run();
    return 0;
}
