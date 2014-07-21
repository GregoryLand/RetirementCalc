#ifndef RETIREMENT_CALC_EXCEPTIONS_HEADER
#define RETIREMENT_CALC_EXCEPTIONS_HEADER
#include <exception>

namespace RetirementCalc
{
    // Relevant Exceptions
    class FileEmpty : public std::runtime_error
    {
    public:
        FileEmpty( const std::string& info ) : std::runtime_error( "FileEmpty" ), errorInfo{ info }
        {
        }

        std::string errorInfo;
    };
    class FileNotFound : public std::runtime_error
    {
    public:
        FileNotFound( const std::string& info ) : std::runtime_error( "FileNotFound" ), errorInfo{ info }
        {
        }

        std::string errorInfo;
    };
    class BadArgument : public std::logic_error
    {
    public:
        BadArgument( const std::string& info ) : std::logic_error( "BadArgument" ), errorInfo{ info }
        {
        }

        std::string errorInfo;
    };
}

#endif // RETIREMENT_CALC_EXCEPTIONS_HEADER
