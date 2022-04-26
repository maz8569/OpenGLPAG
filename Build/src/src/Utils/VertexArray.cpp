#include "Utils/VertexArray.h"

using namespace GameEngine;

GameEngine::VertexArray::VertexArray()
{
	this->array_id = 0;
	glGenVertexArrays(1, &(this->array_id));
	this->Bind();
}

GameEngine::VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &(this->array_id));
	this->Unbind();
}

void GameEngine::VertexArray::Bind()
{
	glBindVertexArray(this->array_id);
}

void GameEngine::VertexArray::Unbind()
{
	glBindVertexArray(0);
}
