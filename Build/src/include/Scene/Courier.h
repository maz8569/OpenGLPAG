#pragma once
#include "Scene/Entity.h"
#include "Physics/RayCasting/MousePicker.h"
#include "typedefs.h"

namespace GameEngine {
	class Courier : public Entity
	{
	private:
		float speed = 1.f;
		Ref<MousePicker> m_mousePicker;

	public:
		Courier(Ref<MousePicker> mousePicker, Ref<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Collision> colMan);
		virtual void render();
		virtual void Update();
		virtual void reactOnCollision(GObject* other);
	};
}


