#pragma once

#include <glm/glm.hpp>
#include <World/Model/TileModel.h>
#include <Shaders/Shader.h>
#include <Texture/BasicTexture.h>
#include <typedefs.h>

namespace GameEngine {

	class Camera;

	class QuadRenderer
	{
	public:
		QuadRenderer();
		void add(const glm::vec3& position);

		void renderQuads(const Ref<Camera> camera);

		void setShader(Ref<Shader> shader);

	private:
		std::vector<glm::vec3> m_quads;

		TileModel m_quadModel;
		Ref<Shader> m_shader;
		BasicTexture m_basicTexture;
	};
}
