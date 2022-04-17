#pragma once
#include<Scene/Entity.h>
#include "Utils/InputManager.h"

namespace GameEngine {
	class Player: public Entity
	{
	private:
		float speed = 20;
		float turnSpeed = 160;

		float currentSpeed = 0;
		float currentTurnSpeed = 0;

		std::shared_ptr<InputManager> inputManager;
		
	public:
		Player(std::shared_ptr<InputManager> inputManager, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Collision> colMan);

		virtual void render();
		virtual void Update();
		virtual void reactOnCollision(GObject* other);
	};
}

