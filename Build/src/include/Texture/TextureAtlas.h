#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "BasicTexture.h"

namespace GameEngine {

	class TextureAtlas : public BasicTexture
	{
    public:
        TextureAtlas(const std::string& textureFileName);

        std::vector<GLfloat> getTexture(const glm::ivec2& coords);

    private:
        int m_imageSize;
        int m_individualTextureSize;
	};

}