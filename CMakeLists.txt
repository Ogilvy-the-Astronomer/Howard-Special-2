cmake_minimum_required(VERSION 2.6)
project(HowardSpecial2)

add_library(HowardSpecial2
	src/HowardSpecial2/dummy.cpp
)
target_link_libraries(HowardSpecial2 SDL2 opengl32 glew32)

add_executable(game
	src/game/main.cpp
)
target_link_libraries(game HowardSpecial2)