#pragma once

#include <vector>
#include <include/World/Chunk.h>

namespace GameEngine {

    class MasterRenderer;

	class World : IChunk
	{
	public:
		World();

        ChunkBlock  getBlock(int x, int y, int z) const             override;
        void        setBlock(int x, int y, int z, ChunkBlock block) override;

        void editBlock(int x, int y, int z, ChunkBlock block);

        void renderWorld(MasterRenderer& master);

        void addChunk(int x, int z);

    private:
        std::vector<Chunk>  m_chunks;
        std::vector<Chunk*> m_changedChunks;
	};
}
