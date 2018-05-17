cmake_minimum_required(VERSION 3.9)
PROJECT(cpp_indie_studio)

set(CMAKE_CXX_STANDARD 11)

set(SRCS
  src/Menu.cpp
  src/main.cpp
  src/MenuItem.cpp
  src/Core.cpp
  src/Actions.cpp
  Game/GameCore.cpp
  Irrlicht/IrrLib.cpp
  Irrlicht/MyEventReceiver.cpp
  Game/Item.cpp
  Game/eItem.cpp
  )

ADD_EXECUTABLE(bomberman ${SRCS})

include_directories(inc /usr/include/irrlicht)
include_directories(inc include)

target_link_libraries(bomberman -lIrrlicht)
