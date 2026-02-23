cmake_minimum_required(VERSION 3.16)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC_FILES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

add_executable(untitled ${SRC_FILES})

include_directories("${CMAKE_SOURCE_DIR}/include")

link_directories("${CMAKE_SOURCE_DIR}/lib")

file(GLOB PROJECT_LIBS
    "${CMAKE_SOURCE_DIR}/lib/*.a"
    "${CMAKE_SOURCE_DIR}/lib/*.dylib"
)

target_link_libraries(untitled PRIVATE ${PROJECT_LIBS})