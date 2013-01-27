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
#include <m3d/Math.h>
#include "glycerin/Projection.hxx"
using namespace std;
namespace Glycerin {

/**
 * Calculates an orthographic projection matrix.
 *
 *     2/w 0    0  -1
 *     0   2/h  0  -1
 *     0   0   -1   0
 *     0   0    0   1
 *
 * @param width Width of viewport
 * @param height Height of viewport
 * @return Matrix representing orthographic projection
 */
M3d::Mat4 Projection::orthographic(const int width, const int height) {

    M3d::Mat4 m;

    // Scale
    m[0][0] = 2.0 / width;
    m[1][1] = 2.0 / height;
    m[2][2] = -1;
    m[3][3] = 1;

    // Translate
    m[3][0] = -1;
    m[3][1] = -1;

    return m;
}

/**
 * Calculates a perspective projection matrix.
 *
 *     f = cotangent(fovy / 2)
 *
 *     f / a  0    0        0
 *       0    f    0        0
 *               f + n  2 * f * n
 *       0    0  -----  ---------
 *               n - f    f - n
 *       0    0   -1        0
 *
 * @param fovy Field of view angle, in degrees, in Y direction
 * @param aspect Aspect ratio to determine field of view in X direction
 * @param zNear Distance from viewer to near clipping plane (positive)
 * @param zFar Distance from viewer to far clipping plane (positive)
 * @return Matrix representing a perspective projection
 * @throw invalid_argument if either Z distance is not greater than 0
 */
M3d::Mat4 Projection::perspective(const double fovy,
                                  const double aspect,
                                  const double zNear,
                                  const double zFar) {

    double f;
    M3d::Mat4 mat;

    if (zNear <= 0 || zFar <= 0) {
        throw invalid_argument("[Projection] Z distances must be positive!");
    }

    f = 1.0 / tan(M3d::toRadians(fovy) / 2);

    mat[0][0] = f / aspect;
    mat[1][1] = f;
    mat[2][2] = (zFar + zNear) / (zNear - zFar);
    mat[3][2] = (2 * zFar * zNear) / (zNear - zFar);
    mat[2][3] = -1;

    return mat;
}

/**
 * Converts normalized device coordinates to object coordinates.
 *
 * Note that the Y direction for the normalized device coordinates should normally
 * be reversed because OpenGL has its origin at the bottom-left corner, whereas
 * most windowing systems treat the top-left corner as the origin.
 *
 * In addition, as opposed to `gluUnProject`, `unProject` expects to be given the
 * inverse model view projection matrix directly, so that it does not have to
 * invert the matrix every time.
 *
 * @param win Normalized device coordinates, with the Y direction normally reversed
 * @param inverseModelViewProjectionMatrix Inverse model view projection matrix
 * @param viewport Current OpenGL viewport
 * @return Object coordinates corresponding to given device coordinates
 * @see http://www.opengl.org/sdk/docs/man2/xhtml/gluUnProject.xml
 */
M3d::Vec4 Projection::unProject(const M3d::Vec3& win,
                                const M3d::Mat4& inverseModelViewProjectionMatrix,
                                const Viewport& viewport) {

    // Compute coordinates
    M3d::Vec4 p;
    p.x = (2.0 * (win.x - viewport.x()) / viewport.width()) - 1.0;
    p.y = (2.0 * (win.y - viewport.y()) / viewport.height()) - 1.0;
    p.z = (2.0 * win.z) - 1.0;
    p.w = 1.0;

    // Transform
    return inverseModelViewProjectionMatrix * p;
}

} /* namespace Glycerin */
