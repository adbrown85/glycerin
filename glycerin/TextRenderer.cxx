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
#include <stdexcept>
#include "glycerin/TextRenderer.hxx"
namespace Glycerin {

// Directories to look for resources in
const std::vector<std::string> TextRenderer::RESOURCE_DIRECTORIES = createResourceDirectories();

// Image with font's glyphs
const std::string TextRenderer::FONT_FILENAME("monospaced-24.bmp");

// Vertex shader used to render the text
const std::string TextRenderer::VERTEX_SHADER_FILENAME("text-renderer.vert");

// Fragment shader used to render the text
const std::string TextRenderer::FRAGMENT_SHADER_FILENAME("text-renderer.frag");

/**
 * Constructs a `TextRenderer`.
 */
TextRenderer::TextRenderer() :
        bufferObject(Gloop::BufferObject::generate()),
        arrayBuffer(Gloop::BufferTarget::arrayBuffer()),
        program(createProgram()),
        textureObject(createTextureObject()),
        textureTarget(Gloop::TextureTarget::texture2d()),
        textureUnit(Gloop::TextureUnit::fromEnum(GL_TEXTURE0)),
        vertexArrayObject(Gloop::VertexArrayObject::generate()) {

    // Bind
    vertexArrayObject.bind();
    arrayBuffer.bind(bufferObject);

    // Fill buffer
    const BufferLayout layout = BufferLayoutBuilder()
        .count(6)
        .components(2)
        .interleaved(true)
        .region("MCVertex")
        .region("TexCoord0")
        .build();
    arrayBuffer.data(layout.sizeInBytes(), NULL, GL_STREAM_DRAW);

    // Set up pointers
    for (BufferLayout::const_iterator it = layout.begin(); it != layout.end(); ++it) {
        const GLint location = program.attribLocation(it->name());
        vertexArrayObject.enableVertexAttribArray(location);
        vertexArrayObject.vertexAttribPointer(Gloop::VertexAttribPointer()
                .index(location)
                .size(it->components())
                .stride(it->stride())
                .offset(it->offset()));
    }

    // Unbind
    arrayBuffer.unbind(bufferObject);
    vertexArrayObject.unbind();
}

/**
 * Starts rendering.
 *
 * @param width Width of the viewport
 * @param height Height of the viewport
 */
void TextRenderer::beginRendering(const GLsizei width, const GLsizei height) {

    // Enable blending
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    // Bind texture
    textureUnit.activate();
    textureTarget.bind(textureObject);

    // Use program
    program.use();

    // Set transformation matrix
    const M3d::Mat4 mat = Projection::orthographic(width, height);
    GLfloat arr[16];
    mat.toArrayInColumnMajor(arr);
    const GLint location = program.uniformLocation("MVPMatrix");
    glUniformMatrix4fv(location, 1, false, arr);

    // Bind VAO and VBO
    vertexArrayObject.bind();
    arrayBuffer.bind(bufferObject);
}

/**
 * Creates the shader program used to render the text.
 *
 * @return Shader program used to render the text
 */
Gloop::Program TextRenderer::createProgram() {

    // Create shaders
    ShaderFactory shaderFactory;
    const Gloop::Shader vertexShader = shaderFactory.createShaderFromFile(
            GL_VERTEX_SHADER, getResource(VERTEX_SHADER_FILENAME));
    const Gloop::Shader fragmentShader = shaderFactory.createShaderFromFile(
            GL_FRAGMENT_SHADER, getResource(FRAGMENT_SHADER_FILENAME));

    // Create programs and attach shaders
    const Gloop::Program program = Gloop::Program::create();
    program.attachShader(vertexShader);
    program.attachShader(fragmentShader);

    // Link program
    program.link();
    if (!program.linked()) {
        throw std::runtime_error(program.log());
    }

    // Return program
    return program;
}

/**
 * Creates the list of directories to look for resources in.
 *
 * @return List of directories to look for resources in
 */
std::vector<std::string> TextRenderer::createResourceDirectories() {
    std::vector<std::string> directories;
    directories.push_back(PACKAGE_TARNAME);
    directories.push_back(DATA_DIR "/" PACKAGE_TARNAME "-" PACKAGE_MAJOR_VERSION_AS_STRING);
    return directories;
}

/**
 * Creates the texture holding the font's glyphs.
 *
 * @return Handle to the texture holding the font's glyphs
 */
Gloop::TextureObject TextRenderer::createTextureObject() {

    // Read the bitmap into a texture
    BitmapReader reader;
    const Bitmap bitmap = reader.read(getResource(FONT_FILENAME));
    const Gloop::TextureObject textureObject = bitmap.createTexture(false);

    // Set the filtering
    const Gloop::TextureTarget texture2d = Gloop::TextureTarget::texture2d();
    texture2d.bind(textureObject);
    texture2d.minFilter(GL_LINEAR);
    texture2d.magFilter(GL_LINEAR);

    // Return the texture
    return textureObject;
}

/**
 * Draws a string of text.
 *
 * @param text Text to draw
 * @param x Location on X axis to draw text
 * @param y Location on Y axis to draw baseline of text
 */
void TextRenderer::draw(const std::string& text, GLfloat x, const GLfloat y) {

    // Calculate Y positions and texture coordinates
    const GLfloat y1 = y - DESCENT;
    const GLfloat y2 = y1 + CHARACTER_HEIGHT;
    const GLfloat t1 = 0.0f;
    const GLfloat t2 = 1.0f;

    for (std::string::const_iterator it = text.begin(); it != text.end(); ++it) {

        // Determine index in texture
        const int i = (*it) - FIRST_CHARACTER;

        // Calculate X positions and texture coordinates
        const GLfloat x1 = x;
        const GLfloat x2 = x + CHARACTER_WIDTH;
        const GLfloat s1 = DELTA_S * i;
        const GLfloat s2 = s1 + DELTA_S;

        // Draw rectangle
        const GLfloat data[] = {
            x2, y2,
            s2, t2,
            x1, y2,
            s1, t2,
            x1, y1,
            s1, t1,
            x1, y1,
            s1, t1,
            x2, y1,
            s2, t1,
            x2, y2,
            s2, t2
        };
        arrayBuffer.subData(0, sizeof(data), data);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Advance cursor
        x += CHARACTER_WIDTH;
    }
}

/**
 * Finishes rendering.
 */
void TextRenderer::endRendering() {
    textureTarget.unbind();
    glUseProgram(0);
    vertexArrayObject.unbind();
    arrayBuffer.unbind(bufferObject);
}

/**
 * Checks if a file exists.
 *
 * @param path Path of the file to check for
 * @return `true` if file exists
 */
bool TextRenderer::exists(const std::string& path) {
    std::ifstream file(path.c_str());
    return file;
}

/**
 * Finds a resource in one of the resource directories.
 *
 * @param name Name of the resource to find
 * @throws std::invalid_argument if name of resource is empty
 * @throws std::runtime_error if could not find resource
 */
std::string TextRenderer::getResource(const std::string& name) {

    // Check argument
    if (name.empty()) {
        throw std::invalid_argument("[TextRenderer] Name of resource is empty");
    }

    // Look for resource in each directory
    for (int i = 0; i < RESOURCE_DIRECTORIES.size(); ++i) {
        const std::string path = RESOURCE_DIRECTORIES[i] + '/' + name;
        if (exists(path)) {
            return path;
        }
    }

    // Not found
    throw std::runtime_error("[TextRenderer] Could not find resource!");
}

}
