cmake_minimum_required(VERSION 3.10)

project(la)


set(laSource
	laApp.h
	laApp.c
	laMesh.h
	laMesh.c
	laShader.h
	laShader.c
	laTexture.h
	laTexture.c
	laFile.h
	laLog.h
	)

add_library(la STATIC ${laSource})

include_directories(./../miniaudio)
include_directories(./../stb_image)
include_directories(./../glad/include)
include_directories(./../glfw/include)
include_directories(./../log)
