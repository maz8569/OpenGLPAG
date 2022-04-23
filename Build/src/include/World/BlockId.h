#pragma once

#include <cstdint>

using Block_t = uint8_t;

namespace GameEngine {

	enum class BlockId : Block_t
	{
		Air = 0,
		Grass,
		Water,

		NUM_TYPES
	};
}
