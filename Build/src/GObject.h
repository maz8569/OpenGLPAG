#pragma once
#include <memory>
#include <vector>
#include <Collision.h>
#include "SceneGraph.h"

namespace GameEngine {
	class GObject: public SceneNode
	{
	private:
		std::vector<std::shared_ptr<Collision>> collisions;
		std::shared_ptr<Model> m_model;
		glm::vec3 color;
		std::shared_ptr<Shader> m_shader;

	public:
		GObject();
		explicit GObject(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader);

		void set_color(glm::vec3 c);

		glm::vec3 get_color();

		void setModel(std::shared_ptr<Model> model);

		virtual void render();
		virtual void Move();

	};
}


