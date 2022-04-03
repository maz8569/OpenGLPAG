#pragma once
#include<Entity.h>
#include "InputManager.h"

namespace GameEngine {
	class Player: public Entity
	{
	private:
		std::shared_ptr<InputManager> inputManager;
		
	public:
		Player(std::shared_ptr<InputManager> inputManager, std::shared_ptr<Model> model);
	};
}

