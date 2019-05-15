#include "glRenderer.h"
#include "../pch.h"

void glRenderer::render(GLFWwindow* windowToRenderTo)
{
	while (glfwGetKey(windowToRenderTo, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(windowToRenderTo) == 0)
	{
		// Clear the screen.
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw nothing, see you in tutorial 2 !


		// Swap buffers
		glfwSwapBuffers(windowToRenderTo);
		glfwPollEvents();
	}
}