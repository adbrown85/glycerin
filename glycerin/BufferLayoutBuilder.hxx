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
#ifndef GLYCERIN_BUFFERLAYOUTBUILDER_HXX
#define GLYCERIN_BUFFERLAYOUTBUILDER_HXX
#include <set>
#include "glycerin/common.h"
#include "glycerin/BufferRegion.hxx"
#include "glycerin/BufferLayout.hxx"
namespace Glycerin {


/**
 * Utility for building a buffer layout.
 *
 * _BufferLayoutBuilder_ creates _BufferLayout_ instances.  The user defines
 * the desired properties for the regions, and then directs the builder to
 * create the layout.  The state of each property is maintained from region to
 * region unless changed by the user, making most layouts very easy to make.
 *
 * To get started with _BufferLayoutBuilder_, first create one.
 *
 * ~~~
 * BufferLayoutBuilder builder;
 * ~~~
 *
 * Then start defining the properties of the first region you'd like in the
 * buffer layout.  You can specify the number of components per vector with
 * _components_, the number of vectors per region with _count_, whether the
 * vector components should be normalized with _normalized_, and the data type
 * of the vector components with _type_.
 *
 * ~~~
 * builder.components(3);
 * builder.count(24);
 * builder.normalized(false);
 * builder.type(GL_FLOAT);
 * ~~~
 *
 * Since the builder starts with valid default values for the _component_,
 * _normalized_, and _type_ properties, the user can leave them unspecified if
 * desired.  The _components_ property starts with `4`, _normalized_ starts
 * with `false`, and _type_ starts with `GL_FLOAT`.  Therefore the following
 * code segment is equivalent to the one above.
 *
 * ~~~
 * builder.components(3);
 * builder.count(24);
 * ~~~
 *
 * Then add the first region using _region_, giving it the name that you want
 * to refer to it by later.  The current state of the builder's properties will
 * be captured and used for the region when the buffer layout is built later.
 *
 * ~~~
 * builder.region("MCVertex");
 * ~~~
 *
 * From there, more regions can be added by changing properties and calling
 * _region_ again with different names.  If you don't change a property when
 * you add a new region, that property will have the same value as the previous
 * region.  For example, the two regions that are added below will still
 * include _24_ vectors, be of type `GL_FLOAT`, and should not be normalized.
 * However, the _Normal_ region will have three components per vector whereas
 * the _TexCoord0_ region will only have two.
 *
 * ~~~
 * builder.region("Normal");
 * builder.components(2);
 * builder.region("TexCoord0");
 * ~~~
 *
 * To make things even easier, most calls can be chained together.  For
 * example, the first three regions could have been added with the more compact
 * form below.  Notice that often the only property that needs to change is
 * _components_.
 *
 * ~~~
 * builder.count(24);
 * builder.components(3).region("MCVertex");
 * builder.components(4).region("Color");
 * builder.components(2).region("TexCoord0");
 * ~~~
 *
 * In addtion, if the number of vectors in each region is the same, the regions
 * can be interleaved.  An interleaved buffer layout will alternate vectors
 * from each region, often making it easier for the video card to iterate
 * through.  However, it is generally harder to update an interleaved buffer,
 * since all the vectors for one region are no longer together.
 *
 * ~~~
 * builder.interleaved(true);
 * ~~~
 *
 * When all the regions have been added, call _build_ to make the buffer
 * layout.
 *
 * ~~~
 * const BufferLayout layout = builder.build();
 * ~~~
 *
 * The offset and stride, as well as all the properties you specified can be
 * retrieved using the accessors of each region.  The code segment below sets
 * up vertex attribute pointers for a buffer by iterating through the regions
 * in the layout.
 *
 * ~~~
 * for (BufferLayout::const_iterator r = layout.begin(); r != layout.end(); ++r) {
 *     const char* name = r->name().c_str();
 *     const GLuint location = glGetAttribLocation(program, name);
 *     glEnableVertexAttribArray(location);
 *     glVertexAttribPointer(
 *             location,
 *             r->components(),
 *             r->type(),
 *             r->normalized(),
 *             r->stride(),
 *             r->offset());
 * }
 * ~~~
 *
 * @ingroup extensions
 */
class BufferLayoutBuilder {
public:
// Methods
    BufferLayoutBuilder();
    virtual ~BufferLayoutBuilder();
    BufferLayout build();
    BufferLayoutBuilder& components(GLuint components);
    BufferLayoutBuilder& count(GLuint count);
    BufferLayoutBuilder& interleaved(bool interleaved);
    BufferLayoutBuilder& normalized(bool normalized);
    BufferLayoutBuilder& region(const std::string& name);
    BufferLayoutBuilder& type(GLenum type);
private:
// Types
    class State;
    class InterleavedState;
    class NonInterleavedState;
    typedef std::vector<BufferRegion>::iterator iterator;
    typedef std::pair<iterator,iterator> iterator_pair;
    typedef std::vector<BufferRegion>::const_iterator const_iterator;
    typedef std::pair<const_iterator,const_iterator> const_iterator_pair;
// Attributes
    GLuint _components;
    GLuint _count;
    std::set<std::string> _names;
    bool _normalized;
    std::vector<BufferRegion> _regions;
    State* _state;
    GLenum _type;
// Methods
    BufferLayoutBuilder(const BufferLayoutBuilder&);
    BufferLayoutBuilder& operator=(const BufferLayoutBuilder&);
    static bool isValidType(GLenum type);
    iterator_pair regions();
    const_iterator_pair regions() const;
    static GLsizei sizeOf(GLenum type);
// Constants
    static const GLsizei DEFAULT_COMPONENTS = 4;
    static const GLuint DEFAULT_COUNT = 0;
    static const bool DEFAULT_NORMALIZED = false;
    static const GLsizei DEFAULT_OFFSET = 0;
    static const GLsizei DEFAULT_STRIDE = 0;
    static const GLenum DEFAULT_TYPE = GL_FLOAT;
    static State* INTERLEAVED;
    static State* NON_INTERLEAVED;
    static const size_t MIN_REGION_COMPONENTS = 1;
    static const size_t MAX_REGION_COMPONENTS = 4;
    static const size_t MIN_REGION_COUNT = 1;
    static const size_t MAX_REGION_COUNT = SIZE_MAX;
};


class BufferLayoutBuilder::State {
public:
    virtual void computeStrides(iterator_pair regions) = 0;
    virtual void computeOffsets(iterator_pair regions) = 0;
};


class BufferLayoutBuilder::InterleavedState : public BufferLayoutBuilder::State {
public:
    virtual void computeStrides(iterator_pair regions);
    virtual void computeOffsets(iterator_pair regions);
};


class BufferLayoutBuilder::NonInterleavedState : public BufferLayoutBuilder::State {
public:
    virtual void computeStrides(iterator_pair regions);
    virtual void computeOffsets(iterator_pair regions);
};

} /* namespace Glycerin */
#endif
