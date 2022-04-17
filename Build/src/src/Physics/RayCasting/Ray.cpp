#include "Physics/RayCasting/Ray.h"

GameEngine::Ray::Ray(const glm::vec3& position, const glm::vec3& direction) : m_rayStart(position), m_rayEnd(position), m_direction(direction) {}

void GameEngine::Ray::step(float scale)
{
    float yaw = glm::radians(m_direction.y + 90);
    float pitch = glm::radians(m_direction.x);

    auto& p = m_rayEnd;

    p.x -= glm::cos(yaw) * scale;
    p.z -= glm::sin(yaw) * scale;
    p.y -= glm::tan(pitch) * scale;
}

const glm::vec3& GameEngine::Ray::getEnd() const
{
    return m_rayEnd;
}

float GameEngine::Ray::getLength() const
{
    return glm::distance(m_rayStart, m_rayEnd);
}


