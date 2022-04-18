#include "Physics/RayCasting/MousePicker.h"
#include "Rendering/WindowManager.h"

GameEngine::MousePicker::MousePicker(Ref<Camera> camera, glm::mat4 projectionMatrix, Ref<InputManager> inputManager)
	: m_camera(camera), m_projectionMatrix(projectionMatrix), m_inputManager(inputManager)
{
	m_viewMatrix = camera->GetViewMatrix();
}

void GameEngine::MousePicker::update()
{
	m_viewMatrix = m_camera->GetViewMatrix();
	if (m_inputManager->m_isRclicked)
	{
		m_currentRay = calculateRay();
	}
	
}

glm::vec3 GameEngine::MousePicker::getCurrentRay()
{
	return m_currentRay;
}

glm::vec3 GameEngine::MousePicker::calculateRay()
{

	float posx = m_inputManager->m_posx;
	float posy = m_inputManager->m_posy;
	glm::vec2 normalizedCoords = getNormalizedDeviceCoords(posx, posy);
	glm::vec4 clipCoords = glm::vec4(normalizedCoords.x, normalizedCoords.y, -1, 1);
	glm::vec4 eyeCoords = toEyeCoords(clipCoords);
	glm::vec3 worldRay = toWorldCoords(eyeCoords);
	return worldRay;
}

glm::vec2 GameEngine::MousePicker::getNormalizedDeviceCoords(float mouseX, float mouseY)
{
	float x = (2.0f * mouseX) / WindowManager::SCR_WIDTH - 1;
	float y = (2.0f * mouseY) / WindowManager::SCR_HEIGHT - 1;
	return glm::vec2(x, -y);
}

glm::vec4 GameEngine::MousePicker::toEyeCoords(glm::vec4 clipCoords)
{
	glm::mat4 invertedProjection = glm::inverse(m_projectionMatrix);
	glm::vec4 eyeCoords = invertedProjection * clipCoords;
	return glm::vec4(eyeCoords.x, eyeCoords.y, -1, 0);
}

glm::vec3 GameEngine::MousePicker::toWorldCoords(glm::vec4 eyeCoords)
{
	glm::mat4 invertedView = glm::inverse(m_viewMatrix);
	glm::vec4 rayWorld = invertedView * eyeCoords;
	glm::vec3 mouseRay = glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z);
	mouseRay = glm::normalize(mouseRay);
	return mouseRay;
}
