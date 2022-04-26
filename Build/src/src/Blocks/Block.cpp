#include "Blocks/Block.h"

bool GameEngine::Block::IsTransparent()
{
    if (m_blockType == BlockType::AIR)
        return true;
    return false;
}

bool GameEngine::Block::IsOpaque()
{
	if (m_blockType != BlockType::AIR)
		return true;
	return false;
}

GameEngine::BlockModel::BlockModel()
{
	AddVertex(glm::vec3(0, 0, 0), { 0, 0 });
	AddVertex(glm::vec3(1, 0, 1), { 0, 1 });
	AddVertex(glm::vec3(1, 1, 1), { 1, 1 });
	AddVertex(glm::vec3(0, 1, 0), { 1, 0 });
	AddVertex(glm::vec3(1, 0, 0), { 0, 0 });
	AddVertex(glm::vec3(0, 0, 1), { 0, 1 });
	AddVertex(glm::vec3(0, 1, 1), { 1, 1 });
	AddVertex(glm::vec3(1, 1, 0), { 1, 0 });
}

void GameEngine::BlockModel::AddVertex(const glm::vec3& pos, const i16Vec2 tex_coords)
{
	m_modelVertices.push_back({ pos, tex_coords });
}
