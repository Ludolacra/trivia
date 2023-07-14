#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

#include <Game/Game.hpp>

using namespace testing;

namespace UT
{
    class GameTest : public ::testing::Test
    {
    public:
        std::unique_ptr<Game> testedObject;

        void SetUp()
        {
            testedObject = std::make_unique<Game>();
        }
        void TearDown()
        {
            testedObject.reset();
        }
    };

    TEST_F( GameTest, popQuestionsArePopulatedCorrectly )
    {
        ASSERT_EQ( testedObject->popQuestions.size(), 50ul );

        for( unsigned short i = 0; i < 50; ++i )
        {
            ASSERT_EQ( testedObject->popQuestions.front(), std::string( "Pop Question " + std::to_string( i ) ) );
            testedObject->popQuestions.pop_front();
        }
    }

    TEST_F( GameTest, scienceQuestionsArePopulatedCorrectly )
    {
        ASSERT_EQ( testedObject->scienceQuestions.size(), 50ul );

        for( unsigned short i = 0; i < 50; ++i )
        {
            ASSERT_EQ( testedObject->scienceQuestions.front(), std::string( "Science Question " + std::to_string( i ) ) );
            testedObject->scienceQuestions.pop_front();
        }
    }

    TEST_F( GameTest, sportQuestionsArePopulatedCorrectly )
    {
        ASSERT_EQ( testedObject->sportsQuestions.size(), 50ul );

        for( unsigned short i = 0; i < 50; ++i )
        {
            ASSERT_EQ( testedObject->sportsQuestions.front(), std::string( "Sports Question " + std::to_string( i ) ) );
            testedObject->sportsQuestions.pop_front();
        }
    }

    TEST_F( GameTest, rockQuestionsArePopulatedCorrectly )
    {
        ASSERT_EQ( testedObject->rockQuestions.size(), 50ul );

        for( unsigned short i = 0; i < 50; ++i )
        {
            ASSERT_EQ( testedObject->rockQuestions.front(), std::string( "Rock Question " + std::to_string( i ) ) );
            testedObject->rockQuestions.pop_front();
        }
    }
}
