#pragma once
#include <GLFW/glfw3.h>

namespace GameEngine {
	class InputManager
	{
	private:
		int horizontal = 0;
		int vertical = 0;
		GLFWwindow* window;

	public:
		InputManager(GLFWwindow* window);
		int getHorizontal();
		int getVertical();
		void getInput();
	};
}



