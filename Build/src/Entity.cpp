#include "Entity.h"

GameEngine::Entity::Entity(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader) : GObject(model, shader)
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
