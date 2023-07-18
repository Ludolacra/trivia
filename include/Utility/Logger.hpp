#ifndef UTILITY_LOGGER_HPP_
#define UTILITY_LOGGER_HPP_

#include <cstdarg>
#include <memory>
#include <mutex>

#define DEBUG( ... ) Utility::Logger::Log( Utility::Logger::Level::Debug, __FILE__, __func__, __LINE__, __VA_ARGS__ )
#define INFO( ... )  Utility::Logger::Log( Utility::Logger::Level::Info, __FILE__, __func__, __LINE__, __VA_ARGS__ )
#define ERROR( ... ) Utility::Logger::Log( Utility::Logger::Level::Error, __FILE__, __func__, __LINE__, __VA_ARGS__ )
#define WARN( ... )  Utility::Logger::Log( Utility::Logger::Level::Warn, __FILE__, __func__, __LINE__, __VA_ARGS__ )
#define CRIT( ... )  Utility::Logger::Log( Utility::Logger::Level::Critical, __FILE__, __func__, __LINE__, __VA_ARGS__ )

namespace Utility
{
    class Logger
    {
    public:
        enum class Level
        {
            Debug = 0,
            Info,
            Warning,
            Error,
            Critical
        };

        static void Init( std::unique_ptr<Logger> instance );
        static void Destroy();
        static void SetLogLvl( const Level newLvl );

        inline Logger()   = default;
        virtual ~Logger() = default;

        static void Log( const Level loglvl, const char* file, const char* function, const int line,
                         const char* formatStr, va_list args );
        static void Log( const Level loglvl, const char* file, const char* function, const int line,
                         const char* formatStr, ... );

    protected:
        virtual void log( const Level loglvl, const char* file, const char* function, const int line,
                          const char* formatStr, va_list args ) = 0;

    private:
        typedef std::unique_ptr<Logger> Singleton;

        Logger( const Logger& )            = delete;
        Logger& operator=( const Logger& ) = delete;
        bool operator==( const Logger& )   = delete;

        static Level msLogLvl;
        static std::mutex msLock;
        static std::unique_ptr<Logger> msInstance;
    };

    class NullLogger : public Logger
    {
    protected:
        virtual void log( const Level loglvl, const char* file, const char* function, const int line,
                          const char* formatStr, va_list args ) override;
    };

    class CoutLogger : public Logger
    {
    protected:
        virtual void log( const Level loglvl, const char* file, const char* function, const int line,
                          const char* formatStr, va_list args ) override;
    };
}

#endif // UTILITY_LOGGER_HPP_
