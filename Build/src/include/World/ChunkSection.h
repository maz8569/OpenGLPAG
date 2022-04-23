#pragma once

#include <array>

#include <glm/glm.hpp>
#include "ChunkBlock.h"
#include "WorldConstants.h"
#include "ChunkMesh.h"
#include "IChunk.h"

namespace GameEngine {

	class World;

	class ChunkSection : public IChunk
	{
        friend class Chunk;
    public:
        ChunkSection(const glm::ivec3& position, World& world);

        void setBlock(int x, int y, int z, ChunkBlock block) override;
        ChunkBlock getBlock(int x, int y, int z) const override;

        const glm::ivec3 getLocation() const noexcept;

        bool hasMesh() const noexcept;


    private:
        glm::ivec3 toWorldPosition(int x, int y, int z) const;

        static bool outOfBounds(int value);
        static int  getIndex(int x, int y, int z);

        std::array<ChunkBlock, CHUNK_VOLUME>    m_blocks;
        ChunkMesh                               m_mesh;
        glm::ivec3                              m_location;

        World* m_pWorld;
        bool m_hasMesh = false;
	};

}
