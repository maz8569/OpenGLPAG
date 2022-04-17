#pragma once
#include <glm/glm.hpp>
#include <array>
#include "typedefs.h"
#include <Rendering/Model.h>

namespace GameEngine {
	class GObject;

	class AABB
	{
	public:
		GObject* parent;

		glm::vec3 center{ 0.f, 0.f, 0.f };
		glm::vec3 extents{ 0.f, 0.f, 0.f };

		AABB(const glm::vec3& min, const glm::vec3& max);
		AABB(const glm::vec3& inCenter, float iI, float iJ, float iK);
		~AABB();

		std::array<glm::vec3, 8> getVertice() const;

		glm::vec3 max();
		glm::vec3 min();

		glm::vec3 testDepth(Ref<AABB> other);
		float getSmallestDistance(Ref<AABB> other);
		bool collides(Ref<AABB> other) const;
	};

	AABB generateAABB(std::shared_ptr<Model> model);

}
