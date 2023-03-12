cmake_minimum_required(VERSION 3.10)

project(laApp)

set(source main.c
	deps/log/log.h
	deps/log/log.c)

add_subdirectory(deps)

add_executable(${CMAKE_PROJECT_NAME} ${source})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE la glad glfw)

include_directories(deps/la)
include_directories(deps/miniaudio)
include_directories(deps/stb_image)
include_directories(deps/glfw/include)
include_directories(deps/glad/include)
include_directories(deps/log)
