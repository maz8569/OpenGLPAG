#pragma once

#include <glad/glad.h>
#include <string>

namespace GameEngine {

	class BasicTexture
	{
    public:
        BasicTexture() = default;
        BasicTexture(const std::string & file);

        ~BasicTexture();

        void loadFromFile(const std::string & file);

        void bindTexture() const;


    private:
        GLuint m_id;
	};

}
