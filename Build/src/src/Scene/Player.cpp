#include "Scene/Player.h"

GameEngine::Player::Player(std::shared_ptr<InputManager> inputManager, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Collision> colMan) : inputManager(inputManager), Entity(model, shader, colMan) {}

void GameEngine::Player::render()
{
    Entity::render();
}

void GameEngine::Player::Update()
{
    currentSpeed.x = speed * inputManager->getHorizontal();

    currentSpeed.y = speed * inputManager->getVertical();

    //currentSpeed = glm::normalize(currentSpeed);
    get_transform().m_position.x += currentSpeed.x * 0.005;

    get_transform().m_position.y += currentSpeed.y * 0.005;

    jumpPower += gravity / 60;
    get_transform().m_position.z += jumpPower * 0.005;
    if (get_transform().m_position.z < 0)
    {
        get_transform().m_position.z = 0;
        jumpPower = 0;
    }

    if (inputManager->getJump()) {
        jump();
    }

    update(get_parent()->get_transform(), true);

    Entity::Update();
}

void GameEngine::Player::jump()
{
    jumpPower = jumpHeight;
}

void GameEngine::Player::reactOnCollision(GObject* other)
{
    get_transform().m_position.y -= currentSpeed.x * 0.005;
    get_transform().m_position.x -= currentSpeed.y * 0.005;
    
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