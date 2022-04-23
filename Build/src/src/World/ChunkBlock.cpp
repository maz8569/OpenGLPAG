#include "World/ChunkBlock.h"

#include "World/BlockDatabase.h"

using namespace GameEngine;

GameEngine::ChunkBlock::ChunkBlock(Block_t id) : id(id)
{
}

GameEngine::ChunkBlock::ChunkBlock(BlockId id) : id(static_cast<Block_t>(id))
{
}

const BlockData& GameEngine::ChunkBlock::getData() const
{
    // TODO: вставьте здесь оператор return
    return BlockDatabase::get().getData((BlockId)id);
}

const BlockType& GameEngine::ChunkBlock::getType() const
{
    // TODO: вставьте здесь оператор return
    return BlockDatabase::get().getBlock((BlockId)id);
}

bool GameEngine::ChunkBlock::operator==(ChunkBlock other)
{
    return id == other.id;
}

bool GameEngine::ChunkBlock::operator!=(ChunkBlock other)
{
    return id != other.id;
}
