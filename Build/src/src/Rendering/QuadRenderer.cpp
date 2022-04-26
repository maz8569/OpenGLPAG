#include "Rendering/QuadRenderer.h"

#include <Scene/Camera.h>

GameEngine::QuadRenderer::QuadRenderer()
{
	m_basicTexture.loadFromFile("res/textures/torus.png");

    m_quadModel.addData(
        {
            -0.5,  0.5, 0,
             0.5,  0.5, 0,
             0.5, -0.5, 0,
            -0.5, -0.5, 0,
        },
        {
            0, 1,
            1, 1,
            1, 0,
            0, 0,
        },
        {
            0, 1, 2,
            2, 3, 0
        }
    );
}

void GameEngine::QuadRenderer::add(const glm::vec3& position)
{
    m_quads.push_back(position);
}

void GameEngine::QuadRenderer::renderQuads(const Ref<Camera> camera)
{
    m_shader->use();
    m_quadModel.bindVAO();
    m_basicTexture.bindTexture();

    m_shader->setMat4("projection", camera->m_projectionMatrix);
    m_shader->setMat4("view", camera->m_viewMatrix);

    for (auto& quad : m_quads)
    {
        glm::mat4 model(1.0f);
        model = glm::translate(model, quad);
        m_shader->setMat4("model", model);

        glDrawElements(GL_TRIANGLES, m_quadModel.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
    }

    m_quads.clear();
}

void GameEngine::QuadRenderer::setShader(Ref<Shader> shader)
{
    m_shader = shader;
}
