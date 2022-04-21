#include "Scene/Courier.h"

GameEngine::Courier::Courier(Ref<MousePicker> mousePicker, Ref<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Collision> colMan) 
	: Entity(model, shader, colMan), m_mousePicker(mousePicker)
{
	m_inputManager = mousePicker->getInputManager();
	Entity::Update();
}

void GameEngine::Courier::render()
{
	Entity::render();
}

void GameEngine::Courier::Update()
{
	//if (get_transform().m_position.y > 10 || get_transform().m_position.y < -10)
		//speed *= -1;
	//get_transform().m_position.y += 0.01 * speed;
	//update(get_parent()->get_transform(), true);
	if (m_inputManager->m_isRclicked)
	{
		glm::vec3 start = m_mousePicker->getCameraPos();
		glm::vec3 dir = m_mousePicker->getCurrentRay();
		//std::cout << dir.x << " " << dir.y << " " << dir.z << " " << std::endl;


		glm::vec3 end = dir *10.f + start;

		get_transform().m_position = end;
		update(get_parent()->get_transform(), true);


		//std::cout << end.x << " " << end.y << " " << end.z << " " << std::endl;

	}


	Entity::Update();
}

void GameEngine::Courier::reactOnCollision(GObject* other)
{
	//std::cout << "end";
}
