#include "shader_utils.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

std::string load_shader_source(const std::string &file_path) {
  std::ifstream file(file_path);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open shader file: " + file_path);
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

GLuint create_shader_from_file(const std::string &file_path,
                               GLenum shader_type) {
  std::string source;
  try {
    source = load_shader_source(file_path);
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 0;
  }

  const char *src_ptr = source.c_str();
  GLuint shader = glCreateShader(shader_type);
  glShaderSource(shader, 1, &src_ptr, nullptr);
  glCompileShader(shader);

  GLint success = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char info_log[512];
    glGetShaderInfoLog(shader, sizeof(info_log), nullptr, info_log);
    std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n"
              << "File: " << file_path << "\n"
              << info_log << std::endl;
    glDeleteShader(shader);
    return 0;
  }

  return shader;
}

