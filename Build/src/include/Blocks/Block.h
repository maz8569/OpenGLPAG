#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <typedefs.h>
#include <vector>

namespace GameEngine {

	enum BlockFaceType
	{
		top = 0,
		bottom,
		left,
		right,
		front,
		backward
	};

	enum BlockType : std::uint8_t {
		AIR = 0,
		GRASS = 1,
		WATER = 2
	};

	struct  Block
	{
        BlockType m_blockType = BlockType::AIR;
        bool IsTransparent();
		bool IsOpaque();

	};

	struct BlockVertex
	{
		glm::vec3 position;
		i16Vec2 tex_coords;
	};

	class BlockModel {
	public:
		std::vector<BlockVertex> m_modelVertices;

		BlockModel();

		void AddVertex(const glm::vec3& pos, const i16Vec2 tex_coords);
	};

}