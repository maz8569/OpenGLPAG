#include "Utils/IndexBuffer.h"

GameEngine::IndexBuffer::IndexBuffer()
{
	this->buffer_id = 0;
	this->type = GL_ELEMENT_ARRAY_BUFFER;
	glGenBuffers(1, &(this->buffer_id));
	this->Bind();
}

GameEngine::IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &(this->buffer_id));
	this->Unbind();
}

void GameEngine::IndexBuffer::BufferData(GLsizeiptr size, void* data, GLenum usage)
{
	this->Bind();
	glBufferData(this->type, size, data, usage);
}

void GameEngine::IndexBuffer::Bind()
{
	glBindBuffer(this->type, buffer_id);
}

void GameEngine::IndexBuffer::Unbind()
{
	glBindBuffer(this->type, 0);
	glBindVertexArray(0);
}
