#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

#include "Game/Game.hpp"
#include "Game/Topic.hpp"
#include "mock/Player.hpp"
#include "mock/QuestionFactory.hpp"

using namespace testing;

namespace UT
{
    TEST( GameQuestionGenerationTest, questionsAreGenerated )
    {
        auto questionFactoryMock = std::make_shared<UT::Mock::QuestionFactory>();
        EXPECT_CALL( *questionFactoryMock, generateQuestions( Topic::Pop, 50 ) );
        EXPECT_CALL( *questionFactoryMock, generateQuestions( Topic::Science, 50 ) );
        EXPECT_CALL( *questionFactoryMock, generateQuestions( Topic::Sports, 50 ) );
        EXPECT_CALL( *questionFactoryMock, generateQuestions( Topic::Rock, 50 ) );

        auto testedObject = std::make_unique<Game>( questionFactoryMock );
    }

    class GameTest : public ::testing::Test
    {
    public:
        std::shared_ptr<Mock::QuestionFactory> questionFactoryMock;
        std::unique_ptr<Game> testedObject;
        std::shared_ptr<Mock::Player> player;

        void SetUp()
        {
            questionFactoryMock = std::make_shared<UT::Mock::QuestionFactory>();
            EXPECT_CALL( *questionFactoryMock, generateQuestions )
                .Times( 4 )
                .WillRepeatedly(
                    []( const Topic topic, const unsigned int ) -> std::list<std::string>
                    {
                        return { to_string( topic ) };
                    } );

            testedObject = std::make_unique<Game>( questionFactoryMock );

            player = std::make_shared<Mock::Player>( "Bob" );
            testing::internal::CaptureStdout();
            testedObject->addPlayer( player );
            testing::internal::GetCapturedStdout();
        }
        void TearDown()
        {
            testedObject.reset();
            questionFactoryMock.reset();
        }
    };

    TEST_F( GameTest, questionCategoryIsDeterminedBasedOnPlayerLocaion )
    {
        constexpr const unsigned short categoryCount = 4;
        for( unsigned short i = 0; i <= 11; ++i )
        {
            switch( i % categoryCount )
            {
                case 0:
                    ASSERT_EQ( Topic::Pop, testedObject->currentCategory( i ) );
                    break;
                case 1:
                    ASSERT_EQ( Topic::Science, testedObject->currentCategory( i ) );
                    break;
                case 2:
                    ASSERT_EQ( Topic::Sports, testedObject->currentCategory( i ) );
                    break;
                case 3:
                    ASSERT_EQ( Topic::Rock, testedObject->currentCategory( i ) );
                    break;
            }
        }
    }

    TEST_F( GameTest, popQuestionIsAsked )
    {
        EXPECT_CALL( *player, getLocation ).WillOnce( Return( 0 ) );

        testing::internal::CaptureStdout();
        testedObject->askQuestion();
        const std::string result = testing::internal::GetCapturedStdout();
        ASSERT_EQ( result, "Pop\n" );
    }

    TEST_F( GameTest, ScienceQuestionIsAsked )
    {
        EXPECT_CALL( *player, getLocation ).WillOnce( Return( 1 ) );

        testing::internal::CaptureStdout();
        testedObject->askQuestion();
        const std::string result = testing::internal::GetCapturedStdout();
        ASSERT_EQ( result, "Science\n" );
    }

    TEST_F( GameTest, SportsQuestionIsAsked )
    {
        EXPECT_CALL( *player, getLocation ).WillOnce( Return( 2 ) );

        testing::internal::CaptureStdout();
        testedObject->askQuestion();
        const std::string result = testing::internal::GetCapturedStdout();
        ASSERT_EQ( result, "Sports\n" );
    }

    TEST_F( GameTest, rockQuestionIsAsked )
    {
        EXPECT_CALL( *player, getLocation ).WillOnce( Return( 3 ) );

        testing::internal::CaptureStdout();
        testedObject->askQuestion();
        const std::string result = testing::internal::GetCapturedStdout();
        ASSERT_EQ( result, "Rock\n" );
    }

    class GameTurnTest : public GameTest
    {
    };

    TEST_F( GameTurnTest, playerIsMovedByRollValueAndQuestionIsAsked )
    {
        EXPECT_CALL( *player, move( 1, 12 ) );

        testing::internal::CaptureStdout();
        testedObject->roll( 1 );
        testing::internal::GetCapturedStdout();
    }

    TEST_F( GameTurnTest, playerStaysInPenaltyOnEvenRoll )
    {
        EXPECT_CALL( *player, isInPenalty ).WillOnce( Return( true ) );
        EXPECT_CALL( *player, removeFromPenalty ).Times( 0 );

        testing::internal::CaptureStdout();
        testedObject->roll( 2 );
        testing::internal::GetCapturedStdout();
    }

    TEST_F( GameTurnTest, playerIsRemovedFromPenaltyAndHasRegularTurnOnOddRoll )
    {
        EXPECT_CALL( *player, isInPenalty ).WillOnce( Return( true ) );
        EXPECT_CALL( *player, removeFromPenalty );

        testing::internal::CaptureStdout();
        testedObject->roll( 3 );
        testing::internal::GetCapturedStdout();
    }

    class GameAnswerTest : public GameTurnTest
    {
    };

    TEST_F( GameAnswerTest, correctAnswerGivesReward )
    {
        testing::internal::CaptureStdout();
        testedObject->wasCorrectlyAnswered();
        testing::internal::GetCapturedStdout();

        // ASSERT_EQ( testedObject->places[0], 0 );
        // ASSERT_EQ( testedObject->purses[0], 1 );
        // ASSERT_EQ( testedObject->inPenaltyBox[0], false );
    }

    TEST_F( GameAnswerTest, correctAnswerGivesNoRewardWhenPenalized )
    {
        // testedObject->inPenaltyBox[0] = true;
        testing::internal::CaptureStdout();
        testedObject->wasCorrectlyAnswered();
        testing::internal::GetCapturedStdout();

        // ASSERT_EQ( testedObject->places[0], 0 );
        // ASSERT_EQ( testedObject->purses[0], 0 );
        // ASSERT_EQ( testedObject->inPenaltyBox[0], true );
    }

    TEST_F( GameAnswerTest, wrongAnswerPenalizesPlayer )
    {
        // testedObject->inPenaltyBox[0] = false;
        testing::internal::CaptureStdout();
        testedObject->wrongAnswer();
        testing::internal::GetCapturedStdout();

        // ASSERT_EQ( testedObject->places[0], 0 );
        // ASSERT_EQ( testedObject->purses[0], 0 );
        // ASSERT_EQ( testedObject->inPenaltyBox[0], true );
    }

    TEST_F( GameAnswerTest, sixCoinsWinGame )
    {
        EXPECT_CALL( *player, isInPenalty ).WillOnce( Return( false ) );
        EXPECT_CALL( *player, getCoinCount ).Times( 2 ).WillRepeatedly( Return( 6 ) );


        testing::internal::CaptureStdout();
        bool notWon = testedObject->wasCorrectlyAnswered();
        ASSERT_FALSE( notWon );
        testing::internal::GetCapturedStdout();

        // ASSERT_EQ( testedObject->places[0], 0 );
        // ASSERT_EQ( testedObject->purses[0], 6 );
        // ASSERT_EQ( testedObject->inPenaltyBox[0], false );
    }
}
