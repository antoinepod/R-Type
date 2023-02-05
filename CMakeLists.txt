# CMakeLists.txt
cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)

# Windows
if(WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}/build>)
endif()

# Projects
project(r-type_server)
project(r-type_client)

# Conan
find_program(conan_path conan)
message(${conan_path})
execute_process(COMMAND ${conan_path} "install" ".." " --build=missing" "-c" "tools.system.package_manager:mode=install" "-c" "tools.system.package_manager:sudo=True")
include(build/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

# R-Type Server
include_directories(${CMAKE_INCLUDE_PATH} Server/ Server/src/)
file(GLOB_RECURSE SERVER_SOURCES Server/src/*.cpp)
file(GLOB_RECURSE SERVER_HEADERS Server/src/*.hpp)
add_executable(r-type_server ${SERVER_HEADERS} ${SERVER_SOURCES})
target_link_libraries(r-type_server CONAN_PKG::boost)

# R-Type Client
include_directories(${CMAKE_INCLUDE_PATH} Client/ Client/assets/ Client/src/ Client/src/GameStatus)
file(GLOB_RECURSE CLIENT_SOURCES Client/src/*.cpp)
file(GLOB_RECURSE CLIENT_HEADERS Client/src/*.hpp)
add_executable(r-type_client ${CLIENT_HEADERS} ${CLIENT_SOURCES})
target_link_libraries(r-type_client sfml-graphics sfml-window sfml-audio sfml-system)
target_link_libraries(r-type_client CONAN_PKG::boost)

# Assets
add_custom_command(
        TARGET r-type_client
        POST_BUILD COMMAND ${CMAKE_COMMAND}
        -E create_symlink ${CMAKE_SOURCE_DIR}/Client/assets
        ${CMAKE_BINARY_DIR}/assets
)