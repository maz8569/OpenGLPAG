#include "GObject.h"

GameEngine::GObject::GObject(): SceneNode(), color({1, 1, 1})
{
}

GameEngine::GObject::GObject(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader): m_model(model), m_shader(shader), SceneNode(), color({ 1, 1, 1 })
{
}

void GameEngine::GObject::set_color(glm::vec3 c)
{
	color = c;
}

glm::vec3 GameEngine::GObject::get_color()
{
	return color;
}

void GameEngine::GObject::setModel(std::shared_ptr<Model> model)
{
	m_model = model;
}

void GameEngine::GObject::render()
{
	m_shader->setMat4("model", get_transform().m_world_matrix);
	if (m_model != nullptr)
	{
		m_shader->setVec3("color", color);
		m_model->Draw(m_shader);
	}

	auto children = get_children();

	for (uint32_t i = 0; i < children.size(); ++i)
	{
		children[i]->render();
	}
}

void GameEngine::GObject::Move()
{
}
