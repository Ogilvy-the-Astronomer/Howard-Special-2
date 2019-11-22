cmake_minimum_required(VERSION 2.6)
project(HOWARDSPECIAL2)

include_directories(src)

add_library(HowardSpecial2
	src/HowardSpecial2/GameObject.h
	src/HowardSpecial2/GameObject.cpp
	src/HowardSpecial2/Core.cpp
	src/HowardSpecial2/Core.h
	src/HowardSpecial2/Component.cpp
	src/HowardSpecial2/Component.h
	src/HowardSpecial2/ShaderProgram.cpp
	src/HowardSpecial2/ShaderProgram.h
	src/HowardSpecial2/VertexArray.cpp
	src/HowardSpecial2/VertexArray.h
	src/HowardSpecial2/VertexBuffer.cpp
	src/HowardSpecial2/VertexBuffer.h
	src/HowardSpecial2/HowardSpecial2.h
	src/HowardSpecial2/Texture.h
	src/HowardSpecial2/Texture.cpp
	src/HowardSpecial2/stb_image.h
	src/HowardSpecial2/stb_image.cpp
	src/HowardSpecial2/Transform.cpp
	src/HowardSpecial2/Transform.h
	src/HowardSpecial2/Renderer.cpp
	src/HowardSpecial2/Renderer.h
	src/HowardSpecial2/Camera.h
	src/HowardSpecial2/Camera.cpp
	src/HowardSpecial2/stb_vorbis.h
	src/HowardSpecial2/SoundBuffer.h
	src/HowardSpecial2/SoundBuffer.cpp
)
target_link_libraries(HowardSpecial2 SDL2 opengl32 openal32 glew32)

add_executable(game
	src/game/main.cpp
	src/game/TriangleRenderer.cpp
	src/game/TriangleRenderer.h
)
target_link_libraries(game HowardSpecial2)