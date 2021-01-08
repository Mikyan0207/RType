cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)
project(RType)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

option(SERVER "Build project for server" OFF)
option(GAME "Build project for client" OFF)
option(TESTS "Build test project" OFF)

add_subdirectory(RType.Common)

if (SERVER)
    add_subdirectory(RType.Server)
    add_subdirectory(RType.Entities)
endif()

if (GAME)
    add_subdirectory(RType.Game)
endif()

if(TESTS)
    add_subdirectory(RType.Tests)
endif()