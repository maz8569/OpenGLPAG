#include "WindowManager.h"

GameEngine::WindowManager::WindowManager()
{
	createWindow();
}

GameEngine::WindowManager::~WindowManager()
{
	closeWindow();
}

void GameEngine::WindowManager::createWindow()
{
    const char* glsl_version = "#version 460";
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    /*
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, name.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    */
}

void GameEngine::WindowManager::updateWindow()
{
}

void GameEngine::WindowManager::closeWindow()
{
}
