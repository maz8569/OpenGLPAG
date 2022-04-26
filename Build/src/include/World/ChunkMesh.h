#pragma once

#include "Model/TileModel.h"
#include <glm/glm.hpp>
#include <vector>

namespace GameEngine {

	class ChunkMesh
	{
	public:
		ChunkMesh();

		void addFace(const std::vector<GLfloat>& blockFace,
			const std::vector<GLfloat>& textureCoords,
			const glm::ivec3& chunkPosition,
			const glm::ivec3& blockPosition);

		void bufferMesh();

		const TileModel& getModel() const;

	private:
		TileMesh  m_mesh;
		TileModel m_model;
		GLuint m_indexIndex = 0;

	};

}