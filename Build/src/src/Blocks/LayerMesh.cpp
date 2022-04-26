#include "Blocks/LayerMesh.h"
#include "Blocks/Layer.h"

using namespace GameEngine;

GameEngine::LayerMesh::LayerMesh() : m_VBO(GL_ARRAY_BUFFER), m_TransparentVBO(GL_ARRAY_BUFFER), m_ModelVBO(GL_ARRAY_BUFFER)
{
	static bool IndexBufferInitialized = false;

	// Static index buffer
	static IndexBuffer StaticIBO;

	if (IndexBufferInitialized == false)
	{
		IndexBufferInitialized = true;

		GLuint* IndexBuffer = nullptr;

		int index_size = CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z * 6;
		int index_offset = 0;

		IndexBuffer = new GLuint[index_size * 6];

		for (size_t i = 0; i < index_size; i += 6)
		{
			IndexBuffer[i] = 0 + index_offset;
			IndexBuffer[i + 1] = 1 + index_offset;
			IndexBuffer[i + 2] = 2 + index_offset;
			IndexBuffer[i + 3] = 2 + index_offset;
			IndexBuffer[i + 4] = 3 + index_offset;
			IndexBuffer[i + 5] = 0 + index_offset;

			index_offset = index_offset + 4;
		}

		StaticIBO.BufferData(index_size * 6 * sizeof(GLuint), IndexBuffer, GL_STATIC_DRAW);

		delete[] IndexBuffer;
	}

	m_VAO.Bind();
	m_VBO.Bind();
	StaticIBO.Bind();
	m_VBO.VertexAttribIPointer(0, 3, GL_UNSIGNED_BYTE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	m_VBO.VertexAttribIPointer(1, 2, GL_UNSIGNED_SHORT, sizeof(Vertex), (void*)offsetof(Vertex, texture_coords));
	m_VBO.VertexAttribIPointer(2, 1, GL_UNSIGNED_BYTE, sizeof(Vertex), (void*)offsetof(Vertex, lighting_level));
	m_VBO.VertexAttribIPointer(3, 1, GL_UNSIGNED_BYTE, sizeof(Vertex), (void*)offsetof(Vertex, block_face_lighting));
	m_VAO.Unbind();

	m_TransparentVAO.Bind();
	m_TransparentVBO.Bind();
	StaticIBO.Bind();
	m_TransparentVBO.VertexAttribIPointer(0, 3, GL_UNSIGNED_BYTE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	m_TransparentVBO.VertexAttribIPointer(1, 2, GL_UNSIGNED_SHORT, sizeof(Vertex), (void*)offsetof(Vertex, texture_coords));
	m_TransparentVBO.VertexAttribIPointer(2, 1, GL_UNSIGNED_BYTE, sizeof(Vertex), (void*)offsetof(Vertex, lighting_level));
	m_TransparentVBO.VertexAttribIPointer(3, 1, GL_UNSIGNED_BYTE, sizeof(Vertex), (void*)offsetof(Vertex, block_face_lighting));
	m_TransparentVAO.Unbind();

	m_ModelVAO.Bind();
	m_ModelVBO.Bind();
	StaticIBO.Bind();
	m_ModelVBO.VertexAttribIPointer(0, 3, GL_UNSIGNED_BYTE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	m_ModelVBO.VertexAttribIPointer(1, 2, GL_UNSIGNED_SHORT, sizeof(Vertex), (void*)offsetof(Vertex, texture_coords));
	m_ModelVBO.VertexAttribIPointer(2, 1, GL_UNSIGNED_BYTE, sizeof(Vertex), (void*)offsetof(Vertex, lighting_level));
	m_ModelVBO.VertexAttribIPointer(3, 1, GL_UNSIGNED_BYTE, sizeof(Vertex), (void*)offsetof(Vertex, block_face_lighting));
	m_ModelVAO.Unbind();

	// Set the values of the 2D planes

	m_ForwardFace[0] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	m_ForwardFace[1] = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
	m_ForwardFace[2] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_ForwardFace[3] = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);

	m_BackFace[0] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_BackFace[1] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	m_BackFace[2] = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
	m_BackFace[3] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

	m_TopFace[0] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	m_TopFace[1] = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
	m_TopFace[2] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_TopFace[3] = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);

	m_BottomFace[0] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_BottomFace[1] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	m_BottomFace[2] = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
	m_BottomFace[3] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	m_LeftFace[0] = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
	m_LeftFace[1] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	m_LeftFace[2] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_LeftFace[3] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	m_RightFace[0] = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_RightFace[1] = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
	m_RightFace[2] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	m_RightFace[3] = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
}

GameEngine::LayerMesh::~LayerMesh()
{
	m_Vertices.clear();
}

bool GameEngine::LayerMesh::ConstructMesh(Layer* layer, const glm::vec3& chunk_pos)
{
	LayerDataTypePtr ChunkData = &layer->m_LayerContents;

	glm::vec3 world_position;
	glm::vec3 local_position;
	m_Vertices.clear();

	LayerDataTypePtr ForwardChunkData = m_GetLayerDataForMeshing(static_cast<int>(chunk_pos.x), static_cast<int>(chunk_pos.z + 1));
	LayerDataTypePtr BackwardChunkData = m_GetLayerDataForMeshing(static_cast<int>(chunk_pos.x), static_cast<int>(chunk_pos.z - 1));
	LayerDataTypePtr RightChunkData = m_GetLayerDataForMeshing(static_cast<int>(chunk_pos.x + 1), static_cast<int>(chunk_pos.z));
	LayerDataTypePtr LeftChunkData = m_GetLayerDataForMeshing(static_cast<int>(chunk_pos.x - 1), static_cast<int>(chunk_pos.z));

	if (ForwardChunkData && BackwardChunkData && RightChunkData && LeftChunkData)
	{
		for (int x = 0; x < CHUNK_SIZE_X; x++)
		{
			for (int y = 0; y < CHUNK_SIZE_Y; y++)
			{
				for (int z = 0; z < CHUNK_SIZE_Z; z++)
				{
					if (ChunkData->at(x).at(y).at(z).m_blockType != BlockType::AIR)
					{
						Block* block = &ChunkData->at(x).at(y).at(z);

						// To fix chunk edge mesh building issues, both faces are added if it is in the edge

						world_position.x = chunk_pos.x * CHUNK_SIZE_X + x;
						world_position.y = 0 * CHUNK_SIZE_Y + y;
						world_position.z = chunk_pos.z * CHUNK_SIZE_Z + z;
						local_position = glm::vec3(x, y, z);

						if (z <= 0)
						{
							if (block->IsTransparent())
							{
								if (BackwardChunkData->at(x).at(y).at(CHUNK_SIZE_Z - 1).IsTransparent() &&
									BackwardChunkData->at(x).at(y).at(CHUNK_SIZE_Z - 1).m_blockType != block->m_blockType)
								{
									AddFace(layer, BlockFaceType::front, local_position, block->m_blockType, 0, false);
									AddFace(layer, BlockFaceType::backward, local_position, block->m_blockType, 0, false);
								}

								else if (ChunkData->at(x).at(y).at(1).IsTransparent() &&
									ChunkData->at(x).at(y).at(1).m_blockType != block->m_blockType)
								{
									AddFace(layer, BlockFaceType::front, local_position, block->m_blockType, 0, false);
									AddFace(layer, BlockFaceType::backward, local_position, block->m_blockType, 0, false);
								}
							}

							else
							{
								if (BackwardChunkData->at(x).at(y).at(CHUNK_SIZE_Z - 1).IsOpaque() == false)
								{
									AddFace(layer, BlockFaceType::front, local_position, block->m_blockType, 0);
									AddFace(layer, BlockFaceType::backward, local_position, block->m_blockType, 0);
								}

								else if (ChunkData->at(x).at(y).at(1).IsOpaque() == false)
								{
									AddFace(layer, BlockFaceType::front, local_position, block->m_blockType, 0);
									AddFace(layer, BlockFaceType::backward, local_position, block->m_blockType, 0);
								}
							}
						}

						else if (z >= CHUNK_SIZE_Z - 1)
						{
							if (block->IsTransparent())
							{
								if (ForwardChunkData->at(x).at(y).at(0).IsTransparent() &&
									ForwardChunkData->at(x).at(y).at(0).m_blockType != block->m_blockType)
								{
									AddFace(layer, BlockFaceType::front, local_position, block->m_blockType, 0, false);
									AddFace(layer, BlockFaceType::backward, local_position, block->m_blockType, 0, false);
								}

								else if (ChunkData->at(x).at(y).at(CHUNK_SIZE_Z - 2).IsTransparent() &&
									ChunkData->at(x).at(y).at(CHUNK_SIZE_Z - 2).m_blockType != block->m_blockType)
								{
									AddFace(layer, BlockFaceType::front, local_position, block->m_blockType, 0, false);
									AddFace(layer, BlockFaceType::backward, local_position, block->m_blockType, 0, false);
								}
							}

							else
							{
								if (ForwardChunkData->at(x).at(y).at(0).IsOpaque() == false)
								{
									AddFace(layer, BlockFaceType::front, local_position, block->m_blockType, 0);
									AddFace(layer, BlockFaceType::backward, local_position, block->m_blockType, 0);
								}

								else if (ChunkData->at(x).at(y).at(CHUNK_SIZE_Z - 2).IsOpaque() == false)
								{
									AddFace(layer, BlockFaceType::front, local_position, block->m_blockType, 0);
									AddFace(layer, BlockFaceType::backward, local_position, block->m_blockType, 0);
								}
							}
						}

						else
						{
							if (block->IsTransparent())
							{
								if (ChunkData->at(x).at(y).at(z + 1).IsTransparent() &&
									ChunkData->at(x).at(y).at(z + 1).m_blockType != block->m_blockType)
								{
									AddFace(layer, BlockFaceType::front, local_position, block->m_blockType, 0, false);
								}

								if (ChunkData->at(x).at(y).at(z - 1).IsTransparent() &&
									ChunkData->at(x).at(y).at(z - 1).m_blockType != block->m_blockType)
								{
									AddFace(layer, BlockFaceType::backward, local_position, block->m_blockType, 0, false);
								}
							}

							else
							{
								//If the forward block is an air block, add the forward face to the mesh
								if (ChunkData->at(x).at(y).at(z + 1).IsOpaque() == false)
								{
									AddFace(layer, BlockFaceType::front, local_position, block->m_blockType, 0);
								}

								// If the back (-forward) block is an air block, add the back face to the mesh
								if (ChunkData->at(x).at(y).at(z - 1).IsOpaque() == false)
								{
									AddFace(layer, BlockFaceType::backward, local_position, block->m_blockType, 0);
								}
							}
						}

						if (x <= 0)
						{
							if (block->IsTransparent())
							{
								if (LeftChunkData->at(CHUNK_SIZE_X - 1).at(y).at(z).IsTransparent() &&
									LeftChunkData->at(CHUNK_SIZE_X - 1).at(y).at(z).m_blockType != block->m_blockType)
								{
									AddFace(layer, BlockFaceType::left, local_position, block->m_blockType, 0, false);
									AddFace(layer, BlockFaceType::right, local_position, block->m_blockType, 0, false);
								}

								else if (ChunkData->at(1).at(y).at(z).IsTransparent() &&
									ChunkData->at(1).at(y).at(z).m_blockType != block->m_blockType)
								{
									AddFace(layer, BlockFaceType::right, local_position, block->m_blockType, 0, false);
									AddFace(layer, BlockFaceType::left, local_position, block->m_blockType, 0, false);
								}

							}

							else
							{
								if (LeftChunkData->at(CHUNK_SIZE_X - 1).at(y).at(z).IsOpaque() == false)
								{
									AddFace(layer, BlockFaceType::left, local_position, block->m_blockType, 0);
									AddFace(layer, BlockFaceType::right, local_position, block->m_blockType, 0);
								}

								else if (ChunkData->at(1).at(y).at(z).IsOpaque() == false)
								{
									AddFace(layer, BlockFaceType::right, local_position, block->m_blockType, 0);
									AddFace(layer, BlockFaceType::left, local_position, block->m_blockType, 0);
								}
							}
						}

						else if (x >= CHUNK_SIZE_X - 1)
						{
							if (block->IsTransparent())
							{
								if (RightChunkData->at(0).at(y).at(z).IsTransparent() &&
									RightChunkData->at(0).at(y).at(z).m_blockType != block->m_blockType)
								{
									AddFace(layer, BlockFaceType::left, local_position, block->m_blockType, 0, false);
									AddFace(layer, BlockFaceType::right, local_position, block->m_blockType, 0, false);
								}

								else if (ChunkData->at(CHUNK_SIZE_X - 2).at(y).at(z).IsTransparent() &&
									ChunkData->at(CHUNK_SIZE_X - 2).at(y).at(z).m_blockType != block->m_blockType)
								{
									AddFace(layer, BlockFaceType::left, local_position, block->m_blockType, 0, false);
									AddFace(layer, BlockFaceType::right, local_position, block->m_blockType, 0, false);
								}
							}

							else
							{
								if (RightChunkData->at(0).at(y).at(z).IsOpaque() == false)
								{
									AddFace(layer, BlockFaceType::left, local_position, block->m_blockType, 0);
									AddFace(layer, BlockFaceType::right, local_position, block->m_blockType, 0);
								}

								else if (ChunkData->at(CHUNK_SIZE_X - 2).at(y).at(z).IsOpaque() == false)
								{
									AddFace(layer, BlockFaceType::left, local_position, block->m_blockType, 0);
									AddFace(layer, BlockFaceType::right, local_position, block->m_blockType, 0);
								}
							}

						}

						else
						{
							if (block->IsTransparent())
							{
								if (ChunkData->at(x + 1).at(y).at(z).IsTransparent() &&
									ChunkData->at(x + 1).at(y).at(z).m_blockType != block->m_blockType)
								{
									AddFace(layer, BlockFaceType::right, local_position, block->m_blockType, 0, false);
								}

								if (ChunkData->at(x - 1).at(y).at(z).IsTransparent() &&
									ChunkData->at(x - 1).at(y).at(z).m_blockType != block->m_blockType)
								{
									AddFace(layer, BlockFaceType::left, local_position, block->m_blockType, 0, false);
								}
							}

							else
							{
								// If the next block is an air block, add the right face to the mesh
								if (ChunkData->at(x + 1).at(y).at(z).IsOpaque() == false)
								{
									AddFace(layer, BlockFaceType::right, local_position, block->m_blockType, 0);
								}

								// If the previous block is an air block, add the left face to the mesh
								if (ChunkData->at(x - 1).at(y).at(z).IsOpaque() == false)
								{
									AddFace(layer, BlockFaceType::left, local_position, block->m_blockType, 0);
								}
							}
						}

						if (y <= 0)
						{
							if (ChunkData->at(x).at(y + 1).at(z).IsOpaque() == false)
							{
								AddFace(layer, BlockFaceType::bottom, local_position, block->m_blockType, 0);
							}
						}

						else if (y >= CHUNK_SIZE_Y - 1)
						{
							AddFace(layer, BlockFaceType::top, local_position, block->m_blockType, 0);
						}

						else
						{
							if (block->IsTransparent())
							{
								if (ChunkData->at(x).at(y - 1).at(z).IsTransparent() &&
									ChunkData->at(x).at(y - 1).at(z).m_blockType != block->m_blockType)
								{
									AddFace(layer, BlockFaceType::bottom, local_position, block->m_blockType, 0, false);
								}

								if (ChunkData->at(x).at(y + 1).at(z).IsTransparent() &&
									ChunkData->at(x).at(y + 1).at(z).m_blockType != block->m_blockType)
								{
									AddFace(layer, BlockFaceType::top, local_position, block->m_blockType, 0, false);
								}
							}

							else
							{
								// If the top block is an air block, add the top face to the mesh
								if (ChunkData->at(x).at(y - 1).at(z).IsOpaque() == false)
								{
									AddFace(layer, BlockFaceType::bottom, local_position, block->m_blockType, 0);
								}

								// If the bottom block is an air block, add the top face to the mesh
								if (ChunkData->at(x).at(y + 1).at(z).IsOpaque() == false)
								{
									AddFace(layer, BlockFaceType::top, local_position, block->m_blockType, 0);
								}
							}
						}
					}
				}
			}
		}

		// Upload the data to the GPU whenever the mesh is reconstructed

		m_VerticesCount = 0;
		m_TransparentVerticesCount = 0;
		m_ModelVerticesCount = 0;

		if (m_Vertices.size() > 0)
		{
			m_VBO.BufferData(this->m_Vertices.size() * sizeof(Vertex), &this->m_Vertices.front(), GL_STATIC_DRAW);
			m_VerticesCount = m_Vertices.size();
			m_Vertices.clear();
		}

		if (m_TransparentVertices.size() > 0)
		{
			m_TransparentVBO.BufferData(this->m_TransparentVertices.size() * sizeof(Vertex), &this->m_TransparentVertices.front(), GL_STATIC_DRAW);
			m_TransparentVerticesCount = m_TransparentVertices.size();
			m_TransparentVertices.clear();
		}

		if (m_ModelVertices.size() > 0)
		{
			m_ModelVBO.BufferData(this->m_ModelVertices.size() * sizeof(Vertex), &this->m_ModelVertices.front(), GL_STATIC_DRAW);
			m_ModelVerticesCount = m_ModelVertices.size();
			m_ModelVertices.clear();
		}

		return true;
	}

	return false;
}

void GameEngine::LayerMesh::AddFace(Layer* layer, BlockFaceType face_type, const glm::vec3& position, BlockType type, uint8_t light_level, bool buffer)
{
	glm::vec4 translation = glm::vec4(position, 0.0f); // No need to create a model matrix. 
// Adding the position to the translation will do the samething but much much faster

	Vertex v1, v2, v3, v4;

	// To fix a face culling issue. I inverted the vertices for the left, front and bottom face so the winding order will be correct
	bool reverse_texture_coordinates = false;

	// Order
	// Top, bottom, front, back, left, right
	static const uint8_t lighting_levels[6] = { 10, 3, 6, 7, 6, 7 };

	switch (face_type)
	{
	case BlockFaceType::top:
	{

		v1.position = translation + m_TopFace[0];
		v2.position = translation + m_TopFace[1];
		v3.position = translation + m_TopFace[2];
		v4.position = translation + m_TopFace[3];

		// Set the lighting level for the vertex
		v1.lighting_level = light_level;
		v2.lighting_level = light_level;
		v3.lighting_level = light_level;
		v4.lighting_level = light_level;

		v1.block_face_lighting = light_level;
		v2.block_face_lighting = light_level;
		v3.block_face_lighting = light_level;
		v4.block_face_lighting = light_level;

		break;
	}

	case BlockFaceType::bottom:
	{
		v1.position = translation + m_BottomFace[3];
		v2.position = translation + m_BottomFace[2];
		v3.position = translation + m_BottomFace[1];
		v4.position = translation + m_BottomFace[0];

		// Set the lighting level for the vertex
		v1.lighting_level = light_level;
		v2.lighting_level = light_level;
		v3.lighting_level = light_level;
		v4.lighting_level = light_level;

		v1.block_face_lighting = lighting_levels[1];
		v2.block_face_lighting = lighting_levels[1];
		v3.block_face_lighting = lighting_levels[1];
		v4.block_face_lighting = lighting_levels[1];

		reverse_texture_coordinates = true;

		break;
	}

	case BlockFaceType::front:
	{
		v1.position = translation + m_ForwardFace[3];
		v2.position = translation + m_ForwardFace[2];
		v3.position = translation + m_ForwardFace[1];
		v4.position = translation + m_ForwardFace[0];

		// Set the lighting level for the vertex
		v1.lighting_level = light_level;
		v2.lighting_level = light_level;
		v3.lighting_level = light_level;
		v4.lighting_level = light_level;

		v1.block_face_lighting = lighting_levels[2];
		v2.block_face_lighting = lighting_levels[2];
		v3.block_face_lighting = lighting_levels[2];
		v4.block_face_lighting = lighting_levels[2];

		reverse_texture_coordinates = true;

		break;
	}

	case BlockFaceType::backward:
	{
		v1.position = translation + m_BackFace[0];
		v2.position = translation + m_BackFace[1];
		v3.position = translation + m_BackFace[2];
		v4.position = translation + m_BackFace[3];

		v1.lighting_level = light_level;
		v2.lighting_level = light_level;
		v3.lighting_level = light_level;
		v4.lighting_level = light_level;

		v1.block_face_lighting = lighting_levels[3];
		v2.block_face_lighting = lighting_levels[3];
		v3.block_face_lighting = lighting_levels[3];
		v4.block_face_lighting = lighting_levels[3];

		break;
	}

	case BlockFaceType::left:
	{
		v1.position = translation + m_LeftFace[3];
		v2.position = translation + m_LeftFace[2];
		v3.position = translation + m_LeftFace[1];
		v4.position = translation + m_LeftFace[0];

		v1.lighting_level = light_level;
		v2.lighting_level = light_level;
		v3.lighting_level = light_level;
		v4.lighting_level = light_level;

		v1.block_face_lighting = lighting_levels[4];
		v2.block_face_lighting = lighting_levels[4];
		v3.block_face_lighting = lighting_levels[4];
		v4.block_face_lighting = lighting_levels[4];

		reverse_texture_coordinates = true;

		break;
	}

	case BlockFaceType::right:
	{
		v1.position = translation + m_RightFace[0];
		v2.position = translation + m_RightFace[1];
		v3.position = translation + m_RightFace[2];
		v4.position = translation + m_RightFace[3];

		v1.lighting_level = light_level;
		v2.lighting_level = light_level;
		v3.lighting_level = light_level;
		v4.lighting_level = light_level;

		v1.block_face_lighting = lighting_levels[5];
		v2.block_face_lighting = lighting_levels[5];
		v3.block_face_lighting = lighting_levels[5];
		v4.block_face_lighting = lighting_levels[5];

		break;
	}

	default:
	{
		// Todo : Throw an error here
		break;
	}
	}

	if (reverse_texture_coordinates)
	{
		v1.texture_coords = { 1, 0 };
		v2.texture_coords = { 1, 1 };
		v3.texture_coords = { 0, 1 };
		v4.texture_coords = { 0, 0 };
	}

	else
	{
		v1.texture_coords = { 0, 0 };
		v2.texture_coords = { 0, 1 };
		v3.texture_coords = { 1, 1 };
		v4.texture_coords = { 1, 0};
	}

	if (buffer)
	{
		m_Vertices.push_back(v1);
		m_Vertices.push_back(v2);
		m_Vertices.push_back(v3);
		m_Vertices.push_back(v4);
	}

	else if (!buffer)
	{
		m_TransparentVertices.push_back(v1);
		m_TransparentVertices.push_back(v2);
		m_TransparentVertices.push_back(v3);
		m_TransparentVertices.push_back(v4);
	}
}


