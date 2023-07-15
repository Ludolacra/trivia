#ifndef MOCK_QUESTIONFACTORY_HPP_
#define MOCK_QUESTIONFACTORY_HPP_

#include <gmock/gmock.h>

#include "Abstract/QuestionFactory.hpp"
#include "Game/Topic.hpp"

namespace UT
{
    namespace Mock
    {
        class QuestionFactory : public ::Abstract::QuestionFactory
        {
        public:
            MOCK_CONST_METHOD2( generateQuestions, std::list<std::string>( const Topic, const unsigned int ) );
        };
    }
}
#endif // MOCK_QUESTIONFACTORY_HPP_
