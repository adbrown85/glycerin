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
#include <map>
#include <stdexcept>
#include <string>
#include <GL/glfw.h>
#include <gloop/BufferObject.hxx>
#include <gloop/BufferTarget.hxx>
#include <gloop/Program.hxx>
#include <gloop/Shader.hxx>
#include <gloop/TextureObject.hxx>
#include <gloop/TextureTarget.hxx>
#include <gloop/VertexArrayObject.hxx>
#include <gloop/Uniform.hxx>
#include "glycerin/Volume.hxx"
#include "glycerin/VolumeReader.hxx"


/**
 * Test for `Volume`.
 */
class VolumeTest {
public:

    /**
     * Creates the texture from the volume.
     */
    static Gloop::TextureObject createTexture() {
        Glycerin::VolumeReader reader;
        const Glycerin::Volume volume = reader.read("glycerin/bunny.vlb");
        return volume.createTexture();
    }

    /**
     * Returns the source code for the vertex shader.
     */
    static std::string getVertexShaderSource() {
        return
                "#version 140\n"
                "in vec4 MCVertex;\n"
                "in vec4 TexCoord0;\n"
                "out vec4 Coord0;\n"
                "void main() {\n"
                "  gl_Position = MCVertex;\n"
                "  Coord0 = TexCoord0;\n"
                "}\n";
    }

    /**
     * Returns the source code for the fragment shader.
     */
    static std::string getFragmentShaderSource() {
        return
                "#version 140\n"
                "uniform sampler3D Texture;\n"
                "uniform float P;\n"
                "in vec4 Coord0;\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "  float value = texture(Texture, vec3(Coord0.st, P)).r;\n"
                "  FragColor = vec4(vec3(value), 1);\n"
                "}\n";
    }

    /**
     * Creates the program.
     */
    static Gloop::Program createProgram() {

        // Create program
        const Gloop::Program program = Gloop::Program::create();

        // Store source code by type
        std::map<GLenum,std::string> sources;
        sources[GL_VERTEX_SHADER] = getVertexShaderSource();
        sources[GL_FRAGMENT_SHADER] = getFragmentShaderSource();

        // Create, compile, and attach shaders
        for (std::map<GLenum,std::string>::const_iterator it = sources.begin(); it != sources.end(); ++it) {
            const Gloop::Shader shader = Gloop::Shader::create(it->first);
            program.attachShader(shader);
            shader.source(it->second);
            shader.compile();
            if (!shader.compiled()) {
                throw std::runtime_error(shader.log());
            }
        }

        // Link program
        program.link();
        if (!program.linked()) {
            throw std::runtime_error(program.log());
        }

        // Return the program
        return program;
    }

    // Handle for shader program
    const Gloop::Program program;

    // Target for array buffer
    const Gloop::BufferTarget arrayBuffer;

    // Vertex buffer object
    const Gloop::BufferObject vbo;

    // State of vertex arrays
    const Gloop::VertexArrayObject vao;

    // Target for a 3D texture
    const Gloop::TextureTarget texture3d;

    // Texture containing volume
    const Gloop::TextureObject texture;

    /**
     * Constructs the test.
     */
    VolumeTest() :
            program(createProgram()),
            arrayBuffer(Gloop::BufferTarget::arrayBuffer()),
            vbo(Gloop::BufferObject::generate()),
            vao(Gloop::VertexArrayObject::generate()),
            texture3d(Gloop::TextureTarget::texture3d()),
            texture(createTexture()) {

        // Set up the VBO
        arrayBuffer.bind(vbo);
        GLfloat data[] = {
                +1.0f, +1.0f,
                -1.0f, +1.0f,
                -1.0f, -1.0f,
                -1.0f, -1.0f,
                +1.0f, -1.0f,
                +1.0f, +1.0f,
                1.0f, 1.0f,
                0.0f, 1.0f,
                0.0f, 0.0f,
                0.0f, 0.0f,
                1.0f, 0.0f,
                1.0f, 1.0f };
        arrayBuffer.data(sizeof(data), data, GL_STATIC_DRAW);

        // Set up the VAO
        vao.bind();
        const GLint pointLoc = program.attribLocation("MCVertex");
        vao.enableVertexAttribArray(pointLoc);
        vao.vertexAttribPointer(Gloop::VertexAttribPointer().index(pointLoc).size(2));
        const GLint coordLoc = program.attribLocation("TexCoord0");
        vao.enableVertexAttribArray(coordLoc);
        vao.vertexAttribPointer(Gloop::VertexAttribPointer().index(coordLoc).size(2).offset(sizeof(data) / 2));
    }

    /**
     * Ensures `Volume::createTexture` works correctly.
     */
    void testCreateTexture() {

        // Find uniform for texture
        const std::map<std::string,Gloop::Uniform> uniforms = program.activeUniforms();
        Gloop::Uniform p = (uniforms.find("P"))->second;

        // Activate and bind
        program.use();
        vao.bind();
        texture3d.bind(texture);

        // Render
        const int n = 200;
        for (int i = 0; i < n; ++i) {
            p.load1f(((float) i) / n);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glfwSwapBuffers();
        }
    }
};

int main(int argc, char* argv[]) {

    // Store working directory before GLFW changes it
#ifdef __APPLE__
    char cwd[PATH_MAX];
    if (!getcwd(cwd, PATH_MAX)) {
        throw std::runtime_error("Could not get working directory!");
    }
#endif

    // Initialize GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Could not initialize GLFW!");
    }

    // Reset working directory
#ifdef __APPLE__
    chdir(cwd);
#endif

    // Open window
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (!glfwOpenWindow(512, 512, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)) {
        throw std::runtime_error("Could not open GLFW window!");
    }

    // Run the test
    try {
        VolumeTest test;
        test.testCreateTexture();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
