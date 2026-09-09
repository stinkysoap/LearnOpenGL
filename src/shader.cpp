#include "shader.hpp"
#include <fstream>
#include <sstream>

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;
  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::failbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    std::stringstream vShaderStream, fShaderStream;
    // read file's buffer contents into the streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    // close file handlers
    vShaderFile.close();
    fShaderFile.close();

    // convert Stream Into String
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();

  } catch (std::ifstream::failure e) {
    std::cout << "Error::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
  }
  const char *vShaderCode = vertexCode.c_str();
  const char *fShaderCode = fragmentCode.c_str();
  // 2.Compile Shaders
  GLuint vertex, fragment;
  int success;
  char infolog[512];

  // vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infolog);
    std::cout << "ERRROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infolog << std::endl;
  };
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &vShaderCode, NULL);
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, infolog);
    std::cout << "ERRROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infolog << std::endl;
  };
  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);
  // print linking errors if any
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(ID, 512, NULL, infolog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infolog << std::endl;
  }

  // delete the shaders as they're linked into our program now and no longer
  // necessary
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}
void Shader::use() { glUseProgram(ID); }
void Shader::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
