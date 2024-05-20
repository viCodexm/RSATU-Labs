#include <string>
#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

class ErrorHandler
{
public:
    ErrorHandler();

    void callPopup(const std::string& error_message);
    void logError(const std::string& error_message);
};

#endif // ERRORHANDLER_H
