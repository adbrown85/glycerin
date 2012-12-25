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
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "glycerin/ShaderFactory.hxx"
using namespace std;
namespace Glycerin {

/**
 * Constructs a shader factory.
 */
ShaderFactory::ShaderFactory() {
    // pass
}

/**
 * Creates a shader from a file.
 *
 * @param type Kind of shader, e.g. `GL_VERTEX_SHADER` or `GL_FRAGMENT_SHADER`
 * @param filename Path to the file containing shader's source code
 * @return OpenGL handle to the shader
 * @throws std::invalid_argument if filename is empty
 */
Gloop::Shader ShaderFactory::createShaderFromFile(const GLenum type, const string& filename) {

    // Make a stream from the file
    ifstream fs(filename.c_str());
    if (!fs) {
        throw invalid_argument("[ShaderFactory] Could not open file!");
    }

    // Make the shader from the stream
    return createShaderFromStream(type, fs);
}

/**
 * Creates a shader from a stream.
 *
 * @param type Kind of shader, e.g. `GL_VERTEX_SHADER` or `GL_FRAGMENT_SHADER`
 * @param stream Stream containing shader's source code
 * @return OpenGL handle to the shader
 */
Gloop::Shader ShaderFactory::createShaderFromStream(const GLenum type, istream& stream) {

    // Make a string from the stream
    stringstream ss;
    string line;
    getline(stream, line);
    while (stream) {
        ss << line << '\n';
        getline(stream, line);
    }

    // Make the shader from the string
    return createShaderFromString(type, ss.str());
}

/**
 * Creates a shader from a string.
 *
 * @param type Kind of shader, e.g. `GL_VERTEX_SHADER` or `GL_FRAGMENT_SHADER`
 * @param str String containing shader's source code
 * @return OpenGL handle to the shader
 * @throws runtime_error if could not create or compile shader
 */
Gloop::Shader ShaderFactory::createShaderFromString(const GLenum type, const string& str) {

    // Create the shader
    const Gloop::Shader shader = Gloop::Shader::create(type);

    // Load the source
    shader.source(str);

    // Compile
    shader.compile();
    if (!shader.compiled()) {
        const string log = shader.log();
        throw runtime_error(log);
    }

    // Return the shader
    return shader;
}

} /* namespace Glycerin */
