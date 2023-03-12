#include "laApp.h"
#include "log.h"


void laInit(int major, int minor) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	log_info("OpenGL version: %d.%d", major, minor);
}

GLFWwindow* laCreateWindow(int width, int height, const char* title) {

	GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL) {
		log_error("Failed to create GLFW window");
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		log_error("Failed to initialize GLAD");
		return NULL;
	}

	glViewport(0, 0, width, height);

	log_info("Viewport: %d, %d, %d, %d", 0, 0, width, height);

	return window;
}

float laGetWidth(GLFWwindow* window) {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return width;
}

float laGetHeight(GLFWwindow* window) {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return width;
}

void laSetVsync(bool vsync) {
	if (vsync) {
		glfwSwapInterval(1);
		log_info("Vsync enabled");
	}
	else {
		glfwSwapInterval(0);
	}
}

bool laShouldClose(GLFWwindow* window) {
	return glfwWindowShouldClose(window);
}

void laSwapBuffers(GLFWwindow* window) {
	glfwSwapBuffers(window);
}

void laPollEvents() {
	glfwPollEvents();
}

void laFramebufferChanged(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void laProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void laClear(float r, float g, float b, float a, bool clearDepth) {

	glClearColor(r, g, b, a);
	if (clearDepth) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	else {
		glClear(GL_COLOR_BUFFER_BIT);
	}
}

void laEnableDepthTest() {
	glEnable(GL_DEPTH_TEST);
}

void laTerminate() {
	glfwTerminate();
	log_info("la terminated");
}
