cmake_minimum_required(VERSION 3.9)
PROJECT(cpp_indie_studio)

set(CMAKE_CXX_STANDARD 17)

set(SRCS
  src/Menu.cpp
  src/MenuItem.cpp
  src/main.cpp
  src/Core.cpp
  src/Actions.cpp
  Game/GameCore.cpp
  Irrlicht/IrrLib.cpp
  Irrlicht/MyEventReceiver.cpp
  Game/Wall.cpp
  Game/Crate.cpp
  Game/Player.cpp
  Game/Bomb.cpp
  Game/ACube.cpp
  Game/Fire.cpp
  Game/EntityPos.cpp
  Game/Item.cpp
  Game/Shield.cpp
  src/Music.cpp
  src/MapGenerator.cpp
  )

ADD_EXECUTABLE(bomberman ${SRCS})

include_directories(inc /usr/include/irrlicht)
include_directories(inc include)

target_link_libraries(bomberman -lIrrlicht)
target_link_libraries(bomberman -lIrrKlang)
target_link_libraries(bomberman -lpthread)
target_link_libraries(bomberman -pthread)
target_link_libraries(bomberman -lstdc++fs)
