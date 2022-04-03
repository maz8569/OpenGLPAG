#include "Player.h"

GameEngine::Player::Player(std::shared_ptr<InputManager> inputManager, std::shared_ptr<Model> model): inputManager(inputManager)
{
	setModel(model);
}
