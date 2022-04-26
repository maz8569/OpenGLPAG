#pragma once

#include "typedefs.h"
#include "QuadRenderer.h"
#include "WindowManager.h"

namespace GameEngine {
	
	class Camera;
	
	class MasterRenderer
	{
	public: 
		void DrawQuad(const glm::vec3& pos);
		void finishRender(Ref<WindowManager> windowManager, Ref<Camera> camera);
		
		void setQuadShader(Ref<Shader> shader);

	private:
		QuadRenderer m_quadRenderer;

	};
}

