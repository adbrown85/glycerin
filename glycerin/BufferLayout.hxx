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
#ifndef GLYCERIN_BUFFERLAYOUT_HXX
#define GLYCERIN_BUFFERLAYOUT_HXX
#include "glycerin/common.h"
#include <map>
#include <vector>
#include "glycerin/BufferRegion.hxx"
namespace Glycerin {


/**
 * Layout of a buffer.
 *
 * @ingroup extensions
 */
class BufferLayout {
public:
// Types
    typedef std::vector<BufferRegion>::const_iterator const_iterator; ///< Iterator over regions in layout
// Methods
    BufferLayout(const BufferLayout& layout);
    virtual ~BufferLayout();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator find(const std::string& name) const;
    bool interleaved() const;
    BufferLayout& operator=(const BufferLayout& layout);
private:
// Types
    typedef std::pair<const_iterator,const_iterator> const_iterator_pair;
    typedef std::vector<BufferRegion>::iterator iterator;
    typedef std::pair<iterator,iterator> iterator_pair;
// Attributes
    std::map<std::string,int> _indices;
    bool _interleaved;
    std::vector<BufferRegion> _regions;
// Methods
    BufferLayout();
    BufferLayout(const_iterator_pair regions, bool interleaved);
// Friends
    friend class BufferLayoutBuilder;
};

} /* namespace Glycerin */
#endif
