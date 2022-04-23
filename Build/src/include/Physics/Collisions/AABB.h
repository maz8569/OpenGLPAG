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

		void updateCenter(glm::vec3& newLocation);
		void updateExtents(glm::vec3& newExtents);

		glm::vec3 getVN(const glm::vec3& normal) const;
		glm::vec3 getVP(const glm::vec3& normal) const;


		std::array<glm::vec3, 8> getVertice() const;

		glm::vec3 getMax();
		glm::vec3 getMin();

		glm::vec3 testDepth(Ref<AABB> other);
		float getSmallestDistance(Ref<AABB> other);
		bool collides(Ref<AABB> other) const;
		bool pointVsAABB(glm::vec3 point);
	};

	AABB generateAABB(std::shared_ptr<Model> model);

}
