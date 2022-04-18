#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

namespace GameEngine {
	class InputManager
	{
	private:
		int horizontal = 0;
		int vertical = 0;
		bool jump = false;
		GLFWwindow* window;

	public:

		bool m_isRclicked = false;

		double m_posx = 0;
		double m_posy = 0;

		InputManager(GLFWwindow* window);
		int getHorizontal();
		int getVertical();
		bool getJump();
		void getInput();
	};
}



