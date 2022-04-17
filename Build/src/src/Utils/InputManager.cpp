#include "InputManager.h"

GameEngine::InputManager::InputManager(GLFWwindow* window): window(window)
{
}

int GameEngine::InputManager::getHorizontal()
{
    return horizontal;
}

int GameEngine::InputManager::getVertical()
{
    return vertical;
}

void GameEngine::InputManager::getInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        vertical = 1;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        vertical = -1;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        horizontal = -1;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        horizontal = 1;

    if ((glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE) || (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS))
        vertical = 0;

    if ((glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE) || (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS))
        horizontal = 0;
}
