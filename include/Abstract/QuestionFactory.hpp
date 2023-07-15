#ifndef ABSTRACT_QUESTIONFACTORY_HPP_
#define ABSTRACT_QUESTIONFACTORY_HPP_

#include <list>
#include <string>

#include "Game/Topic.hpp"

namespace Abstract
{
    class QuestionFactory
    {
    public:
        QuestionFactory();
        virtual ~QuestionFactory();

        virtual std::list<std::string> generateQuestions( const Topic topic, const unsigned int numberOfQuestions ) const = 0;
    };
}


#endif // ABSTRACT_QUESTIONFACTORY_HPP_
