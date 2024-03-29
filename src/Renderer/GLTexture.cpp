#include "Renderer/GLTexture.h"

#include "Common.h"
#include <stdexcept>

using namespace Renderer::Internal;

namespace Renderer
{
    static GLfloat blackBorder[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    
    void GLTexture::InitNew(uint32_t width, uint32_t height)
    {
        if(index != 0) glDeleteTextures(1, &index);
        
        glCreateTextures(GL_TEXTURE_2D, 1, &index);
        glTextureStorage2D(index, 1, GL_RGBA8, width, height);
        
        if(GLenum err = glGetError(); err != GL_NO_ERROR)
        {
            std::string msg = glErrMsg(err);
            while((err = glGetError()) != GL_NO_ERROR)
            {
                msg += "\n" + glErrMsg(err);
            }
            throw std::runtime_error(msg);
        }
        
        glTextureParameteri(index, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTextureParameteri(index, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTextureParameterfv(index, GL_TEXTURE_BORDER_COLOR, blackBorder);
        glTextureParameteri(index, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(index, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        if(GLenum err = glGetError(); err != GL_NO_ERROR)
        {
            std::string msg = glErrMsg(err);
            while((err = glGetError()) != GL_NO_ERROR)
            {
                msg += "\n" + glErrMsg(err);
            }
            throw std::runtime_error(msg);
        }
    }
    
    void GLTexture::UpdateRGBA8(const uint32_t * data, uint32_t width, uint32_t height)
    {
        if(index == 0 || width != this->width || height != this->height)
        {
            LoadRGBA8(data, width, height);
        }
        else
        {
            glTextureSubImage2D(index, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, (const void*)data);
            glCheckErrors();
        }
    }
    
    void GLTexture::LoadRGBA8(const uint32_t * data, uint32_t width, uint32_t height)
    {
        if(index != 0) glDeleteTextures(1, &index);
        
        glCreateTextures(GL_TEXTURE_2D, 1, &index);
        glTextureStorage2D(index, 1, GL_RGBA8, width, height);
        
        
        if(GLenum err = glGetError(); err != GL_NO_ERROR)
        {
            std::string msg = glErrMsg(err);
            while((err = glGetError()) != GL_NO_ERROR)
            {
                msg += "\n" + glErrMsg(err);
            }
            throw std::runtime_error(msg);
        }
        
        glTextureSubImage2D(index, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, (const void*)data);
        
        glTextureParameteri(index, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTextureParameteri(index, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTextureParameterfv(index, GL_TEXTURE_BORDER_COLOR, blackBorder);
        glTextureParameteri(index, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(index, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        glCheckErrors();
    }
}
