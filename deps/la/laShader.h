#pragma once

#include <glad/glad.h>
#include <stdbool.h>


void laSetupShader(GLuint shaderProgram, const char* vertexShaderSource, const char* fragmentShaderSource);
void laDeleteShader(GLuint shaderProgram);

void laBeginShader(GLuint shaderProgram);
void laEndShader();

void laSetBool(GLuint shaderProgram, const char* name, bool value);
void laSetInt(GLuint shaderProgram, const char* name, int value);
void laSetFloat(GLuint shaderProgram, const char* name, float value);
void laSetVec2(GLuint shaderProgram, const char* name, float x, float y);
void laSetVec3(GLuint shaderProgram, const char* name, float x, float y, float z);
void laSetVec4(GLuint shaderProgram, const char* name, float x, float y, float z, float w);
void laSetMat2(GLuint shaderProgram, const char* name, float* mat);
void laSetMat3(GLuint shaderProgram, const char* name, float* mat);
void laSetMat4(GLuint shaderProgram, const char* name, float* mat);
void laSetTexture(GLuint shaderProgram, const char* name, int textureUnit);
