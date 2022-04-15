#pragma once
#include <string>
#include "typedefs.h"
#include <vector>
#include <SceneGraph.h>

namespace GameEngine {
	class Scene
	{
	private:
		std::string name;
		Ref<SceneNode> root;
		std::vector<Ref<SceneNode>> GObjects;

	public:
		Scene();
	};
}

