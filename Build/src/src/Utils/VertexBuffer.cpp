#include "Utils/VertexBuffer.h"

using namespace GameEngine;

GameEngine::VertexBuffer::VertexBuffer(GLenum type)
{
	this->buffer_id = 0;
	this->type = type;
	glGenBuffers(1, &(this->buffer_id));
}

GameEngine::VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &(this->buffer_id));
	this->Unbind();
}

void GameEngine::VertexBuffer::BufferData(GLsizeiptr size, void* data, GLenum usage)
{
	this->Bind();
	glBufferData(this->type, size, data, usage);
}

void GameEngine::VertexBuffer::BufferSubData(GLintptr offset, GLsizeiptr size, void* data)
{
	this->Bind();
	(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
}

void GameEngine::VertexBuffer::Bind()
{
	glBindBuffer(this->type, buffer_id);
}

void GameEngine::VertexBuffer::Unbind()
{
	glBindBuffer(this->type, 0);
}

void GameEngine::VertexBuffer::VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer)
{
	this->Bind();
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	glEnableVertexAttribArray(index);
}

void GameEngine::VertexBuffer::VertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer)
{
	this->Bind();
	glVertexAttribIPointer(index, size, type, stride, pointer);
	glEnableVertexAttribArray(index);
}


