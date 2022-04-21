#pragma once
#include <glm/glm.hpp>
#include<Scene/Entity.h>
#include "Utils/InputManager.h"

namespace GameEngine {
	class Player: public Entity
	{
	private:
		float speed = 20;
		float jumpHeight = 20;
		float gravity = -50;
		bool isGrounded = true;

		glm::vec2 currentSpeed = { 0, 0 };
		float jumpPower = 0;

		std::shared_ptr<InputManager> inputManager;
		
	public:
		Player(std::shared_ptr<InputManager> inputManager, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Collision> colMan);

		virtual void render();
		virtual void Update();
		void jump();
		virtual void reactOnCollision(GObject* other);
	};
}

