#include "config.h"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include "glycerin/BufferLayout.hxx"
#include "glycerin/BufferLayoutBuilder.hxx"
using Glycerin::BufferLayout;
using Glycerin::BufferLayoutBuilder;


/**
 * Unit test for BufferLayout.
 */
class BufferLayoutTest : public CppUnit::TestFixture {
public:

    /**
     * Ensures 'sizeInBytes' works with one region.
     */
    void testSizeInBytesWithOneRegion() {
        const BufferLayout layout = BufferLayoutBuilder().count(7).region("r1").build();
        CPPUNIT_ASSERT_EQUAL(112, layout.sizeInBytes());
    }

    /**
     * Ensures 'sizeInBytes' works with two regions.
     */
    void testSizeInBytesWithTwoRegions() {
        const BufferLayout layout = BufferLayoutBuilder().count(7).region("r1").region("r2").build();
        CPPUNIT_ASSERT_EQUAL(224, layout.sizeInBytes());
    }

    CPPUNIT_TEST_SUITE(BufferLayoutTest);
    CPPUNIT_TEST(testSizeInBytesWithOneRegion);
    CPPUNIT_TEST(testSizeInBytesWithTwoRegions);
    CPPUNIT_TEST_SUITE_END();
};

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(BufferLayoutTest::suite());
    runner.run();
    return 0;
}
