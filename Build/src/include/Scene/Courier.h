#pragma once
#include "Scene/Entity.h"

namespace GameEngine {
	class Courier : public Entity
	{
	private:
		float speed = 1.f;
	public:
		Courier(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Collision> colMan);
		virtual void render();
		virtual void Update();
		virtual void reactOnCollision(GObject* other);
	};
}


