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
#include <cppunit/extensions/HelperMacros.h>
#include "glycerin/Volume.hxx"
#include "glycerin/VolumeReader.hxx"


/**
 * Unit test for `VolumeReader`.
 */
class VolumeReaderTest {
public:

    /**
     * Ensures `VolumeReader::read` works correctly.
     */
    void testRead() {

        // Read in a volume
        Glycerin::VolumeReader reader;
        const Glycerin::Volume volume = reader.read("glycerin/bunny.vlb");

        // Check width, height, and depth
        CPPUNIT_ASSERT_EQUAL(128, volume.getWidth());
        CPPUNIT_ASSERT_EQUAL(128, volume.getHeight());
        CPPUNIT_ASSERT_EQUAL(90, volume.getDepth());

        // Check type and endianness
        CPPUNIT_ASSERT_EQUAL((GLenum) GL_UNSIGNED_BYTE, volume.getType());
        CPPUNIT_ASSERT_EQUAL(std::string("little"), volume.getEndianness());

        // Check pitch
        CPPUNIT_ASSERT_EQUAL(1.0f, volume.getPitchX());
        CPPUNIT_ASSERT_EQUAL(1.0f, volume.getPitchY());
        CPPUNIT_ASSERT_EQUAL(1.0f, volume.getPitchZ());
    }
};

int main(int argc, char* argv[]) {
    try {
        VolumeReaderTest test;
        test.testRead();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }
    return 0;
}
