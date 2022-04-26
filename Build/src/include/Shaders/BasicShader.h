#pragma once
#include "Shader.h"

namespace GameEngine {

	class BasicShader : public Shader
	{
	public:
		BasicShader(const std::string& vertexFile = "basic",
					const std::string& fragmentFile = "basic");

	};
}
