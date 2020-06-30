#ifndef STREN_TEXTS_REPOSITORY_H
#define STREN_TEXTS_REPOSITORY_H

#include <map>
#include "string_ext.h"

namespace stren
{
///
/// class TextsRepository
///
class TextsRepository
{
private:
    bool                               m_isReady; ///< flag if repository is loaded and ready
    std::map<std::string, std::string> m_texts;   ///< loaded texts
public:
    ///
    /// Constructor
    ///
    TextsRepository();
    ///
    /// returns required text
    ///
    const std::string & getText(const std::string & alias) const;
    ///
    /// initialize texts repository
    ///
    bool initialize();
    ///
    /// free loaded texts
    ///
    void release();
};

} // stren

#endif // STREN_TEXTS_REPOSITORY_H
