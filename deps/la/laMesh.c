#pragma once

#include "laMesh.h"
#include "laLog.h"

#define M_PI 3.14159265358979323846

laMesh laCreateMesh() {
	laMesh mesh = {0};
	glGenVertexArrays(1, &mesh.vao);
	glGenBuffers(1, &mesh.vbo);
	glGenBuffers(1, &mesh.ebo);
	mesh.vertexCount = 0;
	mesh.indexCount = 0;
	laLogDebug("laMesh created");
	return mesh;
}

void laMeshDelete(laMesh* mesh) {
	glDeleteVertexArrays(1, &mesh->vao);
	glDeleteBuffers(1, &mesh->vbo);
	glDeleteBuffers(1, &mesh->ebo);
	laLogDebug("laMesh deleted");
}

void laMeshSetRectangle(laMesh* mesh, float x, float y, float width, float height) {
	float vertices[] = {
		x + width, y + height, 0.0f, // top right
		x + width, y, 0.0f, // bottom right
		x, y, 0.0f, // bottom left
		x, y + height, 0.0f // top left
	};

	unsigned int indices[] = { 
			0, 1, 3, // first Triangle
			1, 2, 3 // second Triangle
		};
	laMeshSetVertices(mesh, vertices, 4);
	laMeshSetIndices(mesh, indices, 6);
	laLogDebug("laMesh rectangle set");
}

void laMeshSetTriangle(laMesh* mesh, float x1, float y1, float x2, float y2, float x3, float y3) {
	float vertices[] = {
		x1, y1, 0.0f, // top right
		x2, y2, 0.0f, // bottom right
		x3, y3, 0.0f // bottom left
	};
	unsigned int indices[] = { 
				0, 1, 2 
			};
	laMeshSetVertices(mesh, vertices, 3);
	laMeshSetIndices(mesh, indices, 3);
	laLogDebug("laMesh triangle set");
}

void laMeshSetVertices(laMesh* mesh, float* vertices, int vertexCount) {
	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	//position
	glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//color
	glBufferData(GL_ARRAY_BUFFER, vertexCount * 6 * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//texCoord
	glBufferData(GL_ARRAY_BUFFER, vertexCount * 8 * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//normal
	glBufferData(GL_ARRAY_BUFFER, vertexCount * 11 * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	mesh->vertexCount = vertexCount;
	laLogDebug("laMesh vertices set");
}

void laMeshSetIndices(laMesh* mesh, unsigned int* indices, int indexCount) {
	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	mesh->indexCount = indexCount;
	laLogDebug("laMesh indices set");
}

/*
void laMeshAddVertex(laMesh* mesh, laVertex vertex) {
	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh->vertexCount * sizeof(laVertex), &vertex, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(laVertex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(laVertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(laVertex), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(laVertex), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	mesh->vertexCount++;
	log_debug("laMesh vertex added");
}
*/
void laMeshAddIndex(laMesh* mesh, unsigned int index) {
	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indexCount * sizeof(unsigned int), &index, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	mesh->indexCount++;
	laLogDebug("laMesh index added");
}

void laMeshDraw(laMesh* mesh) {
	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
