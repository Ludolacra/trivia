#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

#include <Game/Game.hpp>
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
            EXPECT_CALL( *questionFactoryMock, generateQuestions( _, _ ) ).Times( 4 );
            testedObject = std::make_unique<Game>( questionFactoryMock );
        }
        void TearDown()
        {
            testedObject.reset();
            questionFactoryMock.reset();
        }
    };

    TEST_F( GameTest, qustionsAreGenerated )
    {
    }
}
