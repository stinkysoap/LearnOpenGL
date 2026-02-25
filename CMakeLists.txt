cmake_minimum_required(VERSION 3.16)
project(LearnOpenGL LANGUAGES C CXX)
if(WIN32)
    message(STATUS "Building on Windows")

    if(MSVC)
        message(STATUS "Compiler: MSVC")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        message(STATUS "Compiler: Clang")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        message(STATUS "Compiler: MinGW/GCC")
    else()
        message(WARNING "Unknown Windows compiler: ${CMAKE_CXX_COMPILER_ID}")
    endif()
endif()
set(CMAKE_CXX_STANDARD 14)

# GLAD
set(GLAD_DIR "${CMAKE_SOURCE_DIR}/glad")
add_library(glad "${GLAD_DIR}/src/glad.c")
target_include_directories(glad PUBLIC "${GLAD_DIR}/include")

# Source files
file(GLOB_RECURSE SRC_FILES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_executable(LearnOpenGL ${SRC_FILES})

target_include_directories(LearnOpenGL PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Dependencies
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(LearnOpenGL
    PRIVATE
    glad
    glfw
    OpenGL::GL
)
