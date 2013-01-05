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
#include "glycerin/MatrixStack.hxx"
namespace Glycerin {

/**
 * Constructs a matrix stack initialized with the identity matrix.
 */
MatrixStack::MatrixStack() {
    _stack.push(M3d::Mat4(1));
}

/**
 * Removes the matrix at the top of this stack.
 *
 * @throws std::runtime_error if stack only has one element
 */
void MatrixStack::pop() {
    if (size() == 1) {
        throw std::runtime_error("[MatrixStack] Cannot remove bottom of stack!");
    }
    _stack.pop();
}

/**
 * Copies the matrix a the top of this stack and adds it.
 */
void MatrixStack::push() {
    _stack.push(_stack.top());
}

/**
 * Returns the number of matrices on this matrix stack.
 *
 * @return Number of matrices on this matrix stack
 */
size_t MatrixStack::size() const {
    return _stack.size();
}

/**
 * Returns a reference to the matrix at the top of this stack.
 *
 * @return Reference to the matrix at the top of this stack
 */
M3d::Mat4& MatrixStack::top() {
    return _stack.top();
}

/**
 * Returns a constant reference to the matrix at the top of this stack.
 *
 * @return Constant reference to the matrix at the top of this stack
 */
const M3d::Mat4& MatrixStack::top() const {
    return _stack.top();
}

} /* namespace Glycerin */
