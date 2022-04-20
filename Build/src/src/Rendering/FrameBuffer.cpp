#include "Rendering/FrameBuffer.h"
using namespace GameEngine;

Ref<FrameBuffer> GameEngine::FrameBuffer::Create(const FrameBufferConfig& config)
{
    return CreateRef<FrameBuffer>(config);
}

GameEngine::FrameBuffer::FrameBuffer(const FrameBufferConfig& config): m_config(config)
{
    Resize(m_config.width, m_config.height);
}

GameEngine::FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &m_ID);
    glDeleteTextures(1, &m_colorAttachment);
    glDeleteRenderbuffers(1, &m_depthAttachment);
}

void GameEngine::FrameBuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
    glViewport(0, 0, m_config.width, m_config.height);
}

void GameEngine::FrameBuffer::UpdateTarget(const FramebufferTextureConfig& textureConfig, int i)
{
    glFramebufferTexture2D(GL_FRAMEBUFFER, textureConfig.Attachment, textureConfig.Target + i, m_colorAttachment, 0);
}

void GameEngine::FrameBuffer::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GameEngine::FrameBuffer::Resize(uint32_t width, uint32_t height)
{

    m_config.width = width;
    m_config.height = height;

	if (m_ID)
	{
		glDeleteFramebuffers(1, &m_ID);
		glDeleteTextures(1, &m_colorAttachment);
		glDeleteRenderbuffers(1, &m_depthAttachment);
	}

	glGenFramebuffers(1, &m_ID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

	if (m_config.Textures.size())
	{
		for (auto& textureConfig : m_config.Textures)
		{
			uint32_t* attachment;
			if (textureConfig.Attachment == GL_COLOR_ATTACHMENT0)
			{
				attachment = &m_colorAttachment;
			}
			else if (textureConfig.Attachment = GL_DEPTH_ATTACHMENT)
			{
				attachment = &m_depthAttachment;
			}

			glGenTextures(1, attachment);
			glBindTexture(textureConfig.Target, *attachment);
			glTexImage2D(textureConfig.Target, 0, textureConfig.InternalFormat, m_config.width, m_config.height, 0, textureConfig.Format, textureConfig.Type, nullptr);

			glTexParameteri(textureConfig.Target, GL_TEXTURE_MIN_FILTER, textureConfig.MinFilter);
			glTexParameteri(textureConfig.Target, GL_TEXTURE_MAG_FILTER, textureConfig.MagFilter);

			if (textureConfig.WrapS != GL_NONE && textureConfig.WrapT != GL_NONE)
			{
				glTexParameteri(textureConfig.Target, GL_TEXTURE_WRAP_S, textureConfig.WrapS);
				glTexParameteri(textureConfig.Target, GL_TEXTURE_WRAP_T, textureConfig.WrapT);
			}

			if (textureConfig.Border)
			{
				float border[] = { 1.0f, 1.0f, 1.0f, 1.0f };
				glTexParameterfv(textureConfig.Target, GL_TEXTURE_BORDER_COLOR, border);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, textureConfig.Attachment, textureConfig.Target, *attachment, 0);
		}
	}

	if (!m_colorAttachment)
	{
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}

	if (m_config.Renderbuffers.size())
	{
		for (auto& renderbufferConfig : m_config.Renderbuffers)
		{
			glGenRenderbuffers(1, &m_depthAttachment);
			glBindRenderbuffer(GL_RENDERBUFFER, m_depthAttachment);
			glRenderbufferStorage(GL_RENDERBUFFER, renderbufferConfig.InternalFormat, m_config.width, m_config.height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, renderbufferConfig.Attachment, GL_RENDERBUFFER, m_depthAttachment);
		}
	}

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer is incomplete!" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
