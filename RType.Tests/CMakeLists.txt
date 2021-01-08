cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)
project(RTypeTests)

include_directories(
    ${CMAKE_SOURCE_DIR}/RType.Common/Headers
    ${PROJECT_SOURCE_DIR}/
    ${CONAN_INCLUDE_DIRS_BOOST}
    ${CONAN_INCLUDE_DIRS_SFML}
    ${CONAN_INCLUDE_DIRS_PROTOBUF}
    "C:/Program Files (x86)/Microsoft Visual Studio/2017/Enterprise/VC/Auxiliary/VS/UnitTest/include"
)

link_directories(
    ${CMAKE_SOURCE_DIR}/lib
    "C:/Program Files (x86)/Microsoft Visual Studio/2017/Enterprise/VC/Auxiliary/VS/UnitTest/lib/x86/Microsoft.VisualStudio.TestTools.CppUnitTestFramework.lib"
)

set(HEADER_FILES ${PROJECT_SOURCE_DIR}/pch.h)

set(SOURCES_FILES
    ${PROJECT_SOURCE_DIR}/pch.cpp

    ${PROJECT_SOURCE_DIR}/Components/ButtonTests.cpp
    ${PROJECT_SOURCE_DIR}/Components/DrawableTests.cpp
    ${PROJECT_SOURCE_DIR}/Components/TextTests.cpp
    ${PROJECT_SOURCE_DIR}/Components/TransformTests.cpp

    ${PROJECT_SOURCE_DIR}/Entities/EntityTests.cpp

    ${PROJECT_SOURCE_DIR}/Monsters/MonstersTests.cpp

    ${PROJECT_SOURCE_DIR}/Systems/ButtonSystemTests.cpp
)

add_definitions(-DWIN32_LEAN_AND_MEAN -DRTYPECOMMON_INHERITANCE -D_WIN32 -D_WIN32_WINNT=0x0A00)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADERS_FILES})

add_library(${PROJECT_NAME} SHARED ${SOURCES_FILES} ${HEADER_FILES})
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS} RTypeCommon)