cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)
project(RTypeEntities)

include_directories(${PROJECT_SOURCE_DIR}/Headers ${CMAKE_SOURCE_DIR}/RType.Common/Headers)

set(COMMON_HEADER_FILES
    ${CMAKE_SOURCE_DIR}/RType.Common/Headers/RType.Common.hpp
    ${CMAKE_SOURCE_DIR}/RType.Common/Headers/Reloader/Interfaces/IMonster.hpp
    
    ${PROJECT_SOURCE_DIR}/Headers/RType.Entities.hpp
)

### Example: DefaultMonster
set(MONSTER1_HEADER_FILES
    ${PROJECT_SOURCE_DIR}/Headers/LinearShootingMonster.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Bullet.hpp
)

set(MONSTER1_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/Sources/LinearShootingMonster.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Bullet.cpp
)

# set(MONSTERBOSS_SOURCE_FILES
#      ${PROJECT_SOURCE_DIR}/Sources/BossMonster.cpp
#     ${PROJECT_SOURCE_DIR}/Sources/BulletBoss.cpp
# )

# set(MONSTERBOSS_HEADER_FILES
#     ${PROJECT_SOURCE_DIR}/Headers/BossMonster.hpp
#     ${PROJECT_SOURCE_DIR}/Headers/BulletBoss.hpp
# )

set(MONSTER2_HEADER_FILES
    ${PROJECT_SOURCE_DIR}/Headers/ConeShootingMonster.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Bullet.hpp
)

set(MONSTER2_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/Sources/ConeShootingMonster.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Bullet.cpp
)

set(MONSTER3_HEADER_FILES
    ${PROJECT_SOURCE_DIR}/Headers/DiagonalShootingMonster.hpp
    ${PROJECT_SOURCE_DIR}/Headers/Bullet.hpp
)

set(MONSTER3_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/Sources/DiagonalShootingMonster.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Bullet.cpp
)

if(WIN32)
    add_definitions(-DRTYPECOMMON_INHERITANCE -DRTYPEENTITIES_EXPORTS -D_WIN32)
endif(WIN32)



### Example: Build DefaultMonster
add_library(LinearShootingMonster SHARED ${MONSTER1_SOURCE_FILES} ${MONSTER1_HEADER_FILES} ${COMMON_HEADER_FILES})
add_library(ConeShootingMonster SHARED ${MONSTER2_SOURCE_FILES} ${MONSTER2_HEADER_FILES} ${COMMON_HEADER_FILES})
add_library(DiagonalShootingMonster SHARED ${MONSTER3_SOURCE_FILES} ${MONSTER3_HEADER_FILES} ${COMMON_HEADER_FILES})
# add_library(BossMonster SHARED ${MONSTERBOSS_SOURCE_FILES} ${MONSTER2_HEADER_FILES} ${COMMON_HEADER_FILES})
