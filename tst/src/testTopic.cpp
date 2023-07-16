#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Game/Topic.hpp"

using namespace testing;

namespace UT
{
    TEST( TopicTest, checkStringRepresentations )
    {
        ASSERT_EQ( "Pop", to_string( Topic::Pop ) );
        ASSERT_EQ( "Science", to_string( Topic::Science ) );
        ASSERT_EQ( "Sports", to_string( Topic::Sports ) );
        ASSERT_EQ( "Rock", to_string( Topic::Rock ) );

        ASSERT_THROW( to_string( static_cast<Topic>( -1 ) ), std::runtime_error );
    }
}
