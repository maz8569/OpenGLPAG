#pragma once

#include <typedefs.h>
#include <glm/glm.hpp>
#include <array>
#include "LayerMesh.h"
#include <Rendering/Frustum.h>

namespace GameEngine {

	enum class LayerMeshState : std::uint8_t
	{
		Built = 0,
		Unbuilt,
		error
	};

	enum class LayerState
	{
		Ungenerated = 5,
		Generated,
		Changed,
		undefined
	};

	class Layer {
	public:

		Layer(const glm::vec3 layer_position);
		~Layer();

		void SetBlock(BlockType type, const glm::vec3& position);

		int GetTorchLightAt(int x, int y, int z);
		void SetTorchLightAt(int x, int y, int z, int light_val);

		void Construct();
		LayerMesh* GetLayerMesh();

		Block* GetBlock(int x, int y, int z);

		const glm::vec3 m_Position;
		LayerMeshState m_MeshState;
		LayerState m_ChunkState = LayerState::Ungenerated;
		std::array<std::array<std::array<Block, CHUNK_SIZE_X>, CHUNK_SIZE_Y>, CHUNK_SIZE_Z> m_LayerContents;
		FrustumAABB m_LayerFrustumAABB;

	private:
		LayerMesh m_LayerMesh;
	};

}
