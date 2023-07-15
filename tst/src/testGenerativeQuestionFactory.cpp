#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

#include "Game/Topic.hpp"
#include <Generative/QuestionFactory.hpp>

using namespace testing;

namespace UT
{
    class GenerativeQuestionFactoryTest : public ::testing::Test
    {
    public:
        std::unique_ptr<Generative::QuestionFactory> testedObject;

        void SetUp()
        {
            testedObject = std::make_unique<Generative::QuestionFactory>();
        }
        void TearDown()
        {
            testedObject.reset();
        }
    };

    TEST_F( GenerativeQuestionFactoryTest, generateSinglePopQuestion )
    {
        auto questions = testedObject->generateQuestions( Topic::Pop, 1 );
        ASSERT_EQ( questions.size(), 1ul );
        ASSERT_EQ( questions.front(), std::string( "Pop Question 0" ) );
    }

    TEST_F( GenerativeQuestionFactoryTest, generateSingleScienceQuestion )
    {
        auto questions = testedObject->generateQuestions( Topic::Science, 1 );
        ASSERT_EQ( questions.size(), 1ul );
        ASSERT_EQ( questions.front(), std::string( "Science Question 0" ) );
    }

    TEST_F( GenerativeQuestionFactoryTest, generateSingleSportsQuestion )
    {
        auto questions = testedObject->generateQuestions( Topic::Sports, 1 );
        ASSERT_EQ( questions.size(), 1ul );
        ASSERT_EQ( questions.front(), std::string( "Sports Question 0" ) );
    }

    TEST_F( GenerativeQuestionFactoryTest, generateSingleRockQuestion )
    {
        auto questions = testedObject->generateQuestions( Topic::Rock, 1 );
        ASSERT_EQ( questions.size(), 1ul );
        ASSERT_EQ( questions.front(), std::string( "Rock Question 0" ) );
    }

    TEST_F( GenerativeQuestionFactoryTest, generateMultipleQuestions )
    {
        auto questions = testedObject->generateQuestions( Topic::Pop, 10 );
        ASSERT_EQ( questions.size(), 10ul );
        for( unsigned short i = 0u; i < 10; ++i )
        {
            ASSERT_EQ( questions.front(), std::string( "Pop Question " ) + std::to_string( i ) );
            questions.pop_front();
        }
    }
}
