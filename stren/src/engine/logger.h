#ifndef STREN_LOGGER_H
#define STREN_LOGGER_H

#include "common/string_ext.h"

namespace stren
{
///
/// class Logger
///
class Logger
{
private:
    static std::streamoff   m_writePos;                 ///< @todo
    static bool             m_isFileExist;              ///< @todo
    std::string             m_printColour;              ///< @todo

public:
    ///
    /// Constructor
    ///
    Logger(const char * colour);
    ///
    /// Copy Constructor
    ///
    Logger(const Logger & logger);
    ///
    /// Move Constructor
    ///
    Logger(Logger && logger);
    ///
    /// Destructor
    ///
    ~Logger();
    ///
    /// Copy Assign Operator
    ///
    Logger & operator=(const Logger & logger);
    ///
    /// Move Assign Operator
    ///
    Logger & operator=(Logger && logger);
    ///
    /// @todo
    ///
    Logger & operator <<(const char * data)
    {
        log(data);
        return *this;
    }
    ///
    /// @todo
    ///
    Logger & operator <<(const std::string & data)
    {
        log(data);
        return *this;
    }
    ///
    /// @todo
    ///
    Logger & operator <<(const int data)
    {
        log(data);
        return *this;
    }
    ///
    /// @todo
    ///
    inline void setColor(const char * color) { m_printColour = color; }
private:
    ///
    /// @todo
    ///
    void log(const char * data);
    ///
    /// @todo
    ///
    void log(const std::string & data);
    ///
    /// @todo
    ///
    void log(const int data);

};

} // stren


#endif // STREN_LOGGER_H