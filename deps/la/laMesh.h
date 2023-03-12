#include <glad/glad.h>
#include "HandmadeMath.h"
#define CVECTOR_LOGARITHMIC_GROWTH
#include "cvector.h"
#include "log.h"

typedef struct laMesh {
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	int vertexCount;
	int indexCount;
} laMesh;

typedef struct laVertex {
	HMM_Vec3 position;
	HMM_Vec3 color;
	HMM_Vec2 texCoord;
	HMM_Vec3 normal;
} laVertex;

laMesh* laCreateMesh();
void laDeleteMesh(laMesh* mesh);
void laMeshSetRectangle(laMesh* mesh, float x, float y, float width, float height);
void laMeshSetTriangle(laMesh* mesh, float x1, float y1, float x2, float y2, float x3, float y3);
void laMeshSetVertices(laMesh* mesh, float* vertices, int vertexCount);
void laMeshSetIndices(laMesh* mesh, unsigned int* indices, int indexCount);
void laMeshSetVerticesV(laMesh* mesh, cvector_vector_type(laVertex) vertices);
void laMeshSetIndicesV(laMesh* mesh, cvector_vector_type(unsigned int) indices);
void laMeshAddVertex(laMesh* mesh, laVertex vertex);
void laMeshAddIndex(laMesh* mesh, unsigned int index);
void laMeshDraw(laMesh* mesh);

