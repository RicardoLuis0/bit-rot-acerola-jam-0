#include "Renderer/GLFrameBuffer.h"

#include "Common.h"
#include <stdexcept>

using namespace Renderer::Internal;

namespace Renderer
{
    void GLFrameBuffer::Init(uint32_t _width, uint32_t _height)
    {
        
        glGenFramebuffers(1, &index);
        ResizeInternal(_width, _height);
        
    }
    
    void GLFrameBuffer::Resize(uint32_t _width, uint32_t _height)
    {
        glDeleteTextures(1, &colorTexture.index);
        colorTexture.index = 0;
        ResizeInternal(_width, _height);
    }
    
    void GLFrameBuffer::ResizeInternal(uint32_t _width, uint32_t _height)
    {
        
        width = _width;
        height = _height;
        colorTexture.InitNew(width, height);
        glBindFramebuffer(GL_FRAMEBUFFER, index);
        
        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture.index, 0);
        
        if(GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER); status != GL_FRAMEBUFFER_COMPLETE)
        {
            throw std::runtime_error("Failed to create/resize framebuffer, status: "+std::to_string(status));
        }
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}
