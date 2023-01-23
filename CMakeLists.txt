cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)
project(r-type)

include(cmake/Findraylib.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include_directories(assets/ includes/ includes/Encapsulation includes/Network src/
        src/GameStatus)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(r-type ${HEADERS} ${SOURCES})

target_link_libraries(r-type raylib)

add_custom_command(
        TARGET r-type
        POST_BUILD COMMAND ${CMAKE_COMMAND}
        -E create_symlink ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets
)