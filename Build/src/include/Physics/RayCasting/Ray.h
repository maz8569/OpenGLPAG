#pragma once
#include "glm/glm.hpp"

namespace GameEngine {
	class Ray
	{
	public:
		glm::vec3 m_rayStart;
		glm::vec3 m_rayEnd;
		glm::vec3 m_direction;

		Ray(const glm::vec3& position, const glm::vec3& direction);

		void step(float scale);

		const glm::vec3& getEnd() const;

		float getLength() const;
	};
}

