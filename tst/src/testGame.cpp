#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

#include "mock/Player.hpp"
#include "mock/QuestionFactory.hpp"
#include <ut/Logger.hpp>

// Ugly, but we can easily test private members this way
#define private public
#include "Game/Game.hpp"
#include "Game/Topic.hpp"

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
            testedObject->addPlayer( player );
        }
        void TearDown()
        {
            testedObject.reset();
            questionFactoryMock.reset();
        }
    };

    TEST_F( GameTest, gameIsNotPlayableInSolo )
    {
        Utility::Logger::Init( std::make_unique<Logger>() );
        testedObject->play();

        EXPECT_ERROR( "Game is not playable with current player count(1). At least 2 players are needed." );
        EXPECT_NO_LOG();
        Utility::Logger::Destroy();
    }

    TEST_F( GameTest, questionCategoryIsDeterminedBasedOnPlayerLocaion )
    {
        constexpr const unsigned short categoryCount = 4;
        for( unsigned short i = 0; i <= 11; ++i )
        {
            switch( i % categoryCount )
            {
                case 0:
                    ASSERT_EQ( Topic::Pop, testedObject->getCurrentCategory( i ) );
                    break;
                case 1:
                    ASSERT_EQ( Topic::Science, testedObject->getCurrentCategory( i ) );
                    break;
                case 2:
                    ASSERT_EQ( Topic::Sports, testedObject->getCurrentCategory( i ) );
                    break;
                case 3:
                    ASSERT_EQ( Topic::Rock, testedObject->getCurrentCategory( i ) );
                    break;
            }
        }
    }

    TEST_F( GameTest, appropriateTopicQuestionIsAsked )
    {
        const unsigned short popLocaltion     = 0;
        const unsigned short scienceLocaltion = 1;
        const unsigned short sportsLocaltion  = 2;
        const unsigned short rockLocaltion    = 3;

        ASSERT_EQ( testedObject->getNextQuestion( popLocaltion ), "Pop" );
        ASSERT_EQ( testedObject->getNextQuestion( scienceLocaltion ), "Science" );
        ASSERT_EQ( testedObject->getNextQuestion( sportsLocaltion ), "Sports" );
        ASSERT_EQ( testedObject->getNextQuestion( rockLocaltion ), "Rock" );
    }

    class GameTurnTest : public GameTest
    {
    };

    TEST_F( GameTurnTest, playerIsMovedByRollValueAndQuestionIsAsked )
    {
        EXPECT_CALL( *player, isInPenalty ).Times( 2 ).WillRepeatedly( Return( false ) );
        EXPECT_CALL( *player, rollDice ).WillOnce( Return( 1 ) );
        EXPECT_CALL( *player, move( 1 ) );
        EXPECT_CALL( *player, getLocation ).Times( 2 ).WillRepeatedly( Return( 2 ) );
        EXPECT_CALL( *player, answer ).WillOnce( Return( true ) );
        EXPECT_CALL( *player, receiveReward );
        EXPECT_CALL( *player, getCoinCount ).WillOnce( Return( 1 ) );

        auto abstractPlayer = std::static_pointer_cast<Abstract::Player>( player );
        testedObject->handlePlayerTurn( abstractPlayer );
    }

    TEST_F( GameTurnTest, playerStaysInPenaltyOnEvenRoll )
    {
        EXPECT_CALL( *player, isInPenalty ).WillOnce( Return( true ) );
        EXPECT_CALL( *player, rollDice ).WillOnce( Return( 2 ) );
        EXPECT_CALL( *player, move ).Times( 0 );
        EXPECT_CALL( *player, getLocation ).Times( 0 );
        EXPECT_CALL( *player, answer ).Times( 0 );
        EXPECT_CALL( *player, receiveReward ).Times( 0 );
        EXPECT_CALL( *player, getCoinCount ).Times( 0 );

        auto abstractPlayer = std::static_pointer_cast<Abstract::Player>( player );
        testedObject->handlePlayerTurn( abstractPlayer );
    }

    TEST_F( GameTurnTest, playerIsRemovedFromPenaltyAndHasRegularTurnOnOddRoll )
    {
        EXPECT_CALL( *player, isInPenalty ).Times( 2 ).WillOnce( Return( true ) ).WillOnce( Return( false ) );
        EXPECT_CALL( *player, rollDice ).WillOnce( Return( 3 ) );
        EXPECT_CALL( *player, removeFromPenalty );
        EXPECT_CALL( *player, move( 3 ) );
        EXPECT_CALL( *player, getLocation ).Times( 2 ).WillRepeatedly( Return( 4 ) );
        EXPECT_CALL( *player, answer ).WillOnce( Return( true ) );
        EXPECT_CALL( *player, receiveReward );
        EXPECT_CALL( *player, getCoinCount ).WillOnce( Return( 1 ) );

        auto abstractPlayer = std::static_pointer_cast<Abstract::Player>( player );
        testedObject->handlePlayerTurn( abstractPlayer );
    }

    class GameAnswerTest : public GameTurnTest
    {
    };

    TEST_F( GameAnswerTest, correctAnswerGivesReward )
    {
        EXPECT_CALL( *player, isInPenalty ).WillOnce( Return( false ) );
        EXPECT_CALL( *player, receiveReward );
        EXPECT_CALL( *player, getCoinCount ).WillOnce( Return( 1 ) );

        auto abstractPlayer = std::static_pointer_cast<Abstract::Player>( player );
        testedObject->handleCorrectAnswer( abstractPlayer );
    }

    TEST_F( GameAnswerTest, correctAnswerGivesNoRewardWhenPenalized )
    {
        EXPECT_CALL( *player, isInPenalty ).WillOnce( Return( true ) );
        EXPECT_CALL( *player, receiveReward ).Times( 0 );
        EXPECT_CALL( *player, getCoinCount ).Times( 0 );

        auto abstractPlayer = std::static_pointer_cast<Abstract::Player>( player );
        testedObject->handleCorrectAnswer( abstractPlayer );
    }

    TEST_F( GameAnswerTest, wrongAnswerPenalizesPlayer )
    {
        EXPECT_CALL( *player, moveToPenalty );

        auto abstractPlayer = std::static_pointer_cast<Abstract::Player>( player );
        testedObject->handleIncorrectAnswer( abstractPlayer );
    }

    TEST_F( GameAnswerTest, sixCoinsWinGame )
    {
        EXPECT_CALL( *player, getCoinCount ).WillOnce( Return( 2 ) ).WillOnce( Return( 6 ) );

        auto abstractPlayer = std::static_pointer_cast<Abstract::Player>( player );
        ASSERT_FALSE( testedObject->hasPlayerCollectedEnoughCoins( abstractPlayer->getCoinCount() ) );
        ASSERT_TRUE( testedObject->hasPlayerCollectedEnoughCoins( abstractPlayer->getCoinCount() ) );
    }
}
