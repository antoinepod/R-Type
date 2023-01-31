cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)
project(r-type)

if (NOT raylib_FOUND)
    INCLUDE(FetchContent)
    FetchContent_Declare(raylib URL https://github.com/raysan5/raylib/archive/refs/tags/4.0.0.tar.gz)
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        SET(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        SET(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        ADD_SUBDIRECTORY(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
        SET(raylib_FOUND TRUE)
    endif()
endif()

if(WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}/build>)
endif()

include_directories(Client/ Client/assets/ Client/src/ Client/src/GameStatus)

file(GLOB_RECURSE SOURCES Client/src/*.cpp)

add_executable(r-type ${HEADERS} ${SOURCES})

target_link_libraries(r-type raylib)

add_custom_command(
        TARGET r-type
        POST_BUILD COMMAND ${CMAKE_COMMAND}
        -E create_symlink ${CMAKE_SOURCE_DIR}/Client/assets
        ${CMAKE_BINARY_DIR}/assets
)