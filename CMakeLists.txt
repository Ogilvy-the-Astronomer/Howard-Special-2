cmake_minimum_required(VERSION 2.6)
project(HowardSpecial2)

add_library(HowardSpecial2
	src/HowardSpecial2/GameObject.h
	src/HowardSpecial2/GameObject.cpp
	src/HowardSpecial2/Core.cpp
	src/HowardSpecial2/Core.h
	src/HowardSpecial2/Component.cpp
	src/HowardSpecial2/Component.h
)
target_link_libraries(HowardSpecial2 SDL2 opengl32 glew32)

add_executable(game
	src/game/main.cpp
)
target_link_libraries(game HowardSpecial2)