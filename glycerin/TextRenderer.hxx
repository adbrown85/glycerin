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
#ifndef GLYCERIN_TEXT_RENDERER_HXX
#define GLYCERIN_TEXT_RENDERER_HXX
#include <string>
#include <vector>
#include <gloop/BufferObject.hxx>
#include <gloop/BufferTarget.hxx>
#include <gloop/Program.hxx>
#include <gloop/TextureObject.hxx>
#include <gloop/TextureTarget.hxx>
#include <gloop/TextureUnit.hxx>
#include <gloop/VertexArrayObject.hxx>
#include <gloop/VertexAttribPointer.hxx>
#include <m3d/Mat4.h>
#include "glycerin/common.h"
#include "glycerin/Bitmap.hxx"
#include "glycerin/BitmapReader.hxx"
#include "glycerin/BufferLayout.hxx"
#include "glycerin/BufferLayoutBuilder.hxx"
#include "glycerin/Projection.hxx"
#include "glycerin/ShaderFactory.hxx"
namespace Glycerin {


/**
 * Utility for rendering text.
 */
class TextRenderer {
public:
// Methods
    TextRenderer();
    void beginRendering(GLsizei width, GLsizei height);
    void draw(const std::string& text, GLfloat x, GLfloat y);
    void endRendering();
private:
// Constants
    static const std::vector<std::string> RESOURCE_DIRECTORIES;
    static const std::string VERTEX_SHADER_FILENAME;
    static const std::string FRAGMENT_SHADER_FILENAME;
    static const std::string FONT_FILENAME;
    static const char FIRST_CHARACTER = ' ';
    static const GLint NUMBER_OF_CHARACTERS = 95; 
    static const GLfloat CHARACTER_WIDTH = 16;
    static const GLfloat CHARACTER_HEIGHT = 28;
    static const GLfloat DELTA_S = 1.0f / NUMBER_OF_CHARACTERS;
    static const GLfloat DESCENT = 6;
// Attributes
    const Gloop::BufferObject bufferObject;
    const Gloop::BufferTarget arrayBuffer;
    const Gloop::Program program;
    const Gloop::TextureObject textureObject;
    const Gloop::TextureUnit textureUnit;
    const Gloop::TextureTarget textureTarget;
    const Gloop::VertexArrayObject vertexArrayObject;
// Methods
    static Gloop::Program createProgram();
    static std::vector<std::string> createResourceDirectories();
    static Gloop::TextureObject createTextureObject();
    static bool exists(const std::string& path);
    static std::string getResource(const std::string& name);
};

} /* namespace Glycerin */
#endif
