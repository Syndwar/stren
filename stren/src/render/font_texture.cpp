#include "font_texture.h"

#include "SDL_ttf.h"

#include "colour.h"
#include "renderer.h"

namespace stren
{

FontTexture::GlyphSurface::GlyphSurface()
    : surface(nullptr)
    , glyph(0)
    , width(0)
    , height(0)
{
}

FontTexture::GlyphSurface::~GlyphSurface()
{
    SDL_FreeSurface(surface);
}

SDL_Surface * createSurace(const int width, const int height)
{
    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    return SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, rmask, gmask, bmask, amask);
}

FontTexture::FontTexture()
    : ITexture()
    , m_texture(nullptr)
    , m_size(0)
{
}

FontTexture::FontTexture(const std::string & filePath, const int size, const std::string & glyphs, const bool createEmpty)
    : ITexture()
    , m_filePath(filePath)
    , m_texture(nullptr)
    , m_size(size)
    , m_glyphs(glyphs)
{
    if (!createEmpty)
    {
        load();
    }
}

FontTexture::FontTexture(FontTexture && texture)
    : ITexture()
    , m_filePath(std::move(texture.m_filePath))
    , m_texture(texture.m_texture)
    , m_size(texture.m_size)
    , m_glyphs(std::move(texture.m_glyphs))
    , m_rects(std::move(texture.m_rects))
{
    texture.m_texture = nullptr;
    texture.m_size = 0;
}

FontTexture::~FontTexture()
{
    release();
}

FontTexture & FontTexture::operator=(FontTexture && texture)
{
    m_filePath = std::move(texture.m_filePath);
    m_texture = texture.m_texture;
    m_size = texture.m_size;
    m_glyphs = std::move(texture.m_glyphs);
    m_rects = std::move(texture.m_rects);

    texture.m_texture = nullptr;
    texture.m_size = 0;
    return *this;
}

void FontTexture::load()
{
    std::vector<GlyphSurface> surfaces;
    // render ttf fonts glyphs onto surfaces
    renderGlyphsToSurface(surfaces);
    // render surfaces onto single texture
    m_texture = createTexture(surfaces);
    // save characters positions on the texture
    saveCharsPlaceOnTexture(surfaces);
    // free glyph surfaces
    surfaces.clear();
}

void FontTexture::release()
{
    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
    }
}

SDL_Texture * FontTexture::createTexture(std::vector<GlyphSurface> & surfaces)
{
    // calculate texture size
    const int textureSize = calculateSurfaceSize(surfaces);
    // calculate glyphs position on the texture
    calculateGlyphPlaceOnTexture(surfaces, textureSize);
    // render surfaces on the single surface and create texture from it
    return createTextureFromSurfaces(surfaces, textureSize);;
}

void FontTexture::calculateGlyphPlaceOnTexture(std::vector<GlyphSurface> & surfaces, const int textureSize)
{
    int rulerX = 0; // tracks current x empty position on the fonts surface
    int rulerY = 0; // track current y empty position on the fonts surface
    int maxGlyphHeight = 0;

    for (GlyphSurface & surface : surfaces)
    {
        if (surface.height > maxGlyphHeight)
        {
            maxGlyphHeight = surface.height;
        }

        if (rulerX + surface.width >= textureSize)
        {
            rulerX = 0;
            rulerY += maxGlyphHeight;
        }

        surface.rect.set(rulerX, rulerY, surface.width, surface.height);
        rulerX += surface.width;
    }
}

