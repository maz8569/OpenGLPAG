#pragma once

#include "NonCopyable.h"
#include "NonMovable.h"

namespace GameEngine {

	class Singleton : public NonMovable, public NonCopyable
	{

	};

}