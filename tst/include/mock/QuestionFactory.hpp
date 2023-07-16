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
            MOCK_METHOD( std::list<std::string>, generateQuestions, (const Topic, const unsigned int), ( const, override ) );
        };
    }
}
#endif // MOCK_QUESTIONFACTORY_HPP_
