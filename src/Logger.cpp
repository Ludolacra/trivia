#include "Utility/Logger.hpp"

#include <sstream>

namespace Utility
{
    Logger::Singleton Logger::msInstance( std::make_unique<NullLogger>() );
    Logger::Level Logger::msLogLvl( Logger::Level::Info );
    std::mutex Logger::msLock;

    void Logger::Init( std::unique_ptr<Logger> instance )
    {
        std::lock_guard<std::mutex> guard( msLock );
        msInstance.reset( instance.release() );
    }

    void Logger::Destroy()
    {
        std::lock_guard<std::mutex> guard( msLock );
        msInstance.reset( new NullLogger );
    }

    void Logger::SetLogLvl( const Logger::Level newLvl )
    {
        msLogLvl = newLvl;
    }

    void Logger::Log( const Logger::Level loglvl, const char* file, const char* function, const int line,
                      const char* formatStr, ... )
    {
        va_list list;
        va_start( list, formatStr );
        Log( loglvl, file, function, line, formatStr, list );
        va_end( list );
    }

    void Logger::Log( const Logger::Level loglvl, const char* file, const char* function, const int line,
                      const char* formatStr, va_list args )
    {
        if( !formatStr )
        {
            return;
        }

        std::lock_guard<std::mutex> gurad( msLock );
        if( msInstance.get() && msLogLvl <= loglvl )
        {
            msInstance->log( loglvl, file, function, line, formatStr, args );
        }
    }

    void CoutLogger::log( const Logger::Level loglvl, const char* file, const char* function, const int line,
                          const char* formatStr, va_list args )
    {
        (void)loglvl;
        (void)file;
        (void)function;
        (void)line;

        vprintf( formatStr, args );
        printf( "\n" );
    }

    void NullLogger::log( const Logger::Level loglvl, const char* file, const char* function, const int line,
                          const char* formatStr, va_list args )
    {
        (void)loglvl;
        (void)file;
        (void)function;
        (void)line;
        (void)formatStr;
        (void)args;
    }
}
