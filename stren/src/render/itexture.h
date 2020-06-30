#ifndef STREN_ITEXTURE_H
#define STREN_ITEXTURE_H

namespace stren
{
class Colour;
class Rect;
class Point;
class FontTexture;
class ImageTexture;
///
/// Class ITexture is an interface to different Texture classes
///
class ITexture
{
public:
    ///
    /// load texture
    ///
    virtual void load() = 0;
    ///
    /// free texture
    ///
    virtual void release() = 0;
    ///
    /// return if the texture is loaded
    ///
    virtual bool isLoaded() const = 0;
    ///
    /// render texture,
    /// srcRect shows what part of the texture to render
    /// dstRect shows where on the screen to render
    ///
    virtual void render(const Rect & srcRect, const Rect & dstRect, const double angle, const int flip, const Point & center, const Colour & colour) = 0;
    ///
    /// returns texture width
    ///
    virtual int getWidth() const = 0;
    ///
    /// returns texture height
    ///
    virtual int getHeight() const = 0;
    ///
    /// converts ITexture to ImageTexture
    ///
    virtual ImageTexture * toImageTexture() { return nullptr; }
    ///
    /// converts ITexture to FontTexture
    ///
    virtual FontTexture * toFontTexture() { return nullptr; }
};
} // stren

#endif // STREN_ITEXTURE_H