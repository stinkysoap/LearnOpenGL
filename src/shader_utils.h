#pragma once

#include <glad/glad.h>

#include <string>

namespace shader_utils {

std::string read_file(const std::string& asset_path);
std::string resolve_asset_path(const std::string& asset_path);
GLuint create_program_from_files(const std::string& vertex_shader_path,
                                 const std::string& fragment_shader_path);

}  // namespace shader_utils
