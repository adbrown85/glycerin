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
#ifndef GLYCERIN_MATRIX_STACK_HXX
#define GLYCERIN_MATRIX_STACK_HXX
#include <stack>
#include <m3d/Mat4.hxx>
#include "glycerin/common.h"
namespace Glycerin {


/**
 * Stack of 4x4 matrices.
 *
 * `MatrixStack` is intended to keep track of the state of a transformation while
 * traversing a hierarchical model or scene graph.  It can be used to keep track of
 * your model, view, and projection matrices.
 *
 * `MatrixStack` is patterned after the matrix stack functionality in earlier
 * versions of OpenGL.   As opposed to `std::stack` this stack cannot be empty.
 * Instead it is initialized with a copy of the identity matrix that can be modified
 * but cannot be removed.  If [pop] is called when the stack only has one element,
 * an exception is thrown.  In addition, [push] automatically copies the matrix at
 * the top of the stack.  Generally users should call `push` before modifying the
 * top of the stack, and then call `pop` again when their done.
 *
 * [pop]: @ref pop() "pop()"
 * [push]: @ref push() "push()"
 */
class MatrixStack {
public:
// Methods
    MatrixStack();
    void push();
    void pop();
    size_t size() const;
    M3d::Mat4& top();
    const M3d::Mat4& top() const;
private:
// Attributes
    std::stack<M3d::Mat4> _stack;
};

} /* namespace Glycerin */
#endif
