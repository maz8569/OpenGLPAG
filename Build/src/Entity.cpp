#include "Entity.h"

GameEngine::Entity::Entity(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Collision> colMan) : GObject(model, shader, colMan)
{
}

void GameEngine::Entity::render()
{
	GObject::render();
}

void GameEngine::Entity::Move()
{
	GObject::Move();
}
