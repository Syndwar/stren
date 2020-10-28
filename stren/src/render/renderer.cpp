#include "renderer.h"

#include "SDL.h"

#include "common/colour.h"
#include "engine/app_window.h"
#include "engine/logger.h"

namespace stren
{

SDL_Renderer * Renderer::m_renderer = nullptr;
int Renderer::m_alpha = 255;
Point Renderer::m_offset = Point();
Rect Renderer::m_clippingRect = Rect();

Renderer::Renderer()
{
}

bool Renderer::initialize(AppWindow & appWindow, const bool vsync)
{
    int flags = SDL_RENDERER_ACCELERATED;
    if (vsync)
    {
        flags |= SDL_RENDERER_PRESENTVSYNC;
    }
    m_renderer = appWindow.createRenderer(-1, flags);
    return nullptr != m_renderer;
}

void Renderer::release()
{
    Logger("green") << "[Engine] Destroy SDL renderer";
    if (m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
}

void Renderer::setRenderColour(const Colour & colour)
{
    if (m_renderer)
    {
        SDL_SetRenderDrawColor(m_renderer, (Uint8)colour.r(), (Uint8)colour.g(), (Uint8)colour.b(), (Uint8)colour.a());
    }
}

Colour Renderer::getRenderColour()
{
    if (m_renderer)
    {
        Uint8 r, g, b, a;
        SDL_GetRenderDrawColor(m_renderer, &r, &g, &b, &a);
        return Colour(r, g, b, a);
    }
    return Colour();
}

void Renderer::clear()
{
    if (m_renderer)
    {
        SDL_RenderClear(m_renderer);
    }
}

void Renderer::render()
{
    if (m_renderer)
    {
        SDL_RenderPresent(m_renderer);
    }
}

void Renderer::setClippingRect(const Rect & rect)
{
    if (m_renderer)
    {
        m_clippingRect = rect;
        SDL_Rect sdlRect{ rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight() };
        SDL_RenderSetClipRect(m_renderer, &sdlRect);
    }
}
} // stren