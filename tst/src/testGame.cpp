#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

#include "Game/Game.hpp"
#include "Game/Topic.hpp"
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
        std::shared_ptr<UT::Mock::QuestionFactory> questionFactoryMock;
        std::unique_ptr<Game> testedObject;

        void SetUp()
        {
            questionFactoryMock = std::make_shared<UT::Mock::QuestionFactory>();
            EXPECT_CALL( *questionFactoryMock, generateQuestions ).Times( 4 );
        }
        void TearDown()
        {
            testedObject.reset();
            questionFactoryMock.reset();
        }
    };

    TEST_F( GameTest, questionCategoryIsDeterminedBasedOnPlayerLocaion )
    {
        testedObject = std::make_unique<Game>( questionFactoryMock );

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
        const std::string sampleQuestion = "This is a sample Pop question";
        ON_CALL( *questionFactoryMock, generateQuestions )
            .WillByDefault(
                [sampleQuestion]( const Topic topic, const unsigned int ) -> std::list<std::string>
                {
                    if( topic == Topic::Pop )
                    {

                        return { sampleQuestion };
                    }
                    else
                    {
                        return {};
                    }
                } );
        testedObject = std::make_unique<Game>( questionFactoryMock );

        testing::internal::CaptureStdout();
        testedObject->add( "Bob" );
        testing::internal::GetCapturedStdout();
        testedObject->places[testedObject->currentPlayer] = 0;

        testing::internal::CaptureStdout();
        testedObject->askQuestion();
        const std::string result = testing::internal::GetCapturedStdout();
        ASSERT_EQ( result, sampleQuestion + '\n' );
    }

    TEST_F( GameTest, ScienceQuestionIsAsked )
    {
        const std::string sampleQuestion = "This is a sample Science question";
        ON_CALL( *questionFactoryMock, generateQuestions )
            .WillByDefault(
                [sampleQuestion]( const Topic topic, const unsigned int ) -> std::list<std::string>
                {
                    if( topic == Topic::Science )
                    {

                        return { sampleQuestion };
                    }
                    else
                    {
                        return {};
                    }
                } );
        testedObject = std::make_unique<Game>( questionFactoryMock );

        testing::internal::CaptureStdout();
        testedObject->add( "Bob" );
        testing::internal::GetCapturedStdout();
        testedObject->places[testedObject->currentPlayer] = 1;

        testing::internal::CaptureStdout();
        testedObject->askQuestion();
        const std::string result = testing::internal::GetCapturedStdout();
        ASSERT_EQ( result, sampleQuestion + '\n' );
    }

    TEST_F( GameTest, SportsQuestionIsAsked )
    {
        const std::string sampleQuestion = "This is a sample Sports question";
        ON_CALL( *questionFactoryMock, generateQuestions )
            .WillByDefault(
                [sampleQuestion]( const Topic topic, const unsigned int ) -> std::list<std::string>
                {
                    if( topic == Topic::Sports )
                    {

                        return { sampleQuestion };
                    }
                    else
                    {
                        return {};
                    }
                } );
        testedObject = std::make_unique<Game>( questionFactoryMock );

        testing::internal::CaptureStdout();
        testedObject->add( "Bob" );
        testing::internal::GetCapturedStdout();
        testedObject->places[testedObject->currentPlayer] = 2;

        testing::internal::CaptureStdout();
        testedObject->askQuestion();
        const std::string result = testing::internal::GetCapturedStdout();
        ASSERT_EQ( result, sampleQuestion + '\n' );
    }

    TEST_F( GameTest, rockQuestionIsAsked )
    {
        const std::string sampleQuestion = "This is a sample Rock question";
        ON_CALL( *questionFactoryMock, generateQuestions )
            .WillByDefault(
                [sampleQuestion]( const Topic topic, const unsigned int ) -> std::list<std::string>
                {
                    if( topic == Topic::Rock )
                    {

                        return { sampleQuestion };
                    }
                    else
                    {
                        return {};
                    }
                } );
        testedObject = std::make_unique<Game>( questionFactoryMock );

        testing::internal::CaptureStdout();
        testedObject->add( "Bob" );
        testing::internal::GetCapturedStdout();
        testedObject->places[testedObject->currentPlayer] = 3;

        testing::internal::CaptureStdout();
        testedObject->askQuestion();
        const std::string result = testing::internal::GetCapturedStdout();
        ASSERT_EQ( result, sampleQuestion + '\n' );
    }

    TEST_F( GameTest, newPlayisInitialized )
    {
        testedObject = std::make_unique<Game>( questionFactoryMock );

        testing::internal::CaptureStdout();
        testedObject->add( "Bob" );
        testing::internal::GetCapturedStdout();

        ASSERT_EQ( testedObject->players.size(), 1u );
        ASSERT_EQ( testedObject->places[0], 0 );
        ASSERT_EQ( testedObject->purses[0], 0 );
        ASSERT_EQ( testedObject->inPenaltyBox[0], false );
    }

    class GameTurnTest : public ::testing::Test
    {
    public:
        std::shared_ptr<UT::Mock::QuestionFactory> questionFactoryMock;
        std::unique_ptr<Game> testedObject;

        void SetUp()
        {
            questionFactoryMock = std::make_shared<UT::Mock::QuestionFactory>();
            EXPECT_CALL( *questionFactoryMock, generateQuestions )
                .Times( 4 )
                .WillRepeatedly(
                    []( const Topic, const unsigned int ) -> std::list<std::string>
                    {
                        return { "dummy" };
                    } );

            testedObject = std::make_unique<Game>( questionFactoryMock );

            testing::internal::CaptureStdout();
            testedObject->add( "Bob" );
            testing::internal::GetCapturedStdout();
        }
        void TearDown()
        {
            testedObject.reset();
            questionFactoryMock.reset();
        }
    };

    TEST_F( GameTurnTest, playerIsMovedByRollValueAndQuestionIsAsked )
    {
        testing::internal::CaptureStdout();
        testedObject->roll( 1 );
        testing::internal::GetCapturedStdout();

        ASSERT_EQ( testedObject->places[0], 1 );
        ASSERT_EQ( testedObject->purses[0], 0 );
        ASSERT_EQ( testedObject->inPenaltyBox[0], false );
    }

    TEST_F( GameTurnTest, playerStaysInPenaltyOnEvenRoll )
    {
        testedObject->inPenaltyBox[0] = true;
        testing::internal::CaptureStdout();
        testedObject->roll( 2 );
        testing::internal::GetCapturedStdout();

        ASSERT_EQ( testedObject->places[0], 0 );
        ASSERT_EQ( testedObject->purses[0], 0 );
        ASSERT_EQ( testedObject->inPenaltyBox[0], true );
    }

    TEST_F( GameTurnTest, playerIsRemovedFromPenaltyAndHasRegularTurnOnOddRoll )
    {
        testedObject->inPenaltyBox[0] = true;
        testing::internal::CaptureStdout();
        testedObject->roll( 3 );
        testing::internal::GetCapturedStdout();

        ASSERT_EQ( testedObject->places[0], 3 );
        ASSERT_EQ( testedObject->purses[0], 0 );
        ASSERT_EQ( testedObject->inPenaltyBox[0], false );
    }
}
