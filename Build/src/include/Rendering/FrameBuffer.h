#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include "typedefs.h"

namespace GameEngine {

	struct FramebufferTextureConfig
	{
		int Attachment = GL_COLOR_ATTACHMENT0;
		int Target = GL_TEXTURE_2D;

		int InternalFormat = GL_RGBA32F;
		int Format = GL_RGBA;

		int MinFilter = GL_LINEAR;
		int MagFilter = GL_LINEAR;

		int WrapS = GL_NONE;
		int WrapT = GL_NONE;
		int WrapR = GL_NONE;

		int Type = GL_UNSIGNED_BYTE;

		bool Mipmap = false;
		bool Border = false;
	};

	struct FramebufferRenderbufferConfig
	{
		int Attachment = GL_DEPTH_STENCIL_ATTACHMENT;
		int InternalFormat = GL_DEPTH_STENCIL;
	};

	struct FrameBufferConfig {
		GLuint width = 1024;
		GLuint height = 1024;

		std::vector<FramebufferTextureConfig> Textures;
		std::vector<FramebufferRenderbufferConfig> Renderbuffers;
	};

	class FrameBuffer
	{
	private:
		GLuint m_ID;
		GLuint m_colorAttachment = 0;
		GLuint m_depthAttachment = 0;

		FrameBufferConfig m_config;

	public:
		
		static Ref<FrameBuffer> Create(const FrameBufferConfig& config);

		FrameBuffer(const FrameBufferConfig& config);
		virtual ~FrameBuffer();

		void Bind();

		void UpdateTarget(const FramebufferTextureConfig& textureConfig, int i = 0);

		void Unbind();

		void Resize(uint32_t width, uint32_t height);
		

		inline const FrameBufferConfig& GetConfiguration() const { return m_config; }

		inline uint32_t GetID() const { return m_ID; }
		inline uint32_t GetColorAttachment() const { return m_colorAttachment; }
		inline uint32_t GetDepthAttachment() const { return m_depthAttachment; }
		
	};
}
