#include "World/BlockDatabase.h"

using namespace GameEngine;

BlockDatabase& GameEngine::BlockDatabase::get()
{
    static BlockDatabase d;
    return d;
}

const BlockType& GameEngine::BlockDatabase::getBlock(BlockId id) const
{
    return *m_blocks[(int)id];
}

const BlockData& GameEngine::BlockDatabase::getData(BlockId id) const
{
    return m_blocks[(int)id]->getData();
}

GameEngine::BlockDatabase::BlockDatabase() : textureAtlas("DefaultPack")
{
    m_blocks[(int)BlockId::Air] = std::make_unique<DefaultBlock>("Air");
    m_blocks[(int)BlockId::Grass] = std::make_unique<DefaultBlock>("Grass");
    m_blocks[(int)BlockId::Water] = std::make_unique<DefaultBlock>("Water");
}
