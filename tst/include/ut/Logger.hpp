#ifndef UT_LOGGER_HPP_
#define UT_LOGGER_HPP_

#include <gtest/gtest.h>

#include <cstdarg>
#include <string>

#include "Utility/Logger.hpp"

#define EXPECT_DBG( log ) \
    GTEST_ASSERT_( UT::Logger::Expect( Utility::Logger::Level::Debug, log ), GTEST_NONFATAL_FAILURE_ )

#define EXPECT_INFO( log ) \
    GTEST_ASSERT_( UT::Logger::Expect( Utility::Logger::Level::Info, log ), GTEST_NONFATAL_FAILURE_ )

#define EXPECT_WARN( log ) \
    GTEST_ASSERT_( UT::Logger::Expect( Utility::Logger::Level::Warn, log ), GTEST_NONFATAL_FAILURE_ )

#define EXPECT_ERROR( log ) \
    GTEST_ASSERT_( UT::Logger::Expect( Utility::Logger::Level::Error, log ), GTEST_NONFATAL_FAILURE_ )

#define EXPECT_CRIT( log ) \
    GTEST_ASSERT_( UT::Logger::Expect( Utility::Logger::Level::Critical, log ), GTEST_NONFATAL_FAILURE_ )

#define EXPECT_NO_LOG() \
    GTEST_ASSERT_( UT::Logger::Empty(), GTEST_NONFATAL_FAILURE_ )

#define CLEAR_LOGS() \
    UT::Logger::Clear()

namespace UT
{
    class Logger : public Utility::Logger
    {
    public:
        typedef std::map<Utility::Logger::Level, std::vector<std::string>> ContainerType;
        static ::testing::AssertionResult Expect( const Logger::Level lvl, const std::string& log );
        static ::testing::AssertionResult Empty();
        static void Clear();

    protected:
        void log( const Logger::Level logLvl, const char* file, const char* function, const int line,
                  const char* formatStr, va_list args ) override;

        static ContainerType msLogContainer;

    private:
        static std::string LevelToString( const Logger::Level lvl );
    };
}

#endif // UT_LOGGER_HPP_
