# CMakeLists.txt
cmake_minimum_required(VERSION 3.19)


# Projects
project(r-type_server)
project(r-type_client)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)
add_definitions(-D_WIN32_WINNT=0x0601)

# Conan
set(CONAN_DISABLE_CHECK_COMPILER True CACHE BOOL "" FORCE)
find_program(conan_path conan)
message(${conan_path})
if (WIN32)
    execute_process(COMMAND ${conan_path} "install" "${CMAKE_CURRENT_SOURCE_DIR}" "-s" "compiler=Visual Studio" "-s" "compiler.version=16" "-s" "build_type=Debug" WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
else()
    execute_process(COMMAND ${conan_path} "install" "${CMAKE_CURRENT_SOURCE_DIR}" "--build=missing" "-c" "tools.system.package_manager:mode=install" "-c" "tools.system.package_manager:sudo=True")
endif()
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

# R-Type Server
file(GLOB_RECURSE SERVER_SOURCES Server/src/*.cpp Network/*.cpp)
file(GLOB_RECURSE SERVER_HEADERS Server/src/*.hpp Network/*.hpp)
add_executable(r-type_server ${SERVER_HEADERS} ${SERVER_SOURCES})
target_link_libraries(r-type_server CONAN_PKG::boost)

# R-Type Client
include_directories(${CMAKE_INCLUDE_PATH} Client/ Client/assets/ Client/src/
        Client/src/GameStatus Network/ Network/Data)
file(GLOB_RECURSE CLIENT_SOURCES Client/src/*.cpp Network/*.cpp)
file(GLOB_RECURSE CLIENT_HEADERS Client/src/*.hpp Network/*.hpp)
add_executable(r-type_client ${CLIENT_HEADERS} ${CLIENT_SOURCES})
target_link_libraries(r-type_client CONAN_PKG::boost)

if (WIN32)
    include(FetchContent)
    set(BUILD_SHARED_LIBS OFF)
    FetchContent_Declare(
            SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.5.1
    )
    FetchContent_MakeAvailable(SFML)
endif()

target_link_libraries(r-type_client sfml-graphics)
target_link_libraries(r-type_client sfml-window)
target_link_libraries(r-type_client sfml-audio)
target_link_libraries(r-type_client sfml-network)
target_link_libraries(r-type_client sfml-system)

## Assets
add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/Client/assets
        ${CMAKE_BINARY_DIR}/bin/assets
        COMMENT "Copying assets into binary directory"
        )
add_dependencies(r-type_client copy_resources)