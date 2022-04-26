#pragma once

#include <glad/glad.h>

namespace GameEngine {


	class IndexBuffer
	{
	public:

		IndexBuffer();
		~IndexBuffer();

		void BufferData(GLsizeiptr size, void* data, GLenum usage);
		void Bind();
		void Unbind();


	private:

		GLuint buffer_id;
		GLenum type;
	};

}