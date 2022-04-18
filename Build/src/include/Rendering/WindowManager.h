#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

// manages window
namespace GameEngine {
	class WindowManager
	{
	public:
		void mouse_callback(GLFWwindow* window, double xpos, double ypos);

		static const unsigned int SCR_WIDTH = 1920;
		static const unsigned int SCR_HEIGHT = 1080;
		GLFWwindow* window = nullptr;

		//name of the game
		std::string name = "Package Rush";

		WindowManager();
		~WindowManager();

		int createWindow();
		void updateWindow();
		void closeWindow();
		void blockCursor();
		void freeCursor();
	};
}

