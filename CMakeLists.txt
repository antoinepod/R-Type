cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)
project(r-type)

include(cmake/Findraylib.cmake)

if(WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}/build>)
endif()

file(GLOB_RECURSE HEADERS src/*.hpp)
file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(r-type ${HEADERS} ${SOURCES})

target_link_libraries(r-type raylib)