#include "Courier.h"

GameEngine::Courier::Courier(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Collision> colMan) : Entity(model, shader, colMan)
{

}

void GameEngine::Courier::render()
{
	Entity::render();
}

void GameEngine::Courier::Move()
{
	if (get_transform().m_position.y > 10 || get_transform().m_position.y < -10)
		speed *= -1;
	get_transform().m_position.y += 0.01 * speed;
	update(get_parent()->get_transform(), true);
	Entity::Move();
}
