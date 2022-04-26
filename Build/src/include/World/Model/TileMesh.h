#pragma once

#include <vector>
#include <glad/glad.h>

namespace GameEngine {

	struct TileMesh
	{
		std::vector<GLfloat> vertexPositions;
		std::vector<GLfloat> textureCoords;
		std::vector<GLuint>  indices;
	};

}