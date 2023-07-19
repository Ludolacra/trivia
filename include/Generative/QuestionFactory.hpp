#ifndef GENERATIVE_QUESTIONFACTORY_HPP_
#define GENERATIVE_QUESTIONFACTORY_HPP_

#include <list>
#include <string>

#include "Abstract/QuestionFactory.hpp"
#include "Game/Topic.hpp"

namespace Generative
{
    class QuestionFactory : public ::Abstract::QuestionFactory
    {
    public:
        inline QuestionFactory()    = default;
        ~QuestionFactory() override = default;

        virtual std::list<std::string> generateQuestions( const Topic topic,
                                                          const unsigned int numberOfQuestions ) const override;
    };
}


#endif // GENERATIVE_QUESTIONFACTORY_HPP_
