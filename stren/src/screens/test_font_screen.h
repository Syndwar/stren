#ifndef FONT_TEST_SCREEN_H
#define FONT_TEST_SCREEN_H

#include "widgets/screen.h"

namespace stren
{
class Glyph;
///
/// class TestFontScreen
///
class TestFontScreen : public Screen
{
private:
    std::string fontId_;    ///< @todo
    int         index_;     ///< @todo

public:
    ///
    /// Constructor
    ///
    TestFontScreen();
    ///
    /// Destructor
    ///
    virtual ~TestFontScreen();
    ///
    /// @todo
    ///
    void setFont(const std::string & fontId);
private:
    ///
    /// @todo
    ///
    virtual void doRender() override;
    ///
    /// @todo
    ///
    void onBackBtnClick();
    ///
    /// @todo
    ///
    void onChangeFontBtnClick();
};
} // stren
#endif // FONT_TEST_SCREEN_H
