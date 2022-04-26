#pragma once

#include <glad/glad.h>

namespace GameEngine {

	struct VertexArray
	{
		VertexArray();
		~VertexArray();

		void Bind();
		void Unbind();
		
		GLuint array_id;
		GLenum type;
	};

}
