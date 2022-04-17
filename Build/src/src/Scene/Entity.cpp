#include "Scene/Entity.h"

GameEngine::Entity::Entity(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Collision> colMan) : GObject(model, shader, colMan)
{
}

void GameEngine::Entity::render()
{
	GObject::render();
}

void GameEngine::Entity::Update()
{
	GObject::Update();
}

void GameEngine::Entity::reactOnCollision(GObject* other)
{
}