void FontTexture::renderGlyphsToSurface(std::vector<GlyphSurface> & surfaces)
{
    char glyph[2];
    const SDL_Color sdlColour{ 255, 255, 255, 0 };
    // open ttf font for rendering glyphs
    if (TTF_Font * ttf_font = TTF_OpenFont(m_filePath.c_str(), m_size))
    {
        surfaces.clear();
        surfaces.resize(m_glyphs.size());
        for (size_t i = 0, i_end = m_glyphs.size(); i < i_end; ++i)
        {
            glyph[0] = m_glyphs[i];
            glyph[1] = '\0';

            if (SDL_Surface * surface = TTF_RenderText_Solid(ttf_font, glyph, sdlColour))
            {
                surfaces[i].surface = surface;
                surfaces[i].glyph = glyph[0];
                surfaces[i].width = surface->w;
                surfaces[i].height = surface->h;
            }
        }
        // close ttf font
        TTF_CloseFont(ttf_font);
    }
}

SDL_Texture * FontTexture::createTextureFromSurfaces(const std::vector<GlyphSurface> & surfaces, const int textureSize)
{
    SDL_Texture * texture(nullptr);
    // create empty surface
    if (SDL_Surface * fontSurface = createSurace(textureSize, textureSize))
    {
        // blit glyph surfaces onto single surface
        for (const GlyphSurface & surface : surfaces)
        {
            const Rect & rect = surface.rect;
            SDL_Rect dstRect = { rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight() };
            SDL_BlitSurface(surface.surface, nullptr, fontSurface, &dstRect);
        }

        if (SDL_Renderer * renderer = Renderer::instantiate())
        {
            // create texture from font surface and store it in the font
            texture = SDL_CreateTextureFromSurface(renderer, fontSurface);
        }

        // free font surface after all the symbols are rendered and the font texture created
        SDL_FreeSurface(fontSurface);
    }
    return texture;
}

void FontTexture::saveCharsPlaceOnTexture(std::vector<GlyphSurface> & surfaces)
{
    for (const GlyphSurface & surface : surfaces)
    {
        m_rects[surface.glyph] = surface.rect;
    }
}

const Rect & FontTexture::getGlyphRect(const char letter) const
{
    auto it = m_rects.find(letter);
    if (it != m_rects.end())
    {
        return it->second;
    }
    return Rect::getEmpty();
}

void FontTexture::render(const Rect & srcRect, const Rect & dstRect, const double angle, const int flip, const Point & center, const Colour & colour)
{
    SDL_Renderer * renderer = Renderer::instantiate();
    if (!renderer) return;
    
    if (!isLoaded())
    {
        load();
    }
    if (isLoaded())
    {
        Uint8 r, g, b;
        SDL_GetTextureColorMod(m_texture, &r, &g, &b);
        SDL_SetTextureColorMod(m_texture, (Uint8)colour.r(), (Uint8)colour.g(), (Uint8)colour.b());

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
            SDL_SetTextureColorMod(m_texture, r, g, b);
        }
    }
}

int FontTexture::getWidth() const
{
    int width(0);
    if (m_texture)
    {
        SDL_QueryTexture(m_texture, nullptr, nullptr, &width, nullptr);
    }
    return width;
}

int FontTexture::getHeight() const
{
    int height(0);
    if (m_texture)
    {
        SDL_QueryTexture(m_texture, nullptr, nullptr, nullptr, &height);
    }
    return height;
}

int FontTexture::calculateSurfaceSize(const std::vector<GlyphSurface> & surfaces)
{
    int texture_size = 16;
    int max_width = 0;
    int max_height = 0;
    const int amount = surfaces.size();
    // find maximum texture widths and heights

    if (amount)
    {
        for (const GlyphSurface & surface : surfaces)
        {
            if (surface.width > max_width)
            {
                max_width = surface.width;
            }
            if (surface.height > max_height)
            {
                max_height = surface.height;
            }
        }
        // calculate max number of columns and rows that can fit into the texture
        int cols = texture_size / max_width;
        int rows = texture_size / max_height;
        // if all elements can fit into the texture
        while (cols * rows < amount)
        {
            texture_size *= 2;
            cols = texture_size / max_width;
            rows = texture_size / max_height;
        }
    }

    return texture_size;
}
} // stren