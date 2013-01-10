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
#include <cstring>
#include <iostream>
#include <stdexcept>
#include "glycerin/VolumeReader.hxx"
namespace Glycerin {

/**
 * Constructs a `VolumeReader`.
 */
VolumeReader::VolumeReader() {
    typesByName["uint8"] = GL_UNSIGNED_BYTE;
    typesByName["int16"] = GL_SHORT;
    typesByName["uint16"] = GL_UNSIGNED_SHORT;
    typesByName["float"] = GL_FLOAT;
}

/**
 * Reads in a volume from a file.
 *
 * @param filename Path to file to read
 * @return Volume that was read
 * @throws std::runtime_error if file is invalid or could not be opened
 */
Volume VolumeReader::read(const std::string& filename) {

    // Open file
    std::ifstream file(filename.c_str());
    if (!file) {
        throw std::runtime_error("[VolumeReader] Could not open file!");
    }

    // Read descriptor
    char descriptor[7];
    file.read(descriptor, 6);
    descriptor[6] = '\0';
    if (strcmp(descriptor, "VLIB.1") != 0) {
        throw std::runtime_error("[VolumeReader] First line of header is not 'VLIB.1'!");
    }

    // Skip comments
    char c = file.peek();
    while (c == '#') {
        file.ignore(INT_MAX, '\n');
        c = file.peek();
    }

    // Create a volume
    Volume volume;

    // Read the details
    volume.size = readWidthHeightDepth(file);
    volume.type = readType(file);
    volume.endianness = readEndianness(file);
    volume.pitch = readPitch(file);
    skipMinMax(file);
    skipHighLow(file);

    // Read the data
    const size_t len = volume.getLength();
    volume.data = new GLubyte[len];
    file.read((char*) volume.data, len);
    if (file.gcount() != len) {
        throw std::runtime_error("[VolumeReader] Did not read expected amount of data!");
    }

    // Return volume
    return volume;
}

std::string VolumeReader::readEndianness(std::ifstream& file) {

    // Read in the endianness
    std::string endianness;
    file >> endianness;
    if (!file) {
        throw std::runtime_error("[VolumeReader] Could not read endianness!");
    }

    // Check it
    if ((endianness != "big") && (endianness != "little")) {
        throw std::runtime_error("[VolumeReader] Endianness is invalid!");
    }

    // Return it
    return endianness;
}

Volume::Pitch VolumeReader::readPitch(std::ifstream& file) {

    // Read in the pitch
    Volume::Pitch pitch;
    file >> pitch.x >> pitch.y >> pitch.z;
    if (!file) {
        throw std::runtime_error("[VolumeReader] Could not read pitch!");
    }

    // Check it
    if ((pitch.x <= 0) || (pitch.y <= 0) || (pitch.z <= 0)) {
        throw std::runtime_error("[VolumeReader] Pitch is invalid!");
    }

    // Return it
    return pitch;
}

GLenum VolumeReader::readType(std::ifstream& file) {

    // Read the type
    std::string typeName;
    file >> typeName;
    if (!file) {
        throw std::runtime_error("[VolumeReader] Could not read type!");
    }

    // Check it
    std::map<std::string,GLenum>::const_iterator it = typesByName.find(typeName);
    if (it == typesByName.end()) {
        throw std::runtime_error("[VolumeReader] Type is invalid!");
    }

    // Return it
    return it->second;
}

Volume::Size VolumeReader::readWidthHeightDepth(std::ifstream& file) {

    // Read the size
    Volume::Size size;
    file >> size.width >> size.height >> size.depth;
    if (!file) {
        throw std::runtime_error("[VolumeReader] Could not read size!");
    }

    // Check it
    if (size.width < 1) {
        throw std::runtime_error("[VolumeReader] Width is invalid!");
    } else if (size.height < 1) {
        throw std::runtime_error("[VolumeReader] Height is invalid!");
    } else if (size.depth < 1) {
        throw std::runtime_error("[VolumeReader] Depth is invalid!");
    }

    // Return it
    return size;
}

void VolumeReader::skipHighLow(std::ifstream& file) {
    file.ignore(INT_MAX, ' ');
    file.ignore(INT_MAX, '\n');
    if (!file) {
        throw std::runtime_error("[VolumeReader] Could not skip low and high!");
    }
}

void VolumeReader::skipMinMax(std::ifstream& file) {
    file.ignore(INT_MAX, ' ');
    file.ignore(INT_MAX, '\n');
    if (!file) {
        throw std::runtime_error("[VolumeReader] Could not skip min and max!");
    }
}

} /* namespace Glycerin */
