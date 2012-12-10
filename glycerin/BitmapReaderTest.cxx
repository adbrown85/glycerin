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
#include "glycerin/common.h"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <stdexcept>
#include "glycerin/BitmapReader.hxx"
using namespace std;
namespace Glycerin {


/**
 * Unit test for BitmapReader.
 */
class BitmapReaderTest : public CppUnit::TestFixture {
public:

    /**
     * Ensures read works correctly.
     */
    void testRead() {

        // Read in the file
        BitmapReader reader;
        const Bitmap bitmap = reader.read("glycerin/rgbw.bmp");

        // Check width and height
        CPPUNIT_ASSERT_EQUAL((GLint) 2, bitmap.getWidth());
        CPPUNIT_ASSERT_EQUAL((GLint) 2, bitmap.getHeight());

        // Check format and size
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_BGR, bitmap.getFormat());
        CPPUNIT_ASSERT_EQUAL((GLsizei) 16, bitmap.getSize());

        // Get pixel data
        GLubyte arr[16];
        bitmap.getPixels(arr, 16);

        // Check bottom row (red and white)
        CPPUNIT_ASSERT_EQUAL((GLubyte) 0, arr[0]); // B
        CPPUNIT_ASSERT_EQUAL((GLubyte) 0, arr[1]); // G
        CPPUNIT_ASSERT_EQUAL((GLubyte) 255, arr[2]); // R
        CPPUNIT_ASSERT_EQUAL((GLubyte) 255, arr[3]); // B
        CPPUNIT_ASSERT_EQUAL((GLubyte) 255, arr[4]); // G
        CPPUNIT_ASSERT_EQUAL((GLubyte) 255, arr[5]); // R

        // Check top row (blue and green)
        CPPUNIT_ASSERT_EQUAL((GLubyte) 255, arr[8]); // B
        CPPUNIT_ASSERT_EQUAL((GLubyte) 0, arr[9]); // G
        CPPUNIT_ASSERT_EQUAL((GLubyte) 0, arr[10]); // R
        CPPUNIT_ASSERT_EQUAL((GLubyte) 0, arr[11]); // B
        CPPUNIT_ASSERT_EQUAL((GLubyte) 255, arr[12]); // G
        CPPUNIT_ASSERT_EQUAL((GLubyte) 0, arr[13]); // R
    }

    CPPUNIT_TEST_SUITE(BitmapReaderTest);
    CPPUNIT_TEST(testRead);
    CPPUNIT_TEST_SUITE_END();
};

} /* namespace Glycerin */

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(Glycerin::BitmapReaderTest::suite());
    runner.run();
    return 0;
}
