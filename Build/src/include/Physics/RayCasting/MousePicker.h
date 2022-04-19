#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "typedefs.h"
#include "Scene/Camera.h"
#include "Utils/InputManager.h"

namespace GameEngine {
	class MousePicker
	{
	private:
		glm::vec3 m_currentRay;

		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
		Ref<Camera> m_camera;
		Ref<InputManager> m_inputManager;

		glm::vec3 calculateRay();
		glm::vec2 getNormalizedDeviceCoords(float mouseX, float mouseY);
		glm::vec4 toEyeCoords(glm::vec4 clipCoords);
		glm::vec3 toWorldCoords(glm::vec4 eyeCoords);

	public:
		MousePicker(Ref<Camera> camera, glm::mat4 projectionMatrix, Ref<InputManager> inputManager);

		bool update();

		glm::vec3 getCurrentRay();

		glm::vec3 getCameraPos();
	};
}
