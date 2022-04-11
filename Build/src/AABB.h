#pragma once
#include <glm/glm.hpp>
#include <array>
#include <memory>
#include <Model.h>

namespace GameEngine {
	class AABB
	{
	public:
		glm::vec3 center{ 0.f, 0.f, 0.f };
		glm::vec3 extents{ 0.f, 0.f, 0.f };

		AABB(const glm::vec3& min, const glm::vec3& max);
		AABB(const glm::vec3& inCenter, float iI, float iJ, float iK);

		std::array<glm::vec3, 8> getVertice() const;

	};

	AABB generateAABB(std::shared_ptr<Model> model);
}
