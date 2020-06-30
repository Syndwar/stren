#include "image_texture.h"

#include "SDL_render.h"
#include "SDL_image.h"

#include "renderer.h"

namespace stren
{

ImageTexture::ImageTexture()
    : ITexture()
    , m_texture(nullptr)
    , m_isAlphaBlend(false)
{
}

ImageTexture::ImageTexture(const std::string & path, const bool isAlphaBlend, const bool createEmpty)
    : ITexture()
    , m_texture(nullptr)
    , m_filePath(path)
    , m_isAlphaBlend(isAlphaBlend)
{
    if (!createEmpty)
    {
        load();
    }
}

ImageTexture::ImageTexture(ImageTexture && texture)
    : ITexture()
    , m_texture(texture.m_texture)
    , m_filePath(std::move(texture.m_filePath))
    , m_isAlphaBlend(texture.m_isAlphaBlend)
    , m_rect(std::move(texture.m_rect))
{
    texture.m_texture = nullptr;
}


ImageTexture::~ImageTexture()
{
    release();
}

ImageTexture & ImageTexture::operator=(ImageTexture && texture)
{
    m_texture = texture.m_texture;
    m_filePath = std::move(texture.m_filePath);
    m_rect = std::move(texture.m_rect);
    m_isAlphaBlend = texture.m_isAlphaBlend;

    texture.m_texture = nullptr;
    return *this;
}


void ImageTexture::load()
{
    SDL_Renderer * renderer = Renderer::instantiate();
    if (renderer && !m_texture && !m_filePath.empty())
    {
        if (SDL_Surface * surface = IMG_Load(m_filePath.c_str()))
        {
            m_texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
        }
    }
    if (m_texture)
    {
        int w = 0;
        int h = 0;
        SDL_QueryTexture(m_texture, nullptr, nullptr, &w, &h);
        m_rect.setSize(w, h);
    }
    if (m_isAlphaBlend)
    {
        if (m_texture)
        {
            SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
        }
    }
}

void ImageTexture::release()
{
    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
    }
}

void ImageTexture::render(const Rect & srcRect, const Rect & dstRect, const double angle, const int flip, const Point & center, const Colour & colour)
{
    if (SDL_Renderer * renderer = Renderer::instantiate())
    {
        if (!isLoaded())
        {
            load();
        }
        if (isLoaded())
        {
            const Rect & clippingRect = Renderer::getClippingRect();
            const Point & offset = Renderer::getOffset();
            const int alpha = Renderer::getAlpha();
            SDL_Rect sdldstrect{ dstRect.getX() - offset.getX(), dstRect.getY() - offset.getY(), dstRect.getWidth(), dstRect.getHeight() };
            if (clippingRect.isEmpty() || clippingRect.hasCommon(sdldstrect.x, sdldstrect.y, sdldstrect.w, sdldstrect.h))
            {
                SDL_Rect tempSrc{ srcRect.getX(), srcRect.getY(), srcRect.getWidth(), srcRect.getHeight() };
                SDL_Rect * sdlSrcRect = srcRect.isEmpty() ? nullptr : &tempSrc;
                SDL_Point sdlCenter{ center.getX(), center.getY() };

                SDL_SetTextureAlphaMod(m_texture, (Uint8)alpha);
                SDL_RenderCopyEx(renderer, m_texture, sdlSrcRect, &sdldstrect, angle, &sdlCenter, (SDL_RendererFlip)flip);
            }
        }
    }
}

int ImageTexture::getWidth() const
{
    int width(0);
    if (m_texture)
    {
        SDL_QueryTexture(m_texture, nullptr, nullptr, &width, nullptr);
    }
    return width;
}

int ImageTexture::getHeight() const
{
    int height(0);
    if (m_texture)
    {
        SDL_QueryTexture(m_texture, nullptr, nullptr, nullptr, &height);
    }
    return height;
}

} // stren