#pragma once
#include <memory>
#include <vector>
#include <Collision.h>
#include "SceneGraph.h"
#include <Component.h>
#include <AABB.h>

namespace GameEngine {
	class GObject: public SceneNode
	{
	private:
		std::vector<std::shared_ptr<Collision>> collisions;
		//std::shared_ptr<Plan> boundingVolume;
		std::shared_ptr<Model> m_model;
		std::shared_ptr<AABB> m_aabb;
		glm::vec3 m_color;
		std::shared_ptr<Shader> m_shader;
		bool render_AABB = false;
		unsigned int VBO, VAO;

	public:
		GObject();
		explicit GObject(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader);
		~GObject();

		void set_color(glm::vec3 c);

		glm::vec3 get_color();

		void setModel(std::shared_ptr<Model> model);

		virtual void render();
		virtual void Move();

		void set_render_AABB(bool set);
	};
}


