#include "Rendering/MasterRenderer.h"

void GameEngine::MasterRenderer::DrawQuad(const glm::vec3& pos)
{
	m_quadRenderer.add(pos);
}

void GameEngine::MasterRenderer::finishRender(Ref<WindowManager> windowManager, Ref<Camera> camera)
{
	glClearColor(0.4f, 0.4f, 0.4f, 0.6f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
	m_quadRenderer.renderQuads(camera);


}

void GameEngine::MasterRenderer::setQuadShader(Ref<Shader> shader)
{
	m_quadRenderer.setShader(shader);
}
