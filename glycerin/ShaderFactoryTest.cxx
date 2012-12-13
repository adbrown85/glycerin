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
#include <cassert>
#include <stdexcept>
#include <boost/filesystem.hpp>
#include <cppunit/extensions/HelperMacros.h>
#include <GL/glfw.h>
#include "glycerin/ShaderFactory.hxx"
using namespace std;
using namespace Glycerin;
namespace bfs = boost::filesystem;


/**
 * Unit test for ShaderFactory.
 */
class ShaderFactoryTest {
public:

    /**
     * Ensures createShaderFromString works correctly with a vertex shader.
     */
    void testCreateShaderFromStringWithVertexShader() {
        ShaderFactory sf;
        const Gloop::Shader shader = sf.createShaderFromString(
                GL_VERTEX_SHADER,
                "#version 140\n"
                "in vec4 MCVertex;\n"
                "void main() {\n"
                "   gl_Position = MCVertex;\n"
                "}\n");
        CPPUNIT_ASSERT(shader.id() != 0);
        CPPUNIT_ASSERT(shader.compiled());
    }

    /**
     * Ensures createShaderFromString works correctly with a fragment shader.
     */
    void testCreateShaderFromStringWithFragmentShader() {
        ShaderFactory sf;
        const Gloop::Shader shader = sf.createShaderFromString(
                GL_FRAGMENT_SHADER,
                "#version 140\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "    FragColor = vec4(1);\n"
                "}\n");
        CPPUNIT_ASSERT(shader.id() != 0);
        CPPUNIT_ASSERT(shader.compiled());
    }
};

int main(int argc, char* argv[]) {

    // Capture the initial working directory before GLFW changes it
    bfs::path dir = bfs::initial_path();

    // Initialize GLFW
    if (!glfwInit()) {
        cerr << "Could not initialize GLFW!" << endl;
        return 1;
    }

    // Reset current directory
    bfs::current_path(dir);

    // Open a window
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwOpenWindow(512, 512, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);

    // Run the test
    ShaderFactoryTest test;
    try {
        test.testCreateShaderFromStringWithVertexShader();
        test.testCreateShaderFromStringWithFragmentShader();
    } catch (exception& e) {
        cerr << e.what() << endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
