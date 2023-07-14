#include "Generative/QuestionFactory.hpp"

namespace Generative
{
    QuestionFactory::QuestionFactory()
    {
    }

    QuestionFactory::~QuestionFactory()
    {
    }

    std::list<std::string> QuestionFactory::generateQuestions( const Abstract::QuestionFactory::Topic topic, const unsigned int numberOfQuestions ) const
    {
        (void)topic;
        (void)numberOfQuestions;
        std::list<std::string> result;
        for( unsigned int i = 0; i < numberOfQuestions; ++i )
        {
            result.push_back( std::string( topicToString( topic ) ) + " Question " + std::to_string( i ) );
        }

        return result;
    }

    constexpr std::string_view QuestionFactory::topicToString( const Abstract::QuestionFactory::Topic topic ) const
    {
#define CASE( X ) \
    case Topic::X: return #X
        switch( topic )
        {
            CASE( Pop );
            CASE( Science );
            CASE( Sports );
            CASE( Rock );
            default: throw std::runtime_error( "Unknown topic received!" );
        }
    }
}
