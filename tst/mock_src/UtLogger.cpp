#include "ut/Logger.hpp"

#include <cstdio>
#include <iostream>

namespace UT
{
    Logger::ContainerType Logger::msLogContainer;

    void Logger::log( const Logger::Level lvl, const char* file, const char* function, const int line,
                      const char* formatStr, va_list args )
    {
        (void)file;
        (void)function;
        (void)line;

        std::array<char, 1000> buffer;

        vsnprintf( buffer.data(), buffer.max_size(), formatStr, args );

        msLogContainer[lvl].push_back( std::string( buffer.data() ) );
    }

    void Logger::Clear()
    {
        msLogContainer.clear();
    }

    ::testing::AssertionResult Logger::Expect( const Logger::Level lvl,
                                               const std::string& log )
    {
        if( msLogContainer.empty() || msLogContainer[lvl].empty() )
        {
            return ::testing::AssertionFailure()
                << "No log writings with level: " << LevelToString( lvl ) << "!"
                << "\n"
                << "Expected log writing not found: (" << LevelToString( lvl ) << " - " << log << ")";
        }

        auto it = std::find_if( msLogContainer[lvl].begin(),
                                msLogContainer[lvl].end(),
                                [&log]( const auto& e ) -> bool
                                {
                                    return std::string::npos != e.find( log );
                                } );

        if( msLogContainer[lvl].end() != it )
        {
            msLogContainer[lvl].erase( it );

            if( msLogContainer[lvl].empty() )
            {
                msLogContainer.erase( lvl );
            }

            return ::testing::AssertionSuccess();
        }

        return ::testing::AssertionFailure()
            << "Expected log writing not found: (" << LevelToString( lvl ) << " - " << log << ")";
    }

    ::testing::AssertionResult Logger::Empty()
    {
        if( msLogContainer.empty() )
        {
            return ::testing::AssertionSuccess();
        }

        auto result = ::testing::AssertionFailure();

        result << "Unexpected log writings: ";

        for( const auto& lvlContainer : msLogContainer )
        {
            for( const auto& mlog : lvlContainer.second )
            {
                result << "\n"
                       << LevelToString( lvlContainer.first ) << " - " << mlog;
            }
        }

        return result;
    }

    std::string Logger::LevelToString( const Logger::Level lvl )
    {
#define CASE( x ) \
    case Level::x: return #x
        switch( lvl )
        {
            CASE( Debug );
            CASE( Info );
            CASE( Warning );
            CASE( Error );
            CASE( Critical );
        }
#undef CASE
        return "Unknown";
    }
}
