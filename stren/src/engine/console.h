#ifndef STREN_CONSOLE_H
#define STREN_CONSOLE_H

#include "widgets/dialog.h"

namespace stren
{
class Label;
///
/// class Console
///
class Console : public Dialog
{
private:
    size_t                   index_;  ///< current label index
    std::vector<std::string> stack_;  ///< messages stack
    std::vector<Label *> labels_;     ///< labels with messages
public:
    ///
    /// Constructor
    ///
    Console(const std::string & id);
    ///
    /// Destructor
    ///
    virtual ~Console();
    ///
    /// store message in the console and render it on screen
    ///
    void log(const std::string & message);
};

} // stren

#endif // STREN_CONSOLE_H
