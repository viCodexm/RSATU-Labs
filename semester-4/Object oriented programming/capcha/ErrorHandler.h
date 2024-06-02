#include <string>
#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

class ErrorHandler
{
public:
    ErrorHandler();

    void callErrorPopup(const std::string& error_message) const;
    void logError(const std::string& error_message) const;
};

#endif // ERRORHANDLER_H
