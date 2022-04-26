#include "World/ChunkMesh.h"

#include "World/WorldConstants.h"

using namespace GameEngine;

GameEngine::ChunkMesh::ChunkMesh()
{ }

void GameEngine::ChunkMesh::addFace(const std::vector<GLfloat>&blockFace, const std::vector<GLfloat>&textureCoords, const glm::ivec3 & chunkPosition, const glm::ivec3 & blockPosition)
{
    auto& verticies = m_mesh.vertexPositions;
    auto& texCoords = m_mesh.textureCoords;
    auto& indices = m_mesh.indices;

    texCoords.insert(texCoords.end(), textureCoords.begin(), textureCoords.end());

    for (int i = 0, index = 0; i < 4; ++i)
    {
        verticies.push_back(blockFace[index++] + chunkPosition.x * CHUNK_SIZE + blockPosition.x);
        verticies.push_back(blockFace[index++] + chunkPosition.y * CHUNK_SIZE + blockPosition.y);
        verticies.push_back(blockFace[index++] + chunkPosition.z * CHUNK_SIZE + blockPosition.z);
    }

    indices.insert(indices.end(),
        {
            m_indexIndex,
            m_indexIndex + 1,
            m_indexIndex + 2,

            m_indexIndex + 2,
            m_indexIndex + 3,
            m_indexIndex
        });
    m_indexIndex += 4;
}

void GameEngine::ChunkMesh::bufferMesh()
{
    //m_model.addData(m_mesh);

    m_mesh.vertexPositions.clear();
    m_mesh.textureCoords.clear();
    m_mesh.indices.clear();

    m_mesh.vertexPositions.shrink_to_fit();
    m_mesh.textureCoords.shrink_to_fit();
    m_mesh.indices.shrink_to_fit();

    m_indexIndex = 0;
}

const TileModel& GameEngine::ChunkMesh::getModel() const
{
    // TODO: вставьте здесь оператор return
    return m_model;
}

