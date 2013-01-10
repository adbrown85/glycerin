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
#ifndef GLYCERIN_VOLUME_READER_HXX
#define GLYCERIN_VOLUME_READER_HXX
#include <fstream>
#include <map>
#include <string>
#include "glycerin/common.h"
#include "glycerin/Volume.hxx"
namespace Glycerin {


/**
 * Utility for reading a volume from a file.
 */
class VolumeReader {
public:
// Methods
    VolumeReader();
    Volume read(const std::string& filename);
private:
// Attributes
    std::map<std::string,GLenum> typesByName;
// Methods
    std::string readEndianness(std::ifstream& file);
    Volume::Pitch readPitch(std::ifstream& file);
    GLenum readType(std::ifstream& file);
    Volume::Size readWidthHeightDepth(std::ifstream& file);
    void skipHighLow(std::ifstream& file);
    void skipMinMax(std::ifstream& file);
};

} /* namespace Glycerin */
#endif
