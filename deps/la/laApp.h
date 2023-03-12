#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>


void laInit(int major, int minor);
GLFWwindow* laCreateWindow(int width, int height, const char* title);
float laGetWidth(GLFWwindow* window);
float laGetHeight(GLFWwindow* window);

void laSetVsync(bool vsync);

void laFramebufferChanged(GLFWwindow* window, int width, int height);
void laProcessInput(GLFWwindow* window);
bool laShouldClose(GLFWwindow* window);
void laSwapBuffers(GLFWwindow* window);
void laPollEvents();

void laClear(float r, float g, float b, float a, bool clearDepth);
void laEnableDepthTest();

void laTerminate();