cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)
project(RTypeGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_SUPPRESS_REGENERATION true)

include_directories(${CMAKE_SOURCE_DIR}/RType.Common/Headers ${PROJECT_SOURCE_DIR}/Headers)
link_directories(${CMAKE_SOURCE_DIR}/lib)

set(HEADERS_FILES
    ${PROJECT_SOURCE_DIR}/Headers/Application.hpp
    ${PROJECT_SOURCE_DIR}/Headers/PacketManager.hpp
    ${PROJECT_SOURCE_DIR}/Headers/TCPClient.hpp

    ${PROJECT_SOURCE_DIR}/Headers/UDPClient.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Scenes/MainScreen.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Scenes/LobbyScreen.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Scenes/JoinLobbyScreen.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Scenes/GameScreen.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Scenes/EndScreen.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Scenes/OptionsScreen.hpp
)

set(SOURCES_FILES
    ${PROJECT_SOURCE_DIR}/Sources/Application.cpp
    ${PROJECT_SOURCE_DIR}/Sources/PacketManager.cpp
    ${PROJECT_SOURCE_DIR}/Sources/TCPClient.cpp
    ${PROJECT_SOURCE_DIR}/Sources/UDPClient.cpp
    ${PROJECT_SOURCE_DIR}/Sources/main.cpp

    ${PROJECT_SOURCE_DIR}/Sources/Scenes/MainScreen.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Scenes/LobbyScreen.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Scenes/JoinLobbyScreen.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Scenes/GameScreen.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Scenes/EndScreen.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Scenes/OptionsScreen.cpp
)

if(WIN32)
    add_definitions(-DWIN32_LEAN_AND_MEAN -DRTYPECOMMON_INHERITANCE -D_WIN32 -D_WIN32_WINNT=0x0A00)
endif(WIN32)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADERS_FILES})

add_executable(${PROJECT_NAME} ${SOURCES_FILES} ${HEADERS_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CONAN_INCLUDE_DIRS_BOOST} ${CONAN_INCLUDE_DIRS_SFML} ${CONAN_INCLUDE_DIRS_PROTOBUF})
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS} RTypeCommon)
