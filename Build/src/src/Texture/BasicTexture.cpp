#include "Texture/BasicTexture.h"

#include <stb_image.h>
#include <stdio.h>
#include <iostream>

GameEngine::BasicTexture::BasicTexture(const std::string& file)
{
    loadFromFile(file);
}

GameEngine::BasicTexture::~BasicTexture()
{
	glDeleteTextures(1, &m_id);
}

void GameEngine::BasicTexture::loadFromFile(const std::string& file)
{
    glGenTextures(1, &m_id);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(file.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << file << std::endl;
        stbi_image_free(data);

    }
}

void GameEngine::BasicTexture::bindTexture() const
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}
