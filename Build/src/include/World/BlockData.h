#pragma once
#include <glm/glm.hpp>
#include <string>

namespace GameEngine {

	struct BlockDataHolder
	{
		glm::ivec2 texTopCoord;
		glm::ivec2 texSideCoord;
		glm::ivec2 texBottomCoord;
	};
	
	class BlockData
	{
	public:
		BlockData(const std::string& fileName);

		const BlockDataHolder& getBlockData() const;

	private:
		BlockDataHolder m_data;
	};

}