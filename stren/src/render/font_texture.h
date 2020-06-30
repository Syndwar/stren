#ifndef STREN_FONT_TEXTURE_H
#define STREN_FONT_TEXTURE_H

#include <map>
#include <vector>

#include "itexture.h"
#include "rect.h"

struct SDL_Texture;
struct SDL_Surface;

namespace stren
{
///
/// Class FontTexture, holds path to the texture, pointer to the loaded Texture.
/// Class loads texture if it is not loaded, can free if it is no longer needed.
///
class FontTexture : public ITexture
{
private:
    SDL_Texture *           m_texture;   ///< texture itself
    int                     m_size;      ///< font size
    std::string             m_glyphs;    ///< characters that font have
    std::string             m_filePath;  ///< path to the font file
    std::map<char, Rect>    m_rects;     ///< positions of the characters on the font texture

    class GlyphSurface
    {
    public:
        char            glyph;      ///< @todo
        int             width;      ///< @todo
        int             height;     ///< @todo
        SDL_Surface *   surface;    ///< @todo
        Rect            rect;       ///< @todo
        ///
        /// Default constructor
        ///
        GlyphSurface();
        ///
        /// Destructor
        ///
        ~GlyphSurface();
    };

public:
    ///
    /// Constructor
    ///
    FontTexture();
    ///
    /// Constructor
    ///
    FontTexture(const std::string & filePath, const int size, const std::string & glyphs, const bool createEmpty = false);
    ///
    /// Copy Constructor
    ///
    FontTexture(const FontTexture & texture) = delete;
    ///
    /// Move Constructor
    ///
    FontTexture(FontTexture && texture);
    ///
    /// Destructor
    ///
    virtual ~FontTexture();
    ///
    /// Copy assign operator
    ///
    FontTexture & operator=(const FontTexture & texture) = delete;
    ///
    /// Move assign operator
    ///
    FontTexture & operator=(FontTexture && texture);
    ///
    /// load texture
    ///
    virtual void load() override;
    ///
    /// free texture
    ///
    virtual void release() override;
    ///
    /// return if the texture is loaded
    ///
    virtual bool isLoaded() const override { return nullptr != m_texture; }
    ///
    /// render texture,
    /// srcRect shows what part of the texture to render
    /// dstRect shows where on the screen to render
    ///
    virtual void render(const Rect & srcRect, const Rect & destRect, const double angle, const int flip, const Point & center, const Colour & colour) override;
    ///
    /// @todo
    ///
    virtual FontTexture * toFontTexture() { return this; }
    ///
    /// @todo
    ///
    virtual int getWidth() const override;
    ///
    /// @todo
    ///
    virtual int getHeight() const override;
    ///
    /// @todo
    ///
    const Rect & getGlyphRect(const char letter) const;
private:
    ///
    /// @todo
    ///
    void renderGlyphsToSurface(std::vector<GlyphSurface> & surfaces);
    ///
    /// @todo
    ///
    int calculateSurfaceSize(const std::vector<GlyphSurface> & surfaces);
    ///
    /// @todo
    ///
    SDL_Texture * createTexture(std::vector<GlyphSurface> & surfaces);
    ///
    /// @todo
    ///
    void calculateGlyphPlaceOnTexture(std::vector<GlyphSurface> & surfaces, const int textureSize);
    ///
    /// @todo
    ///
    SDL_Texture * createTextureFromSurfaces(const std::vector<GlyphSurface> & surfaces, const int textureSize);
    ///
    /// @todo
    ///
    void saveCharsPlaceOnTexture(std::vector<GlyphSurface> & surfaces);
};

} // stren

#endif // STREN_FONT_TEXTURE_H