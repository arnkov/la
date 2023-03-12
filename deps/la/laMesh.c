#include "laMesh.h"

#define M_PI 3.14159265358979323846

laMesh* laCreateMesh() {
	laMesh* mesh = malloc(sizeof(laMesh));
	glGenVertexArrays(1, &mesh->vao);
	glGenBuffers(1, &mesh->vbo);
	glGenBuffers(1, &mesh->ebo);
	mesh->vertexCount = 0;
	mesh->indexCount = 0;
	return mesh;
	log_debug("laMesh created");
}

void laDeleteMesh(laMesh* mesh) {
	glDeleteVertexArrays(1, &mesh->vao);
	glDeleteBuffers(1, &mesh->vbo);
	glDeleteBuffers(1, &mesh->ebo);
	free(mesh);
	log_debug("laMesh deleted");
}

void laMeshSetRectangle(laMesh* mesh, float x, float y, float width, float height) {
	float vertices[] = {
		x + width, y + height, 0.0f, // top right
		x + width, y, 0.0f, // bottom right
		x, y, 0.0f, // bottom left
		x, y + height, 0.0f // top left
	};

	unsigned int indices[] = { // note that we start from 0!
			0, 1, 3, // first Triangle
			1, 2, 3 // second Triangle
		};
	laMeshSetVertices(mesh, vertices, 4);
	laMeshSetIndices(mesh, indices, 6);
	log_debug("laMesh rectangle set");
}

void laMeshSetTriangle(laMesh* mesh, float x1, float y1, float x2, float y2, float x3, float y3) {
	float vertices[] = {
		x1, y1, 0.0f, // top right
		x2, y2, 0.0f, // bottom right
		x3, y3, 0.0f // bottom left
	};
	unsigned int indices[] = { // note that we start from 0!
				0, 1, 2 // first Triangle
			};
	laMeshSetVertices(mesh, vertices, 3);
	laMeshSetIndices(mesh, indices, 3);
	log_debug("laMesh triangle set");
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
	log_debug("laMesh vertices set");
}

void laMeshSetIndices(laMesh* mesh, unsigned int* indices, int indexCount) {
	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	mesh->indexCount = indexCount;
	log_debug("laMesh indices set");
}

void laMeshSetVerticesV(laMesh* mesh, cvector_vector_type(laVertex) vertices) {

	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER, cvector_size(vertices) * sizeof(laVertex), vertices, GL_STATIC_DRAW);

	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(laVertex), (void*)0);
	glEnableVertexAttribArray(0);
	//color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(laVertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//texCoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(laVertex), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	//tangent
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(laVertex), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);
	//normals
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(laVertex), (void*)(11 * sizeof(float)));
	glEnableVertexAttribArray(4);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	mesh->vertexCount = cvector_size(vertices);
	log_debug("laMesh vertices set");
}

void laMeshSetIndicesV(laMesh* mesh, cvector_vector_type(unsigned int) indices) {
	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cvector_size(indices) * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	mesh->indexCount = cvector_size(indices);
	log_debug("laMesh indices set");
}

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

void laMeshAddIndex(laMesh* mesh, unsigned int index) {
	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indexCount * sizeof(unsigned int), &index, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	mesh->indexCount++;
	log_debug("laMesh index added");
}

void laMeshDraw(laMesh* mesh) {
	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}