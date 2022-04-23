#pragma once

#include <memory>
#include <array>

#include "BlockType.h"
#include "BlockId.h"

#include "Utils/Singleton.h"

#include "Texture/TextureAtlas.h"

namespace GameEngine {

	class BlockDatabase : public Singleton
	{
    public:
        static BlockDatabase& get();

        const BlockType& getBlock(BlockId id) const;
        const BlockData& getData(BlockId id) const;

        TextureAtlas textureAtlas;

    private:
        BlockDatabase();

        std::array<std::unique_ptr<BlockType>,
            (unsigned)BlockId::NUM_TYPES> m_blocks;
	};

}
