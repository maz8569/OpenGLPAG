#include "GObject.h"

GameEngine::GObject::GObject(): SceneNode(), m_color({1, 1, 1})
{
}

GameEngine::GObject::GObject(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader): m_model(model), m_shader(shader), SceneNode(), m_color({ 1, 1, 1 })
{
	m_aabb = std::make_shared<AABB>(generateAABB(model));
	std::cout << m_aabb->center.x << " " << m_aabb->center.y << " " << m_aabb->center.z << " " << std::endl;
	std::cout << m_aabb->extents.x << " " << m_aabb->extents.y << " " << m_aabb->extents.z << " " << std::endl;
	float vertices[] = {
		m_aabb->center.x + m_aabb->extents.x, m_aabb->center.y + m_aabb->extents.y, m_aabb->center.z + m_aabb->extents.z,
		m_aabb->center.x - m_aabb->extents.x, m_aabb->center.y + m_aabb->extents.y, m_aabb->center.z + m_aabb->extents.z,
		m_aabb->center.x + m_aabb->extents.x, m_aabb->center.y - m_aabb->extents.y, m_aabb->center.z + m_aabb->extents.z,
		m_aabb->center.x - m_aabb->extents.x, m_aabb->center.y - m_aabb->extents.y, m_aabb->center.z + m_aabb->extents.z,

		m_aabb->center.x + m_aabb->extents.x, m_aabb->center.y + m_aabb->extents.y, m_aabb->center.z - m_aabb->extents.z,
		m_aabb->center.x - m_aabb->extents.x, m_aabb->center.y + m_aabb->extents.y, m_aabb->center.z - m_aabb->extents.z,
		m_aabb->center.x + m_aabb->extents.x, m_aabb->center.y - m_aabb->extents.y, m_aabb->center.z - m_aabb->extents.z,
		m_aabb->center.x - m_aabb->extents.x, m_aabb->center.y - m_aabb->extents.y, m_aabb->center.z - m_aabb->extents.z
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

GameEngine::GObject::~GObject()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void GameEngine::GObject::set_color(glm::vec3 c)
{
	m_color = c;
}

glm::vec3 GameEngine::GObject::get_color()
{
	return m_color;
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
		m_shader->setVec3("color", m_color);
		m_model->Draw(m_shader);
		if (m_aabb != nullptr && render_AABB)
		{
			m_shader->setVec3("color", { 1, 1, 1 });
			glBindVertexArray(VAO);
			glDrawArrays(GL_LINE_LOOP, 0, 36);
		}
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

void GameEngine::GObject::set_render_AABB(bool set)
{
	render_AABB = set;
}
