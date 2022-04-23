#pragma once

#include "BlockId.h"

namespace GameEngine {

	class BlockData;
	class BlockType;

	class ChunkBlock
	{
        ChunkBlock() = default;

        ChunkBlock(Block_t id);
        ChunkBlock(BlockId id);

        const BlockData& getData() const;
        const BlockType& getType() const;

        bool operator ==(ChunkBlock other);

        bool operator !=(ChunkBlock other);

        Block_t id = 0;
	};

}
