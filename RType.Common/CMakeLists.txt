cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)
project(RTypeCommon)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_SUPPRESS_REGENERATION true)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(${PROJECT_SOURCE_DIR}/Headers)

set(HEADERS_FILES
    ${PROJECT_SOURCE_DIR}/Headers/RType.Common.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Core.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Logger.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Helper.hpp

    ${PROJECT_SOURCE_DIR}/Headers/Models/RTypePack.pb.h
    ${PROJECT_SOURCE_DIR}/Headers/Models/RGamePack.pb.h

    ${PROJECT_SOURCE_DIR}/Headers/Components/Component.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Components/Button.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Components/Text.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Components/Sprite.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Components/Parallax.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Components/IComponent.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Components/TextInput.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Components/Input.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Components/DynamicButton.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Components/Monster.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Components/Drawable.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Components/Transform.hpp

    ${PROJECT_SOURCE_DIR}/Headers/Entities/IEntity.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Entities/Entity.hpp

    ${PROJECT_SOURCE_DIR}/Headers/Managers/GameManager.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Managers/SoundManager.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Managers/Inputs.hpp

    ${PROJECT_SOURCE_DIR}/Headers/Network/IPacketManager.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Network/ITCPNetwork.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Network/IUDPNetwork.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Network/Connection.hpp

    ${PROJECT_SOURCE_DIR}/Headers/Reloader/Loader.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Reloader/Interfaces/IMonster.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Reloader/DirectoryWatcher.hpp

    ${PROJECT_SOURCE_DIR}/Headers/Scenes/IScene.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Scenes/Scene.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Scenes/Layouts.hpp

    ${PROJECT_SOURCE_DIR}/Headers/Systems/ISystem.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Systems/System.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Systems/ButtonSystem.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Systems/TextInputSystem.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Systems/ParallaxSystem.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Systems/PlayerSystem.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Systems/DynamicButtonSystem.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Systems/SpriteSystem.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Systems/CollisionSystem.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Systems/MonsterSystem.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Systems/LoadSystem.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Systems/DrawableSystem.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Systems/TransformSystem.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Systems/TextSystem.hpp

    ${PROJECT_SOURCE_DIR}/Headers/Threads/ThreadPool.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Threads/SafeQueue.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Threads/ITask.hpp
)

set(SOURCES_FILES
    ${PROJECT_SOURCE_DIR}/Headers/Models/RTypePack.pb.cc
    ${PROJECT_SOURCE_DIR}/Headers/Models/RGamePack.pb.cc

    ${PROJECT_SOURCE_DIR}/Sources/Logger.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Helper.cpp

    ${PROJECT_SOURCE_DIR}/Sources/Components/Button.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Components/Text.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Components/Sprite.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Components/Parallax.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Components/Component.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Components/TextInput.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Components/Input.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Components/DynamicButton.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Components/Monster.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Components/Drawable.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Components/Transform.cpp

    ${PROJECT_SOURCE_DIR}/Sources/Entities/Entity.cpp

    ${PROJECT_SOURCE_DIR}/Sources/Managers/GameManager.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Managers/SoundManager.cpp

    ${PROJECT_SOURCE_DIR}/Sources/Network/Connection.cpp

    ${PROJECT_SOURCE_DIR}/Sources/Reloader/Loader.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Reloader/DirectoryWatcher.cpp

    ${PROJECT_SOURCE_DIR}/Sources/Scenes/Scene.cpp

    ${PROJECT_SOURCE_DIR}/Sources/Systems/System.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Systems/ButtonSystem.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Systems/TextInputSystem.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Systems/ParallaxSystem.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Systems/PlayerSystem.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Systems/DynamicButtonSystem.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Systems/SpriteSystem.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Systems/CollisionSystem.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Systems/MonsterSystem.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Systems/LoadSystem.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Systems/DrawableSystem.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Systems/TransformSystem.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Systems/TextSystem.cpp

    ${PROJECT_SOURCE_DIR}/Sources/Threads/ThreadPool.cpp
)

if(WIN32)
    add_definitions(-DWIN32_LEAN_AND_MEAN -DRTYPECOMMON_EXPORTS -D_WIN32 -D_WIN32_WINNT=0x0A00)
    set(CMAKE_CXX_FLAGS_RELEASE "/O2")
else()
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
endif(WIN32)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADERS_FILES})

add_library(${PROJECT_NAME} STATIC ${SOURCES_FILES} ${HEADERS_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CONAN_INCLUDE_DIRS_BOOST} ${CONAN_INCLUDE_DIRS_SFML} ${CONAN_INCLUDE_DIRS_PROTOBUF})
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
