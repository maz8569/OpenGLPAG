#include "Texture/TextureAtlas.h"

GameEngine::TextureAtlas::TextureAtlas(const std::string& textureFileName)
{
    loadFromFile(textureFileName);
    
    m_imageSize = 256;
    m_individualTextureSize = 16;
}

std::vector<GLfloat> GameEngine::TextureAtlas::getTexture(const glm::ivec2& coords)
{
    static const GLfloat TEX_PER_ROW = (GLfloat)m_imageSize / (GLfloat)m_individualTextureSize;
    static const GLfloat INDV_TEX_SIZE = 1.0f / TEX_PER_ROW;
    static const GLfloat PIXEL_SIZE = 1.0f / (float)m_imageSize;

    GLfloat xMin = (coords.x * INDV_TEX_SIZE) + 0.5 * PIXEL_SIZE;
    GLfloat yMin = (coords.y * INDV_TEX_SIZE) + 0.5 * PIXEL_SIZE;

    GLfloat xMax = (xMin + INDV_TEX_SIZE) - 0.5 * PIXEL_SIZE;
    GLfloat yMax = (yMin + INDV_TEX_SIZE) - 0.5 * PIXEL_SIZE;

    return
    {
        xMax, yMax,
        xMin, yMax,
        xMin, yMin,
        xMax, yMin
    };
}
