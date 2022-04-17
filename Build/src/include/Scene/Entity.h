#pragma once
#include "Scene/GObject.h"

namespace GameEngine {
	class Entity: public GObject
	{
	private:

	public:
		Entity(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Collision> colMan);
		virtual void render();
		virtual void Update();
		virtual void reactOnCollision(GObject* other);
	};
}

