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
#include "glycerin/BufferLayout.hxx"
using namespace std;
namespace Glycerin {

/**
 * Constructs a buffer layout.
 *
 * @param regions Regions in the layout
 * @param interleaved Whether regions are interleaved
 */
BufferLayout::BufferLayout(const_iterator_pair regions, bool interleaved) {

    // Store whether interleaved or not
    _interleaved = interleaved;

    // Copy the regions
    int idx = 0;
    for (const_iterator r = regions.first; r != regions.second; ++r) {
        _indices[r->name()] = idx++;
        _regions.push_back((*r));
    }
}

/**
 * Constructs a buffer layout by copying another one.
 *
 * @param layout Other buffer layout to copy
 */
BufferLayout::BufferLayout(const BufferLayout& layout) {
    _indices = layout._indices;
    _interleaved = layout._interleaved;
    _regions = layout._regions;
}

/**
 * Destroys a buffer layout.
 */
BufferLayout::~BufferLayout() {
    // pass
}

/**
 * Returns an iterator to the first region in the buffer layout.
 */
BufferLayout::const_iterator BufferLayout::begin() const {
    return _regions.begin();
}

/**
 * Returns an iterator past the last region in the buffer layout.
 */
BufferLayout::const_iterator BufferLayout::end() const {
    return _regions.end();
}

/**
 * Finds a region in the buffer layout.
 *
 * @param name Name of the region to find
 * @return Iterator for the region
 */
BufferLayout::const_iterator BufferLayout::find(const std::string& name) const {
    const map<string,int>::const_iterator i = _indices.find(name);
    if (i == _indices.end()) {
        return _regions.end();
    } else {
        return _regions.begin() + i->second;
    }
}

/**
 * Checks if the layout is interleaved.
 *
 * @return `true` if layout is interleaved
 */
bool BufferLayout::interleaved() const {
    return _interleaved;
}

/**
 * Copies another buffer layout.
 *
 * @param layout Other buffer layout to copy
 * @return Reference to this buffer layout
 */
BufferLayout& BufferLayout::operator=(const BufferLayout& layout) {
    _indices = layout._indices;
    _interleaved = layout._interleaved;
    _regions = layout._regions;
}

} /* namespace Glycerin */
