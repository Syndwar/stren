#ifndef STREN_IMAGE_TEXTURE_H
#define STREN_IMAGE_TEXTURE_H

#include "common/string_ext.h"
#include "common/rect.h"
#include "render/itexture.h"

struct SDL_Texture;

namespace stren
{
///
/// Class ImageTexture, holds path to the texture, pointer to the loaded Texture.
/// Class loads texture if it is not loaded, frees if it is no longer needed.
///
class ImageTexture : public ITexture
{
private:
    bool            m_isAlphaBlend;  ///< @todo
    Rect            m_rect;          ///< @todo
    SDL_Texture *   m_texture;       ///< texture itself
    std::string     m_filePath;      ///< path to the texture file 
public:
    enum Flip
    {
        None = 0x00000000,
        Horizontal = 0x00000001,
        Vertical = 0x00000002
    };                              ///< flip types
    ///
    /// Constructor
    ///
    ImageTexture();
    ///
    /// Constructor
    ///
    ImageTexture(const std::string & path, const bool isAlphaBlend, const bool createEmpty = false);
    ///
    /// Copy Constructor
    ///
    ImageTexture(const ImageTexture & texture) = delete;
    ///
    /// Move Constructor
    ///
    ImageTexture(ImageTexture && texture);
    ///
    /// Destructor
    ///
    virtual ~ImageTexture();
    ///
    /// Copy assign operator
    ///
    ImageTexture & operator=(const ImageTexture & texture) = delete;
    ///
    /// Move assign operator
    ///
    ImageTexture & operator=(ImageTexture && texture);
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
    virtual int getWidth() const override;
    ///
    /// @todo
    ///
    virtual int getHeight() const override;
    ///
    /// @todo
    ///
    virtual ImageTexture * toImageTexture() override { return this; }
};

} // stren

#endif // STREN_IMAGE_TEXTURE_H