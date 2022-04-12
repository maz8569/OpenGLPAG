#include "Player.h"

GameEngine::Player::Player(std::shared_ptr<InputManager> inputManager, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Collision> colMan) : inputManager(inputManager), Entity(model, shader, colMan) {}

void GameEngine::Player::render()
{
    Entity::render();
}

void GameEngine::Player::Move()
{
    currentSpeed = speed * inputManager->getHorizontal();

    get_transform().m_position.x += currentSpeed * 0.005;

    currentSpeed = speed * inputManager->getVertical();

    get_transform().m_position.y += currentSpeed * 0.005;

    update(get_parent()->get_transform(), true);

    Entity::Move();
}
