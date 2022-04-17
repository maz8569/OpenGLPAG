#include "Scene/Player.h"

GameEngine::Player::Player(std::shared_ptr<InputManager> inputManager, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Collision> colMan) : inputManager(inputManager), Entity(model, shader, colMan) {}

void GameEngine::Player::render()
{
    Entity::render();
}

void GameEngine::Player::Update()
{
    currentSpeed = speed * inputManager->getHorizontal();

    get_transform().m_position.x += currentSpeed * 0.005;

    currentSpeed = speed * inputManager->getVertical();

    get_transform().m_position.y += currentSpeed * 0.005;

    update(get_parent()->get_transform(), true);

    Entity::Update();
}

void GameEngine::Player::reactOnCollision(GObject* other)
{
    get_transform().m_position.x -= currentSpeed * 0.005;
    
    /*
    auto vec = getAABB()->testDepth(other->getAABB());
    int i = 0;
    
    if (abs(vec[0]) > abs(vec[1]))
    {
        if (vec[1] > vec[2])
        {
            i = 2;
        }
        else
        {
            i = 1;
        }
    }
    else
    {
        if (vec[0] > vec[2])
        {
            i = 2;
        }
        else
        {
            i = 0;
        }
    }
    
    std::cout << vec[i];
    */
}
