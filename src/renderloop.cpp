#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <string>

#include "shader_utils.h"

void render_loop() {
  float vertices[] = {-0.5f, -.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  const std::string vertex_path =
      std::string(LEARNOPENGL_SOURCE_DIR) + "/src/vertex_shader.glsl";
  const std::string fragment_path =
      std::string(LEARNOPENGL_SOURCE_DIR) + "/src/fragment_shader.glsl";

  GLuint vertexShader = create_shader_from_file(vertex_path, GL_VERTEX_SHADER);
  GLuint fragmentShader =
      create_shader_from_file(fragment_path, GL_FRAGMENT_SHADER);

  GLuint shader_program;
  shader_program = glCreateProgram();
  glAttachShader(shader_program, vertexShader);
  glAttachShader(shader_program, fragmentShader);
  glLinkProgram(shader_program);

  glUseProgram(shader_program);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
}
