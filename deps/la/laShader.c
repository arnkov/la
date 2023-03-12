#include "laShader.h"
#include "log.h"

void laSetupShader(GLuint shaderProgram, const char* vertexShaderSource, const char* fragmentShaderSource) {

	int success;
	char infoLog[512];

	//create vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, 0);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		log_error("Vertex shader compilation failed:");
		log_error(infoLog);
	} else log_debug("Vertex shader compilation successful. %d", vertexShader);

	//create fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		log_error("Fragment shader compilation failed:");
		log_error(infoLog);
	}
	else log_debug("Fragment shader compilation successful. %d", fragmentShader);

	//create shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		log_error("Shader program linking failed:");
		log_error(infoLog);
	}
	else log_debug("Shader program linking successful: %d", shaderProgram);

	//detach and delete shaders
	glDetachShader(vertexShader, GL_VERTEX_SHADER);
	glDetachShader(fragmentShader, GL_FRAGMENT_SHADER);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void laDeleteShader(GLuint shaderProgram) {
	glDeleteProgram(shaderProgram);
	log_info("deleted shader: %d", shaderProgram);
}

void laBeginShader(GLuint shaderProgram) {
	glUseProgram(shaderProgram);
}

void laEndShader() {
	glUseProgram(0);
}


void laSetBool(GLuint shaderProgram, const char* name, bool value) {
	glUniform1i(glGetUniformLocation(shaderProgram, name), (int)value);
}

void laSetInt(GLuint shaderProgram, const char* name, int value) {
	glUniform1i(glGetUniformLocation(shaderProgram, name), value);
}

void laSetFloat(GLuint shaderProgram, const char* name, float value) {
	glUniform1f(glGetUniformLocation(shaderProgram, name), value);
}

void laSetVec2(GLuint shaderProgram, const char* name, float x, float y) {
	glUniform2f(glGetUniformLocation(shaderProgram, name), x, y);
}

void laSetVec3(GLuint shaderProgram, const char* name, float x, float y, float z) {
	glUniform3f(glGetUniformLocation(shaderProgram, name), x, y, z);
}

void laSetVec4(GLuint shaderProgram, const char* name, float x, float y, float z, float w) {
	glUniform4f(glGetUniformLocation(shaderProgram, name), x, y, z, w);
}

void laSetMat2(GLuint shaderProgram, const char* name, float* mat) {
	glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, mat);
}

void laSetMat3(GLuint shaderProgram, const char* name, float* mat) {
	glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, mat);
}

void laSetMat4(GLuint shaderProgram, const char* name, float* mat) {
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, mat);
}

void laSetTexture(GLuint shaderProgram, const char* name, int textureUnit) {
	glUniform1i(glGetUniformLocation(shaderProgram, name), textureUnit);
}
