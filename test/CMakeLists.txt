cmake_minimum_required(VERSION 3.9)
PROJECT(cpp_indie_studio)

set(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(bomberman
		map.cpp
)

include_directories(inc /usr/include/irrlicht)

target_link_libraries(bomberman -lIrrlicht)
