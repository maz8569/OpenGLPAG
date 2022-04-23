#pragma once
#include "BlockData.h"

namespace GameEngine {

	class BlockType
	{
	public:
		BlockType(const std::string& fileName);
		virtual ~BlockType() = default;

		const BlockData& getData() const;

	private:
		BlockData m_data;
	};

	class DefaultBlock : public BlockType
	{
	public:
		DefaultBlock(const std::string& fileName);
	};
}
