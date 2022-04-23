#include "World/BlockType.h"

using namespace GameEngine;

GameEngine::BlockType::BlockType(const std::string& fileName) : m_data(fileName)
{
}

const BlockData& GameEngine::BlockType::getData() const
{
	// TODO: вставьте здесь оператор return
	return m_data;
}

GameEngine::DefaultBlock::DefaultBlock(const std::string& fileName)
	: BlockType(fileName)
{ }
