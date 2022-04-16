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
		//std::vector<std::shared_ptr<Collision>> collisions;
		//std::shared_ptr<Plan> boundingVolume;
		Ref<Model> m_model;
		Ref<AABB> m_aabb;
		glm::vec3 m_color;
		Ref<Shader> m_shader;
		bool render_AABB = false;
		unsigned int VBO, VAO;
		glm::vec3 offset;
		std::string m_name;
		std::string m_tag;
		unsigned int ID;
		static unsigned int ms_uiNextID;

	public:
		GObject();
		explicit GObject(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Collision> colMan);
		~GObject();

		void set_color(glm::vec3 c);

		glm::vec3 get_color();

		void setModel(std::shared_ptr<Model> model);
		Ref<AABB> getAABB() const;

		virtual void render();
		virtual void Update();

		virtual void reactOnCollision();

		void MoveColliders();

		void set_render_AABB(bool set);

		void setName(std::string name);
		const std::string& getName() const;

		unsigned int getID() const;
		static unsigned int getNextID();

	};
}


