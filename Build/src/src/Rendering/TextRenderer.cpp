#include "Rendering/TextRenderer.h"

GameEngine::TextRenderer::TextRenderer(std::string fontPath, const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }
    else
    {
        if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
        {
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        }
        else
        {
            FT_Set_Pixel_Sizes(face, 0, m_size);

            if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            }
            else
            {
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

                for (unsigned char c = 0; c < 128; c++)
                {
                    // load character glyph 
                    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
                    {
                        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                        continue;
                    }
                    // generate texture
                    unsigned int texture;
                    glGenTextures(1, &texture);
                    glBindTexture(GL_TEXTURE_2D, texture);
                    glTexImage2D(
                        GL_TEXTURE_2D,
                        0,
                        GL_RED,
                        face->glyph->bitmap.width,
                        face->glyph->bitmap.rows,
                        0,
                        GL_RED,
                        GL_UNSIGNED_BYTE,
                        face->glyph->bitmap.buffer
                    );
                    // set texture options
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    // now store character for later use
                    Character character = {
                        texture,
                        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                        face->glyph->advance.x
                    };
                    Characters.insert(std::pair<char, Character>(c, character));
                }

                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

                FT_Done_Face(face);
                FT_Done_FreeType(ft);

                glGenVertexArrays(1, &GUI_VAO);
                glGenBuffers(1, &GUI_VBO);
                glBindVertexArray(GUI_VAO);
                glBindBuffer(GL_ARRAY_BUFFER, GUI_VBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindVertexArray(0);

                GUIShader = CreateRef<Shader>(vertexPath, fragmentPath, geometryPath);
                GUIShader->use();
                glm::mat4 ortho = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
                GUIShader->setMat4("projection", ortho);

                success = true;
            }
        }
    }
}

GameEngine::TextRenderer::~TextRenderer()
{
    clean();
}

void GameEngine::TextRenderer::RenderText(std::string text, float x, float y, float scale, glm::vec3 color)
{
    //FT_Set_Pixel_Sizes(face, 0, m_size);

    // activate corresponding render state	
    GUIShader->use();
    glUniform3f(glGetUniformLocation(GUIShader->ID, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(GUI_VAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, GUI_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GameEngine::TextRenderer::setSize(int size)
{
    m_size = size;
}

void GameEngine::TextRenderer::clean()
{
    glDeleteVertexArrays(1, &GUI_VAO);
    glDeleteBuffers(1, &GUI_VBO);
}
