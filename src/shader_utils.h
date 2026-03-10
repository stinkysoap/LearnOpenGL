#ifndef SHADER_UTILS_H
#define SHADER_UTILS_H

#include <string>

#include <glad/glad.h>

// Loads a text file (e.g. GLSL source) into a std::string.
// Throws std::runtime_error on failure.
std::string load_shader_source(const std::string &file_path);

// Creates and compiles an OpenGL shader from a GLSL source file.
// On success returns a valid shader object handle.
// On failure prints the compile log to std::cerr and returns 0.
GLuint create_shader_from_file(const std::string &file_path, GLenum shader_type);

#endif  // SHADER_UTILS_H

