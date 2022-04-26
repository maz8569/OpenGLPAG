#include "World/Model/TileModel.h"

using namespace GameEngine;
/*
GameEngine::TileModel::TileModel(const TileMesh& mesh)
{
	addData(mesh);
}
*/

GameEngine::TileModel::TileModel(const std::vector<GLfloat>& vertexPositions, const std::vector<GLfloat>& textureCoords, const std::vector<GLuint>& indices)
{
	addData(vertexPositions, textureCoords, indices);
}

GameEngine::TileModel::~TileModel()
{
	deleteData();
}
/*
GameEngine::TileModel::TileModel(TileModel&& other) 
	: m_vao(other.m_vao), m_vboCount(other.m_vboCount), m_indicesCount(other.m_indicesCount), m_buffers(std::move(other.m_buffers))
{
	other.m_vao = 0;
	other.m_vboCount = 0;
	other.m_indicesCount = 0;
}

TileModel& GameEngine::TileModel::operator=(TileModel&& other)
{
	m_vao = other.m_vao;
	m_vboCount = other.m_vboCount;
	m_indicesCount = other.m_indicesCount;
	m_buffers = std::move(other.m_buffers);

	other.m_vao = 0;
	other.m_vboCount = 0;
	other.m_indicesCount = 0;

	return *this;
}

void GameEngine::TileModel::addData(const TileMesh& mesh)
{
	if (m_vao != 0)
		deleteData();

	m_indicesCount = mesh.indices.size();

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	addVBO(3, mesh.vertexPositions);
	addVBO(2, mesh.textureCoords);
	addEBO(mesh.indices);
}
*/
void GameEngine::TileModel::addData(const std::vector<GLfloat>& vertexPositions, const std::vector<GLfloat>& textureCoords, const std::vector<GLuint>& indices)
{
	if (m_vao != 0)
		deleteData();

	m_indicesCount = indices.size();

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	addVBO(0, vertexPositions);
	addVBO(1, textureCoords);
	addEBO(indices);
}

void GameEngine::TileModel::deleteData()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(m_buffers.size(),
		m_buffers.data());

	m_buffers.clear();

	m_vboCount = 0;
	m_vao = 0;
	m_indicesCount = 0;
}

void GameEngine::TileModel::addVBO(int dimensions, const std::vector<GLfloat>& data)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		data.size() * sizeof(GLfloat),
		data.data(),
		GL_STATIC_DRAW);

	glVertexAttribPointer(m_vboCount,
		dimensions,
		GL_FLOAT,
		GL_FALSE,
		0,
		(GLvoid*)0);

	glEnableVertexAttribArray(m_vboCount++);

	m_buffers.push_back(vbo);
}

void GameEngine::TileModel::bindVAO() const
{
	glBindVertexArray(m_vao);
}

int GameEngine::TileModel::getIndicesCount() const
{
	return m_indicesCount;
}

void GameEngine::TileModel::addEBO(const std::vector<GLuint>& indices)
{
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		indices.size() * sizeof(GLuint),
		indices.data(),
		GL_STATIC_DRAW);
}
