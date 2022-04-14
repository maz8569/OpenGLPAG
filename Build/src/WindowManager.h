#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

namespace GameEngine {
	class WindowManager
	{
	public:

		const unsigned int SCR_WIDTH = 1920;
		const unsigned int SCR_HEIGHT = 1080;
		GLFWwindow* window = nullptr;
		std::string name = "Package Rush";

		WindowManager();
		~WindowManager();

		int createWindow();
		void updateWindow();
		void closeWindow();
	};
}

