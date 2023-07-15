#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

#include "Game/Game.hpp"
#include "Game/Topic.hpp"
#include "mock/QuestionFactory.hpp"

using namespace testing;

namespace UT
{
    class GameTest : public ::testing::Test
    {
    public:
        std::shared_ptr<UT::Mock::QuestionFactory> questionFactoryMock;
        std::unique_ptr<Game> testedObject;

        void SetUp()
        {
            questionFactoryMock = std::make_shared<UT::Mock::QuestionFactory>();
            EXPECT_CALL( *questionFactoryMock, generateQuestions ).Times( 4 );

            testedObject = std::make_unique<Game>( questionFactoryMock );
        }
        void TearDown()
        {
            testedObject.reset();
            questionFactoryMock.reset();
        }
    };

    TEST( GameQuestionGenerationTest, qustionsAreGenerated )
    {
        auto questionFactoryMock = std::make_shared<UT::Mock::QuestionFactory>();
        EXPECT_CALL( *questionFactoryMock, generateQuestions( Topic::Pop, 50 ) );
        EXPECT_CALL( *questionFactoryMock, generateQuestions( Topic::Science, 50 ) );
        EXPECT_CALL( *questionFactoryMock, generateQuestions( Topic::Sports, 50 ) );
        EXPECT_CALL( *questionFactoryMock, generateQuestions( Topic::Rock, 50 ) );

        auto testedObject = std::make_unique<Game>( questionFactoryMock );
    }

    TEST_F( GameTest, questionCategoryIsDeterminedBasedOnPlayerLocaion )
    {
        testing::internal::CaptureStdout();
        testedObject->add( "Bob" );
        testing::internal::GetCapturedStdout();

        constexpr const unsigned short categoryCount = 4;
        for( unsigned short i = 0; i <= 11; ++i )
        {
            testedObject->places[testedObject->currentPlayer] = i;
            switch( i % categoryCount )
            {
                case 0:
                    ASSERT_EQ( "Pop", testedObject->currentCategory() );
                    break;
                case 1:
                    ASSERT_EQ( "Science", testedObject->currentCategory() );
                    break;
                case 2:
                    ASSERT_EQ( "Sports", testedObject->currentCategory() );
                    break;
                case 3:
                    ASSERT_EQ( "Rock", testedObject->currentCategory() );
                    break;
            }
        }
    }
}
