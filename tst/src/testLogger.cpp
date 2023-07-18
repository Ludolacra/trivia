#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Utility/Logger.hpp"
#include "ut/Logger.hpp"

#include <memory>
#include <syslog.h>

namespace UT
{
    TEST( LoggerTest, smallerLvlDoesNotWriteLog )
    {
        Utility::Logger::Init( std::make_unique<Logger>() );

        Utility::Logger::SetLogLvl( Utility::Logger::Level::Critical );

        ERROR( "This won't appear as log" );
        CRIT( "This will" );

        EXPECT_CRIT( "This will" );
        EXPECT_NO_LOG();
    }

    TEST( LoggerTest, emptyFmtStringDoesNotWriteLog )
    {
        Utility::Logger::Init( std::make_unique<Logger>() );

        Utility::Logger::SetLogLvl( Utility::Logger::Level::Debug );

        ERROR( nullptr );

        EXPECT_NO_LOG();
    }
}
