/*
custom dummy file to start
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 0.0, 1.0);
	
	// Draw game objects down here
}

int main(int argc, char** argv)
{
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello OpenGL ", NULL, NULL);

	glfwMakeContextCurrent(window);
	glewInit();

	while (!glfwWindowShouldClose(window))
	{	
		// in this loop all renders will ocure

		renderScene();
		// Chapter 6 p.175 Creating a mesh class to do
		//
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}