#include "Physics/Collisions/PlaneCollider.h"

GameEngine::PlaneCollider::PlaneCollider()
{
	m_normal = { 0, 1, 0 };
	m_center = { 0, 0 ,0 };
	m_size = 1;
}

GameEngine::PlaneCollider::~PlaneCollider()
{
}

void GameEngine::PlaneCollider::SetCenter(glm::vec3 newCenter)
{
	m_center = newCenter;
}

void GameEngine::PlaneCollider::SetNormal(glm::vec3 newNormal)
{
	m_normal = newNormal;
}

void GameEngine::PlaneCollider::SetSize(float newSize)
{
	m_size = newSize;
}

bool GameEngine::PlaneCollider::CollidesWithRay(Ray ray)
{
	float t = 0;
	if (GetRayToPlaneTValue(ray, t)) {
		glm::vec3 location = (ray.m_direction * t) + ray.m_rayStart;

		//glm::vec4 inverseLocation 
	}
	
	return false;
}

bool GameEngine::PlaneCollider::GetRayToPlaneTValue(Ray& ray, float& t)
{
	float dotRayNormal = glm::dot(m_normal, ray.m_direction);

	if (dotRayNormal > 1e-6 || dotRayNormal < -(1e-6))
	{
		glm::vec3 rayOriginToPlaneCenter = m_center - ray.m_rayStart;

		t = glm::dot(rayOriginToPlaneCenter, m_normal) / dotRayNormal;

		if (t >= 0) {
			return true;
		}
	}
	
	return false;
}
