#include "Physics/Collisions/AABB.h"

GameEngine::AABB::AABB(const glm::vec3& min, const glm::vec3& max): center((max+min)*0.5f), extents(max.x - center.x, max.y - center.y, max.z - center.z) 
{
}

GameEngine::AABB::AABB(const glm::vec3& inCenter, float iI, float iJ, float iK): center(inCenter), extents(iI, iJ, iK)
{
}

GameEngine::AABB::~AABB()
{
}

std::array<glm::vec3, 8> GameEngine::AABB::getVertice() const
{
	std::array<glm::vec3, 8> vertice;
	vertice[0] = { center.x - extents.x, center.y - extents.y, center.z - extents.z };
	vertice[1] = { center.x + extents.x, center.y - extents.y, center.z - extents.z };
	vertice[2] = { center.x - extents.x, center.y + extents.y, center.z - extents.z };
	vertice[3] = { center.x + extents.x, center.y + extents.y, center.z - extents.z };
	vertice[4] = { center.x - extents.x, center.y - extents.y, center.z + extents.z };
	vertice[5] = { center.x + extents.x, center.y - extents.y, center.z + extents.z };
	vertice[6] = { center.x - extents.x, center.y + extents.y, center.z + extents.z };
	vertice[7] = { center.x + extents.x, center.y + extents.y, center.z + extents.z };
	return vertice;
}

glm::vec3 GameEngine::AABB::getMax()
{
	return center - extents[0] - extents[1] - extents[2];
}

glm::vec3 GameEngine::AABB::getMin()
{
	return center + extents[0] + extents[1] + extents[2];
}

glm::vec3 GameEngine::AABB::testDepth(Ref<AABB> other)
{
	glm::vec3 result = glm::vec3();

	for (int i = 0; i < 3; i++)
	{
		if (abs(center[i] - other->center[i]) > (extents[i] + other->extents[i]))
			result[i] = extents[i] + other->extents[i] - center[i] - other->center[i];
	}
	return result;
}

float GameEngine::AABB::getSmallestDistance(Ref<AABB> other)
{
	auto vec = testDepth(other);
	float result = vec[0] > vec[1] ? vec[1] : vec[0];
	return result;
}

bool GameEngine::AABB::collides(Ref<AABB> other) const
{
	for (int i = 0; i < 3; i++)
	{
		if (abs(center[i] - other->center[i]) > (extents[i] + other->extents[i]))
			return 0;
	}
	return 1;
}

bool GameEngine::AABB::pointVsAABB(glm::vec3 point)
{
	auto max = getMax();
	auto min = getMin();
	for (int i = 0; i < 3; i++)
	{
		if (!(point[i] >= min[i] && point[i] <= max[i]))
			return 0;
	}
	return 1;
}


GameEngine::AABB GameEngine::generateAABB(std::shared_ptr<Model> model)
{
	glm::vec3 minAABB = glm::vec3(std::numeric_limits<float>::max());
	glm::vec3 maxAABB = glm::vec3(std::numeric_limits<float>::min());
	for (auto&& mesh : model->meshes)
	{
		for (auto&& vertex : mesh.vertices)
		{
			minAABB.x = std::min(minAABB.x, vertex.Position.x);
			minAABB.y = std::min(minAABB.y, vertex.Position.y);
			minAABB.z = std::min(minAABB.z, vertex.Position.z);

			maxAABB.x = std::max(maxAABB.x, vertex.Position.x);
			maxAABB.y = std::max(maxAABB.y, vertex.Position.y);
			maxAABB.z = std::max(maxAABB.z, vertex.Position.z);
		}
	}
	return AABB(minAABB, maxAABB);
}
