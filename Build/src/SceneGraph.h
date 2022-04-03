#pragma once
#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H
#include "Model.h"
#include <list>

namespace GameEngine {

	struct Transform
	{
		Transform() : m_world_matrix(1.0f) {}
	
		glm::mat4 get_combined_matrix()
		{	
			return glm::translate(glm::mat4(1.0f), m_position) *
					glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), glm::vec3(-1, 0, 0)) *
					glm::rotate (glm::mat4(1.0f), glm::radians(m_rotation.y), glm::vec3(0, -1, 0)) *
					glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.z), glm::vec3(0, 0, -1)) *
					glm::scale(glm::mat4(1.0f), m_scale);
		}

		glm::mat4 m_world_matrix;

		glm::vec3 m_position = glm::vec3(0.0f);
		glm::vec3 m_rotation = glm::vec3(0.0f);
		glm::vec3 m_scale = glm::vec3(1.0f);
	};

	struct SceneNode
	{
	public:
		SceneNode() : m_dirty(true) { m_transform = Transform(); m_model = nullptr; color = { 1, 1, 1 }; }
		explicit SceneNode(std::shared_ptr<Model> m) : m_model(m), m_dirty(true) { m_transform = Transform(); color = { 1, 1, 1 }; }

		void add_child(std::shared_ptr<SceneNode>& child)
		{
			m_children.push_back(child);
		}

		void update(const Transform &parent_transform, bool dirty)
		{
			dirty |= m_dirty;

			if (dirty)
			{
				m_transform.m_world_matrix = m_transform.get_combined_matrix();
				m_transform.m_world_matrix = parent_transform.m_world_matrix * m_transform.m_world_matrix;
				//m_dirty = false;
			}

			for (uint32_t i = 0; i < m_children.size(); ++i)
			{
				m_children[i]->update(m_transform, dirty);
			}
		}

		void render(Shader shader)
		{
			shader.setMat4("model", m_transform.m_world_matrix);
			if (m_model != nullptr)
			{
				shader.setVec3("color", color);
				m_model->Draw(shader);
			}

			for (uint32_t i = 0; i < m_children.size(); ++i)
			{
				m_children[i]->render(shader);
			}
		}

		void update_transform()
		{
			m_transform.m_world_matrix = m_transform.get_combined_matrix();
			m_dirty = true;
		}

		Transform& get_transform()
		{
			return m_transform;
		}

		void set_local_position(const glm::vec3& newPosition)
		{
			m_transform.m_position = newPosition;
			m_dirty = true;
		}

		void set_local_rotation(const glm::vec3& newRotation)
		{
			m_transform.m_rotation = newRotation;
			m_dirty = true;
		}

		void set_local_scale(glm::vec3 newScale)
		{
			m_transform.m_scale = newScale;
			m_dirty = true;
		}

		void set_color(glm::vec3 c)
		{
			color = c;
		}

		glm::vec3 get_color()
		{
			return color;
		}

		void setModel(std::shared_ptr<Model> model) {
			m_model = model;
		}

	private:
		std::vector<std::shared_ptr<SceneNode>> m_children;
		Transform m_transform;
		bool m_dirty;
		std::shared_ptr<Model> m_model;
		glm::vec3 color;


	};
}
#endif
