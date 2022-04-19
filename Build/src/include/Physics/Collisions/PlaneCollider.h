#pragma once
#include <glm/glm.hpp>
#include "Physics/Collisions/Collider.h"
#include "Physics/RayCasting/Ray.h"

namespace GameEngine {

	class PlaneCollider : public Collider
	{
	public:
		PlaneCollider();
		~PlaneCollider();

		void SetCenter(glm::vec3 newCenter);
		void SetNormal(glm::vec3 newNormal);
		void SetSize(float newSize);

		float GetHalfWidth();

		bool CollidesWithRay(Ray ray);
		bool GetRayCollisionLocation(Ray ray, glm::vec3& location);

	private:
		bool GetRayToPlaneTValue(Ray& ray, float& t);

		glm::vec3 GetTransformedNormal();
		glm::vec3 GetTransformedCenter();

		glm::vec3 m_center;
		glm::vec3 m_normal;
		float m_size;

	};
}
