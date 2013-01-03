#include "config.h"
#include <cassert>
#include <GL/glfw.h>
#include <gloop/BufferObject.hxx>
#include <gloop/BufferTarget.hxx>
#include <gloop/Program.hxx>
#include <gloop/Shader.hxx>
#include <gloop/TextureObject.hxx>
#include <gloop/VertexArrayObject.hxx>
#include <gloop/VertexAttribPointer.hxx>
#include <iostream>
#include <stdexcept>
#include <string>
#include "glycerin/Bitmap.hxx"
#include "glycerin/BitmapReader.hxx"
#include "glycerin/BufferLayoutBuilder.hxx"
#include "glycerin/ShaderFactory.hxx"


/**
 * Unit test for Bitmap.
 */
class BitmapTest {
public:

    // Number of seconds to sleep after rendering
    static const int SLEEP_TIME_IN_SECONDS = 1;

    /**
     * Returns the source code for the vertex shader.
     */
    static std::string getVertexShaderCode() {
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
    static std::string getFragmentShaderCode() {
        return
                "#version 140\n"
                "uniform sampler2D Texture;\n"
                "in vec4 Coord0;\n"
                "out vec4 FragColor;\n"
                "void main() {\n"
                "  FragColor = texture(Texture, Coord0.st);\n"
                "}\n";
    }

    // Shader program
    const Gloop::Program program;

    // Vertex array object
    const Gloop::VertexArrayObject vao;

    /**
     * Constructs the test.
     */
    BitmapTest() :
            program(Gloop::Program::create()),
            vao(Gloop::VertexArrayObject::generate()) {

        // Compile shaders
        Glycerin::ShaderFactory sf;
        const Gloop::Shader vertexShader = sf.createShaderFromString(GL_VERTEX_SHADER, getVertexShaderCode());
        const Gloop::Shader fragmentShader = sf.createShaderFromString(GL_FRAGMENT_SHADER, getFragmentShaderCode());

        // Link program
        program.attachShader(vertexShader);
        program.attachShader(fragmentShader);
        program.link();
        if (!program.linked()) {
            throw std::runtime_error("Could not link program!");
        }

        // Create buffer layout
        const Glycerin::BufferLayout layout = Glycerin::BufferLayoutBuilder()
                .count(6)
                .components(2)
                .region("MCVertex")
                .region("TexCoord0")
                .build();

        // Create and bind VBO
        const Gloop::BufferObject vbo = Gloop::BufferObject::generate();
        const Gloop::BufferTarget arrayBuffer = Gloop::BufferTarget::arrayBuffer();
        arrayBuffer.bind(vbo);

        // Allocate buffer
        arrayBuffer.data(layout.sizeInBytes(), NULL, GL_STATIC_DRAW);

        // Specify points
        const GLfloat points[] = {
                +0.5f, +0.5f,
                -0.5f, +0.5f,
                -0.5f, -0.5f,
                -0.5f, -0.5f,
                +0.5f, -0.5f,
                +0.5f, +0.5f };
        const Glycerin::BufferRegion r1 = *(layout.find("MCVertex"));
        arrayBuffer.subData(r1.offset(), r1.sizeInBytes(), points);

        // Specify coordinates
        const GLfloat coords[] = {
                1.0f, 1.0f,
                0.0f, 1.0f,
                0.0f, 0.0f,
                0.0f, 0.0f,
                1.0f, 0.0f,
                1.0f, 1.0f };
        const Glycerin::BufferRegion r2 = *(layout.find("TexCoord0"));
        arrayBuffer.subData(r2.offset(), r2.sizeInBytes(), coords);

        // Enable attributes
        vao.bind();
        for (Glycerin::BufferLayout::const_iterator it = layout.begin(); it != layout.end(); ++it) {
            const GLint idx = program.attribLocation(it->name());
            vao.enableVertexAttribArray(idx);
            vao.vertexAttribPointer(Gloop::VertexAttribPointer()
                    .index(idx)
                    .offset(it->offset())
                    .size(it->components()));
        }

        // Load bitmap as texture
        Glycerin::BitmapReader reader;
        const Glycerin::Bitmap bitmap = reader.read("glycerin/crate.bmp");
        bitmap.createTexture();
    }

    /**
     * Ensures `Bitmap::createTexture` works correctly.
     */
    void testCreateTexture() {
        program.use();
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glfwSwapBuffers();
        sleep(SLEEP_TIME_IN_SECONDS);
    }
};

int main(int argc, char* argv[]) {

    // Capture working directory before GLFW changes it
#ifdef __APPLE__
    char* const cwd = new char[PATH_MAX];
    if (!getcwd(cwd, PATH_MAX)) {
        throw std::runtime_error("Could not get current working directory!");
    }
#endif

    // Initialize GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Could not initialize GLFW!");
    }

#ifdef __APPLE__
    chdir(cwd);
    delete[] cwd;
#endif

    // Open window
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (!glfwOpenWindow(512, 512, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)) {
        throw std::runtime_error("Could not open GLFW window!");
    }

    // Run test
    try {
        BitmapTest test;
        test.testCreateTexture();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

    // Exit
    glfwTerminate();
    return 0;
}
