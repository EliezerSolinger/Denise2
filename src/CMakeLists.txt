
cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

SET(BUILD_SHARED_LIBS FALSE)

project(Denise2)

find_package(OpenGL REQUIRED)
add_subdirectory("dependencies")

include_directories(
	${OPENGL_INCLUDE_DIRS} 
	${PROJECT_SOURCE_DIR}
	"dependencies"
	"dependencies/glad/include"
	"dependencies/glfw-3.3.2/include"
	"dependencies/stb/include"
)

add_library(denise2 STATIC
	dsystem.cpp
	mesh_renderer.cpp
)
target_link_libraries(denise2 glad glfw stb_image)

add_executable(boxes
	examples/boxes.cpp
)
target_link_libraries(boxes denise2)

add_executable(toca 
	tocadolobo/main.cpp
	tocadolobo/world/world.cpp
)
target_link_libraries(toca denise2)

