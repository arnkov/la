#include "laApp.h"
#include "laShader.h"
#include "laMesh.h"
#include "laTexture.h"
#include "laFile.h"


int main() {

	log_set_level(LOG_DEBUG);
	laInit(3, 3);
	GLFWwindow* window = laCreateWindow(800, 800, "laApp");
	laSetVsync(true);
	laEnableDepthTest();

	//-------------------
	const char* vertexShaderSource = readFile("default.vert");
	const char* fragmentShaderSource = readFile("default.frag");

	//create the shader
	GLuint shader = glCreateProgram();
	laSetupShader(shader, vertexShaderSource, fragmentShaderSource);

	//create the mesh
	laMesh* mesh = laCreateMesh();
	laBeginShader(shader);
	laMeshSetRectangle(mesh, -.5f, -.5f, 1.0f, 1.0f);
	laEndShader();

	float width = laGetWidth(window);
	float height = laGetHeight(window);
	

	while (!laShouldClose(window))
	{
		laProcessInput(window);
		laClear(0.2f, 0.3f, 0.3f, 1.0f, true);

		laBeginShader(shader);
		
		laSetVec2(shader, "u_resolution", width, height);
		
		laMeshDraw(mesh);


		laSwapBuffers(window);
		laPollEvents();
	}

	laDeleteShader(shader);
	laDeleteMesh(mesh);

	laTerminate();

	return 0;
}