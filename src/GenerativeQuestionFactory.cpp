#include "Generative/QuestionFactory.hpp"

namespace Generative
{
    QuestionFactory::QuestionFactory()
    {
    }

    QuestionFactory::~QuestionFactory()
    {
    }

    std::list<std::string> QuestionFactory::generateQuestions( const Topic topic, const unsigned int numberOfQuestions ) const
    {
        (void)topic;
        (void)numberOfQuestions;
        std::list<std::string> result;
        for( unsigned int i = 0; i < numberOfQuestions; ++i )
        {
            result.push_back( to_string( topic ) + " Question " + std::to_string( i ) );
        }

        return result;
    }
}
