#pragma once
#include <string>
#include <memory>
#include <vector>
#include <SceneGraph.h>

namespace GameEngine {
	class Scene
	{
	private:
		std::string name;
		std::shared_ptr<SceneNode> root;
		std::vector<SceneNode> GObjects;

	public:

	};
}

