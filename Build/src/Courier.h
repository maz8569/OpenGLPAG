#pragma once
#include "Entity.h"

namespace GameEngine {
	class Courier : public Entity
	{
	private:
		float speed = 1.f;
	public:
		Courier(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader);
		virtual void render();
		virtual void Move();
	};
}


