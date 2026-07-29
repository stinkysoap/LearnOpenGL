#include "shader_utils.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace shader_utils {

std::string read_file(const std::string& asset_path) {
    std::ifstream input(asset_path);
    if (!input.is_open()) {
        std::cerr << "Failed to open shader file: " << asset_path << '\n';
        return "";
    }

    std::ostringstream buffer;
    buffer << input.rdbuf();
    return buffer.str();
}

std::string resolve_asset_path(const std::string& asset_path) {
    if (asset_path.empty()) {
        return asset_path;
    }

#if defined(LEARNOPENGL_SOURCE_DIR)
    if (asset_path[0] == '/' || asset_path[0] == '\\') {
        return asset_path;
    }

    return std::string(LEARNOPENGL_SOURCE_DIR) + "/" + asset_path;
#else
    return asset_path;
#endif
}

static GLuint compile_shader(GLenum shader_type, const std::string& shader_path,
                             const std::string& shader_source) {
    if (shader_source.empty()) {
        std::cerr << "Shader source is empty: " << shader_path << '\n';
        return 0;
    }

    const GLuint shader = glCreateShader(shader_type);
    const GLchar* source = shader_source.c_str();
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint compile_status = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE) {
        GLint log_length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

        std::vector<GLchar> error(log_length > 0 ? static_cast<size_t>(log_length) : 1);
        glGetShaderInfoLog(shader, log_length, nullptr, error.data());
        std::cerr << "Failed to compile shader " << shader_path << ":\n"
                  << error.data() << '\n';

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint create_program_from_files(const std::string& vertex_shader_path,
                                 const std::string& fragment_shader_path) {
    const std::string resolved_vertex_path = resolve_asset_path(vertex_shader_path);
    const std::string resolved_fragment_path = resolve_asset_path(fragment_shader_path);

    const std::string vertex_source = read_file(resolved_vertex_path);
    const std::string fragment_source = read_file(resolved_fragment_path);

    const GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, resolved_vertex_path, vertex_source);
    if (vertex_shader == 0) {
        return 0;
    }

    const GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, resolved_fragment_path, fragment_source);
    if (fragment_shader == 0) {
        glDeleteShader(vertex_shader);
        return 0;
    }

    const GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    GLint link_status = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &link_status);
    if (link_status == GL_FALSE) {
        GLint log_length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);

        std::vector<GLchar> error(log_length > 0 ? static_cast<size_t>(log_length) : 1);
        glGetProgramInfoLog(program, log_length, nullptr, error.data());
        std::cerr << "Failed to link shader program from files:\n" << error.data() << '\n';

        glDeleteProgram(program);
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        return 0;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return program;
}

}  // namespace shader_utils
