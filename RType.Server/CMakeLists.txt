cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)
project(RTypeServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_SUPPRESS_REGENERATION true)

include_directories(${CMAKE_SOURCE_DIR}/RType.Common/Headers ${PROJECT_SOURCE_DIR}/Headers)
link_directories(${CMAKE_SOURCE_DIR}/lib)

set(HEADERS_FILES
    ${PROJECT_SOURCE_DIR}/Headers/UDPServer.hpp
    ${PROJECT_SOURCE_DIR}/Headers/IGameInstance.hpp
    ${PROJECT_SOURCE_DIR}/Headers/GameInstance.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Lobby.hpp
    ${PROJECT_SOURCE_DIR}/Headers/PacketManager.hpp
    ${PROJECT_SOURCE_DIR}/Headers/TCPServer.hpp
    ${PROJECT_SOURCE_DIR}/Headers/ServerScene.hpp
    ${PROJECT_SOURCE_DIR}/Headers/ServApp.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Parser/PowerType.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Parser/LevelInformation.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Parser/Parser.hpp
)

set(SOURCES_FILES
    ${PROJECT_SOURCE_DIR}/Sources/UDPServer.cpp
    ${PROJECT_SOURCE_DIR}/Sources/GameInstance.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Lobby.cpp
    ${PROJECT_SOURCE_DIR}/Sources/PacketManager.cpp
    ${PROJECT_SOURCE_DIR}/Sources/TCPServer.cpp
    ${PROJECT_SOURCE_DIR}/Sources/ServApp.cpp
    ${PROJECT_SOURCE_DIR}/Sources/ServerScene.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Parser/Parser.cpp
    ${PROJECT_SOURCE_DIR}/Sources/main.cpp
)

if(WIN32)
    add_definitions(-DWIN32_LEAN_AND_MEAN -DRTYPECOMMON_INHERITANCE -D_WIN32 -D_WIN32_WINNT=0x0A00)
endif()

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADERS_FILES})

add_executable(${PROJECT_NAME} ${SOURCES_FILES} ${HEADERS_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CONAN_INCLUDE_DIRS_BOOST} ${CONAN_INCLUDE_DIRS_SFML} ${CONAN_INCLUDE_DIRS_PROTOBUF})
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS} RTypeCommon)
