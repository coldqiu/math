#pragma once

/***  **/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	std::cout << "window size change" << width  << std::endl;
}

void processInput(GLFWwindow* window)
{
	//����û��Ƿ����˷��ؼ�(Esc)
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
