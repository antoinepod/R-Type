# CMakeLists.txt
cmake_minimum_required(VERSION 3.24.2)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})


# VCPKG
if (WIN32)
    execute_process(COMMAND ${CMAKE_SOURCE_DIR}/vcpkg/bootstrap-vcpkg.bat)
    execute_process(COMMAND ${CMAKE_SOURCE_DIR}/vcpkg/vcpkg "--feature-flags=manifests" "install" "--triplet" "x64-windows-static")
    set(Boost_INCLUDE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-windows-static/include)
else()
    execute_process(COMMAND ${CMAKE_SOURCE_DIR}/vcpkg/bootstrap-vcpkg.sh)
    execute_process(COMMAND ${CMAKE_SOURCE_DIR}/vcpkg/vcpkg "--feature-flags=manifests" "install" "--triplet" "x64-linux")
    set(Boost_INCLUDE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-linux/include)
    #list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-linux/lib)
endif()

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")


# Projects
project(r-type_client)
project(r-type_server)


# SFML (vcpkg)
find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)

# Boost (vcpkg)
find_package(Boost REQUIRED)


# R-Type Server
include_directories(${CMAKE_INCLUDE_PATH} Server/ Server/src/ Network/ Network/Data ${Boost_INCLUDE_DIR})
file(GLOB_RECURSE SERVER_SOURCES Server/src/*.cpp Network/*.cpp)
file(GLOB_RECURSE SERVER_HEADERS Server/src/*.hpp Network/*.hpp)
add_executable(r-type_server ${SERVER_HEADERS} ${SERVER_SOURCES})

# R-Type Client
file(GLOB_RECURSE CLIENT_SOURCES Client/src/*.cpp Network/*.cpp)
file(GLOB_RECURSE CLIENT_HEADERS Client/src/*.hpp Network/*.hpp)
include_directories(${CMAKE_INCLUDE_PATH} Client/ Client/assets/ Client/src/ Client/src/GameStatus Network/ Network/Data)
add_executable(r-type_client ${CLIENT_HEADERS} ${CLIENT_SOURCES})

# Linking
target_link_libraries(r-type_client PRIVATE sfml-system sfml-graphics sfml-window sfml-audio)
target_link_libraries(r-type_client PRIVATE ${Boost_LIBRARIES})
target_link_libraries(r-type_server PRIVATE ${Boost_LIBRARIES})


## Assets
add_custom_command(
        TARGET r-type_client
        POST_BUILD COMMAND ${CMAKE_COMMAND}
        -E create_symlink ${CMAKE_SOURCE_DIR}/Client/assets ${CMAKE_BINARY_DIR}/assets
)