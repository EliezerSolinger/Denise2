
cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 98)

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
)

add_library(denise2 STATIC
	dsystem.cpp
	denise.cpp
)
target_link_libraries(denise2 glad glfw)

add_executable(boxes
	examples/boxes.cpp
)
target_link_libraries(boxes denise2)
add_executable(mapgenerator 
	examples/perlin/mapgenerator.cpp
)
target_link_libraries(mapgenerator denise2)

