cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)

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


project(r-type_server)

include_directories(Server/ Server/src/)
file(GLOB_RECURSE SERVER_SOURCES Server/src/*.cpp)
file(GLOB_RECURSE SERVER_HEADERS Server/src/*.hpp)

add_executable(r-type_server ${SERVER_HEADERS} ${SERVER_SOURCES})


project(r-type_client)

include_directories(Client/ Client/assets/ Client/src/ Client/src/GameStatus)
file(GLOB_RECURSE CLIENT_SOURCES Client/src/*.cpp)
file(GLOB_RECURSE CLIENT_HEADERS Client/src/*.hpp)

add_executable(r-type_client ${CLIENT_HEADERS} ${CLIENT_SOURCES})
target_link_libraries(r-type_client raylib)
add_custom_command(
        TARGET r-type_client
        POST_BUILD COMMAND ${CMAKE_COMMAND}
        -E create_symlink ${CMAKE_SOURCE_DIR}/Client/assets
        ${CMAKE_BINARY_DIR}/assets
)