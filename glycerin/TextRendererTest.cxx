/*
 * Glycerin - Fuel for OpenGL applications
 * Copyright (C) 2013  Andrew Brown
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
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <GL/glfw.h>
#include "glycerin/TextRenderer.hxx"


/**
 * Test for `TextRenderer`.
 */
class TextRendererTest {
public:

    /**
     * Tests `TextRenderer::draw`.
     */
    void testDraw() {

        // Clear
        glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render text
        Glycerin::TextRenderer textRenderer;
        textRenderer.beginRendering(512, 512);
        textRenderer.draw("Hello, World! 12345", 10, 10);
        textRenderer.endRendering();

        // Flush and wait
        glfwSwapBuffers();
        glfwSleep(2.0);
    }
};

int main(int argc, char* argv[]) {

#ifdef __APPLE__
    // Store working directory before GLFW changes it
    char cwd[PATH_MAX];
    if (!getcwd(cwd, PATH_MAX)) {
        throw std::runtime_error("Could not get working directory!");
    }
#endif

    // Initialize GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Could not initialize GLFW!");
    }

#ifdef __APPLE__
    // Reset working directory
    chdir(cwd);
#endif

    // Open window
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (!glfwOpenWindow(512, 512, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)) {
        throw std::runtime_error("Could not open window!");
    }

    // Run test
    try {
        TextRendererTest test;
        test.testDraw();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
