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
#include "glycerin/BufferLayoutBuilder.hxx"
using namespace std;
namespace Glycerin {

BufferLayoutBuilder::State* BufferLayoutBuilder::INTERLEAVED = new InterleavedState();
BufferLayoutBuilder::State* BufferLayoutBuilder::NON_INTERLEAVED = new NonInterleavedState();

/**
 * Constructs a buffer layout builder.
 */
BufferLayoutBuilder::BufferLayoutBuilder() {
    _components = DEFAULT_COMPONENTS;
    _count = DEFAULT_COUNT;
    _normalized = DEFAULT_NORMALIZED;
    _type = DEFAULT_TYPE;
    _state = NON_INTERLEAVED;
}

/**
 * Destroys a buffer layout builder.
 */
BufferLayoutBuilder::~BufferLayoutBuilder() {
    // pass
}

/**
 * Builds a buffer layout using the regions that have been added to the builder.
 */
BufferLayout BufferLayoutBuilder::build() {

    // Compute strides and offsets
    _state->computeStrides(regions());
    _state->computeOffsets(regions());

    // Create layout
    const bool interleaved = (_state == INTERLEAVED);
    return BufferLayout(regions(), interleaved);
}

/**
 * Changes the number of components in subsequent regions.
 *
 * @param components Number of components in subsequent regions
 * @return Reference to this builder to support chaining
 * @throws invalid_argument if number of components is less than one or more than four
 */
BufferLayoutBuilder& BufferLayoutBuilder::components(const GLuint components) {
    if (components < MIN_REGION_COMPONENTS) {
        throw invalid_argument("[BufferLayoutBuilder] Number of components is less than one!");
    } else if (components > MAX_REGION_COMPONENTS) {
        throw invalid_argument("[BufferLayoutBuilder] Number of components is more than four!");
    }
    _components = components;
    return (*this);
}

/**
 * Changes the number of vectors in subsequent regions.
 *
 * @param count Number of vectors in subsequent regions
 * @return Reference to this builder to support chaining
 * @throws invalid_argument if count is less than one
 * @throws logic_error if layout is interleaved and count doesn't match previous regions
 */
BufferLayoutBuilder& BufferLayoutBuilder::count(const GLuint count) {

    // Check for invalid count
    if (count < MIN_REGION_COUNT) {
        throw invalid_argument("[BufferLayoutBuilder] Count is less than one!");
    }

    // Check for interleaved
    if ((_state == INTERLEAVED) && !_regions.empty()) {
        if (count != _count) {
            throw logic_error("[BufferLayoutBuilder] Counts in interleaved layout must be equal!");
        }
    }

    // Otherwise copy count
    _count = count;

    // Return self
    return (*this);
}

/**
 * Changes whether regions in the layout will be interleaved together.
 *
 * @param interleaved Whether regions will be interleaved
 * @return Reference to this builder to support chaining
 */
BufferLayoutBuilder& BufferLayoutBuilder::interleaved(const bool interleaved) {

    // Check if all counts match
    if (interleaved && !_regions.empty()) {
        const_iterator r = _regions.begin();
        const GLuint first = r->_count;
        while (r != _regions.end()) {
            if (r->_count != first) {
                throw logic_error("[BufferLayout] Counts in interleaved layout must be equal!");
            }
            ++r;
        }
    }

    // Otherwise copy interleaved
    _state = interleaved ? INTERLEAVED : NON_INTERLEAVED;

    // Return self
    return (*this);
}

/**
 * Changes whether subsequent regions should be normalized.
 *
 * @param normalized Whether subsequent regions should be normalized
 * @return Reference to this builder to support chaining
 */
BufferLayoutBuilder& BufferLayoutBuilder::normalized(const bool normalized) {
    _normalized = normalized;
    return (*this);
}

/**
 * Adds a region to the buffer layout using the current state of the builder.
 *
 * @param name Name of the region
 * @return Reference to this builder to support chaining
 * @throws invalid_argument if name is empty, or layout already contains a region with same name
 * @throws logic_error if count has not been set yet
 */
BufferLayoutBuilder& BufferLayoutBuilder::region(const string& name) {

    // Check name is not empty
    if (name.empty()) {
        throw invalid_argument("[BufferLayoutBuilder] Region name is empty!");
    }

    // Check name is not already in layout
    set<string>::const_iterator it = _names.find(name);
    if (it != _names.end()) {
        throw invalid_argument("[BufferLayoutBuilder] Name already in layout!");
    }

    // Check count is is in-range
    if (_count < MIN_REGION_COUNT) {
        throw logic_error("[BufferLayoutBuilder] Count has not been set!");
    }

    // Add the region
    BufferRegion region;
    region._components = _components;
    region._count = _count;
    region._name = name;
    region._normalized = _normalized;
    region._type = _type;
    _regions.push_back(region);
    _names.insert(name);

    // Return self
    return (*this);
}

/**
 * Returns a pair of iterators over the regions in the layout.
 */
BufferLayoutBuilder::iterator_pair BufferLayoutBuilder::regions() {
    iterator beg = _regions.begin();
    iterator end = _regions.end();
    return make_pair(beg, end);
}

/**
 * Returns a pair of read-only iterators over the regions in the layout.
 */
BufferLayoutBuilder::const_iterator_pair BufferLayoutBuilder::regions() const {
    const_iterator beg = _regions.begin();
    const_iterator end = _regions.end();
    return make_pair(beg, end);
}

/**
 * Changes the data type of components in subsequent regions.
 *
 * @param type Data type of components in subsequent regions, e.g. `GL_FLOAT`
 * @return Reference to this builder to support chaining
 * @throws invalid_argument if type is not recognized
 */
BufferLayoutBuilder& BufferLayoutBuilder::type(const GLenum type) {
    if (!isValidType(type)) {
        throw invalid_argument("[BufferLayoutBuilder] Type is unrecognized!");
    }
    _type = type;
    return (*this);
}

/**
 * Checks if a component type is valid.
 *
 * @param type Type to check
 * @return `true` if type is a valid component type
 */
bool BufferLayoutBuilder::isValidType(const GLenum type) {
    switch (type) {
    case GL_FLOAT:
    case GL_INT:
    case GL_UNSIGNED_INT:
        return true;
    default:
        return false;
    }
}

/**
 * Returns the size in bytes of an OpenGL type.
 *
 * @param type Enumeration of OpenGL type to find size of
 * @return Size of type in bytes
 * @throws std::invalid_argument if type is invalid
 */
GLsizei BufferLayoutBuilder::sizeOf(const GLenum type) {
    switch (type) {
    case GL_FLOAT:
        return sizeof(GLfloat);
    case GL_INT:
        return sizeof(GLint);
    case GL_UNSIGNED_INT:
        return sizeof(GLuint);
    default:
        throw runtime_error("[BufferLayoutBuilder] Unrecognized type!");
    }
}

//
// STATES
//

/**
 * Calculates the offsets for a range of regions when the buffer is interleaved.
 *
 * @param regions Pair of iterators over the range of regions to calculate offsets for
 */
void BufferLayoutBuilder::InterleavedState::computeOffsets(iterator_pair regions) {
    GLsizei offset = 0;
    for (iterator r = regions.first; r != regions.second; ++r) {
        r->_offset = offset;
        offset += sizeOf(r->_type) * r->_components;
    }
}

/**
 * Calculates the strides for a range of regions when the buffer is interleaved.
 *
 * @param regions Pair of iterators over the range of regions to calculate strides for
 */
void BufferLayoutBuilder::InterleavedState::computeStrides(iterator_pair regions) {

    // First add up stride
    GLsizei stride = 0;
    for (const_iterator r = regions.first; r != regions.second; ++r) {
        stride += sizeOf(r->_type) * r->_components;
    }

    // Then copy to each region
    for (iterator r = regions.first; r != regions.second; ++r) {
        r->_stride = stride;
    }
}

/**
 * Calculates the offsets for a range of regions when the buffer is not interleaved.
 *
 * @param regions Pair of iterators over the range of regions to calculate offsets for
 */
void BufferLayoutBuilder::NonInterleavedState::computeOffsets(iterator_pair regions) {
    GLsizei offset = 0;
    for (iterator r = regions.first; r != regions.second; ++r) {
        r->_offset = offset;
        offset += sizeOf(r->_type) * r->_components * r->_count;
    }
}

/**
 * Calculates the strides for a range of regions when the buffer is not interleaved.
 *
 * @param regions Pair of iterators over the range of regions to calculate strides for
 */
void BufferLayoutBuilder::NonInterleavedState::computeStrides(iterator_pair regions) {
    for (iterator r = regions.first; r != regions.second; ++r) {
        const GLsizei stride = sizeOf(r->_type) * r->_components;
        r->_stride = stride;
    }
}

} /* namespace Glycerin */
