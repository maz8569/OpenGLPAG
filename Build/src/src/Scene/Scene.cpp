#include "Scene/Scene.h"

using namespace GameEngine;

GameEngine::Scene::Scene(std::string name): m_name(name)
{
	m_camera = CreateRef<Camera>(Camera(glm::vec3(0.0f, 3.0f, 0.0f)));
	m_camera->Pitch = -90;
	m_camera->Yaw = 90;

	m_root = CreateRef<GObject>();
}

void GameEngine::Scene::Start()
{
}

void GameEngine::Scene::Update()
{
}

void GameEngine::Scene::FixedUpdate()
{
}

void GameEngine::Scene::LateUpdate()
{
}

void GameEngine::Scene::Render()
{
}

Ref<GObject> GameEngine::Scene::getObjectByName(const std::string& name)
{
	return Ref<GObject>();
}

std::vector<Ref<GObject>> GameEngine::Scene::getAllObjects()
{
	return std::vector<Ref<GObject>>();
}

std::vector<Ref<GObject>> GameEngine::Scene::getAllObjectsByName(const std::string& name)
{
	return std::vector<Ref<GObject>>();
}

Ref<GObject> GameEngine::Scene::getObjectByID(unsigned int ID)
{
	return Ref<GObject>();
}

Ref<Camera> GameEngine::Scene::getCamera()
{
	return m_camera;
}
