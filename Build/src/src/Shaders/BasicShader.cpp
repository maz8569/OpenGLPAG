#include "Shaders/BasicShader.h"

GameEngine::BasicShader::BasicShader(const std::string& vertexFile, const std::string& fragmentFile) 
	: Shader(("res/shaders/" + vertexFile + ".vert").c_str(), ("res/shaders/" + fragmentFile + ".frag").c_str())
{
}
