#include "World/World.h"

#include "Rendering/MasterRenderer.h"
#include "World/WorldConstants.h"
#include <iostream>

constexpr int temp_worldSize = 8;

struct VectorXZ
{
    int x, z;
};

VectorXZ getBlockXZ(int x, int z)
{
    return
    {
        x % CHUNK_SIZE,
        z % CHUNK_SIZE
    };
}

VectorXZ getChunkXZ(int x, int z)
{
    return
    {
        x / CHUNK_SIZE,
        z / CHUNK_SIZE
    };
}

bool isOutOfBounds(const VectorXZ& chunkPos)
{
    if (chunkPos.x < 0) return true;
    if (chunkPos.z < 0) return true;
    if (chunkPos.x >= temp_worldSize) return true;
    if (chunkPos.z >= temp_worldSize) return true;
    return false;
}
/*
GameEngine::World::World()
{
    for (int x = 0; x < temp_worldSize; x++)
    {
        for (int z = 0; z < temp_worldSize; z++)
        {
            addChunk(x, z);
        }
    }

    for (auto& chunk : m_chunks)
    {
        chunk.makeMesh();
    }
}

ChunkBlock GameEngine::World::getBlock(int x, int y, int z) const
{
    return ChunkBlock();
}

void GameEngine::World::setBlock(int x, int y, int z, ChunkBlock block)
{
}

void GameEngine::World::editBlock(int x, int y, int z, ChunkBlock block)
{
}

*/
