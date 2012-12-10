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
#include "glycerin/BitmapReader.hxx"
using namespace std;
namespace Glycerin {

/**
 * Constructs a new image reader.
 */
BitmapReader::BitmapReader() {
    // empty
}

/**
 * Destroys the image reader.
 */
BitmapReader::~BitmapReader() {
    // empty
}

/**
 * Checks if any info header fields indicate the data is compressed.
 *
 * @param infoHeader Info header to check
 * @return `true` if any info header fields indicate the data is compressed
 */
bool BitmapReader::isCompressed(const InfoHeader& infoHeader) {
    return infoHeader.biCompression != 0;
}

/**
 * Checks if info header fields indicate the data is 24-bit.
 *
 * @param infoHeader Info header to check
 * @return `true` if info header fields indicate the data is 24-bit
 */
bool BitmapReader::isTwentyFourBit(const InfoHeader& infoHeader) {
    return infoHeader.biBitCount == 24
            && infoHeader.biClrUsed == 0
            && infoHeader.biClrImportant == 0;
}

/**
 * Checks if the file header is valid.
 *
 * @param fileHeader File header to check
 * @return `true` if the file header is valid
 */
bool BitmapReader::isValidFileHeader(const FileHeader& fileHeader) {
    return fileHeader.bfType[0] == 'B'
            && fileHeader.bfType[1] == 'M'
            && fileHeader.bfReserved1 == 0
            && fileHeader.bfReserved2 == 0;
}

/**
 * Checks if the info header is valid.
 *
 * @param infoHeader Info header to check
 * @return `true` if the info header is valid
 */
bool BitmapReader::isValidInfoHeader(const InfoHeader& infoHeader) {
    return infoHeader.biSize == 40
            && infoHeader.biWidth > 0
            && infoHeader.biHeight > 0
            && infoHeader.biPlanes == 1;
}

/**
 * Reads an image into memory.
 *
 * @param filename Path to the file to read
 * @return Bitmap containing pixels of and information about the image
 * @throws invalid_argument if file cannot be opened
 * @throws runtime_error if file is not valid, is compressed, is not 24-bit, or cannot be read
 */
Bitmap BitmapReader::read(const string &filename) {

    // Open the file
    ifstream file(filename.c_str(), ios_base::binary);
    if (!file) {
        throw invalid_argument("[BitmapReader] File does not exist!");
    }

    // Read in the file
    const FileHeader fileHeader = readFileHeader(file);
    const InfoHeader infoHeader = readInfoHeader(file);
    const GLubyte* pixels = readPixels(file, infoHeader.biSizeImage);

    // Make the bitmap
    Bitmap bitmap;
    bitmap.pixels = (GLubyte*) pixels;
    bitmap.format = FORMAT;
    bitmap.width = infoHeader.biWidth;
    bitmap.height = infoHeader.biHeight;
    bitmap.size = infoHeader.biSizeImage;
    bitmap.alignment = ALIGNMENT;
    return bitmap;
}

/**
 * Reads just the file header section.
 *
 * @param file File to read from
 * @return File header that was read
 * @throws runtime_error if not a valid file header
 */
BitmapReader::FileHeader BitmapReader::readFileHeader(ifstream& file) {

    FileHeader fileHeader;

    file.read((char*) &fileHeader.bfType, 2);
    file.read((char*) &fileHeader.bfSize, 4);
    file.read((char*) &fileHeader.bfReserved1, 2);
    file.read((char*) &fileHeader.bfReserved2, 2);
    file.read((char*) &fileHeader.bfOffBits, 4);

    if (!isValidFileHeader(fileHeader)) {
        throw runtime_error("[BitmapReader] Not a valid bitmap file header!");
    }

    return fileHeader;
}

/**
 * Reads just the info header section.
 *
 * @param file File to read from
 * @return InfoHeader that was read
 * @throws runtime_error if not a valid info header, is compressed, or is not 24-bit
 */
BitmapReader::InfoHeader BitmapReader::readInfoHeader(ifstream& file) {

    InfoHeader infoHeader;

    file.read((char*) &infoHeader.biSize, 4);
    file.read((char*) &infoHeader.biWidth, 4);
    file.read((char*) &infoHeader.biHeight, 4);
    file.read((char*) &infoHeader.biPlanes, 2);
    file.read((char*) &infoHeader.biBitCount, 2);
    file.read((char*) &infoHeader.biCompression, 4);
    file.read((char*) &infoHeader.biSizeImage, 4);
    file.read((char*) &infoHeader.biXPelsPerMeter, 4);
    file.read((char*) &infoHeader.biYPelsPerMeter, 4);
    file.read((char*) &infoHeader.biClrUsed, 4);
    file.read((char*) &infoHeader.biClrImportant, 4);

    if (!isValidInfoHeader(infoHeader)) {
        throw runtime_error("[BitmapReader] Not a valid bitmap info header!");
    }

    if (isCompressed(infoHeader)) {
        throw runtime_error("[BitmapReader] Only supports uncompressed data.");
    }

    if (!isTwentyFourBit(infoHeader)) {
        throw runtime_error("[BitmapReader] Only supports 24-bit data.");
    }

    return infoHeader;
}

/**
 * Reads the pixel data into memory.
 *
 * @param file File to read from
 * @param size Number of bytes to read
 * @return Pointer to a byte array containing the pixels
 * @throws runtime_error if improper amount of pixels were read
 */
GLubyte* BitmapReader::readPixels(ifstream& file, const size_t size) {
    GLubyte* const pixels = new GLubyte[size];
    file.read((char*) pixels, size);
    if (file.gcount() != size) {
        throw runtime_error("[BitmapReader] All pixels could not be read!");
    }
    return pixels;
}


} /* namespace Glycerin */
