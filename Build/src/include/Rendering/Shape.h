#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace GameEngine {
	enum class Coords
	{
		COORDS = 0,
		COORDSTEXT = 1,
		COORDSTEXTNORM = 2
	};

	class Shape
	{
	private:
		unsigned int VBO, VAO;

	public:

		Shape(Coords verts);

		void clean();
		void Render(int numb);
		void activateAttribs();
	};
}
