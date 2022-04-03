#pragma once
#include <memory>
#include <vector>
#include <Collision.h>
#include "SceneGraph.h"

namespace GameEngine {
	class GObject: public SceneNode
	{
	private:
		std::vector<std::shared_ptr<Collision>> collisions;
	public:
		GObject();
	};
}


