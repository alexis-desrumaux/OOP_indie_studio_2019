
cmake_minimum_required(VERSION 2.8.9)

project(bomberman)

set(SOURCES Code/main.cpp
            Code/src/Display/Buttons.cpp
            Code/src/Display/Display.cpp
            Code/src/Game/Game.cpp
            Code/src/Game/GameObjects/GameObjects.cpp
            Code/src/Game/GameObjects/Bomb/Bomb.cpp
            Code/src/Game/GameObjects/Bomb/Fireball/Fireball.cpp
            Code/src/Game/GameObjects/Bomberman/Bomberman.cpp
            Code/src/Game/GameObjects/BombermanIA/BombermanIA.cpp
            Code/src/Game/GameObjects/Camera/Camera.cpp
            Code/src/Game/GameObjects/Map/Map.cpp
            Code/src/Game/GameObjects/Map/BombUp/BombUp.cpp
            Code/src/Game/GameObjects/Map/DBlock/DBlock.cpp
            Code/src/Game/GameObjects/Map/EmptyBlock/EmptyBlock.cpp
            Code/src/Game/GameObjects/Map/FireUp/FireUp.cpp
            Code/src/Game/GameObjects/Map/Floor/Floor.cpp
            Code/src/Game/GameObjects/Map/SpeedUp/SpeedUp.cpp
            Code/src/Game/GameObjects/Map/Wall/Wall.cpp
            Code/src/Game/GameObjects/Map/WallPass/WallPass.cpp
            Code/src/Game/Music.cpp
            Code/src/Libs/Irrlicht/Irrlicht.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")


set(IRRLICHT_LIBRARY
-lIrrlicht
-lGL
-lGLU
-lXext
-lX11
-lXxf86vm
-lsfml-audio
-lsfml-system
-lsfml-window
)

include_directories(./libs/Irrlicht/include/
                    ./Code/include/)

add_executable(bomberman
            ${SOURCES})

target_link_libraries(bomberman
            ${IRRLICHT_LIBRARY})