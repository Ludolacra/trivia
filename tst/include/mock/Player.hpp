#ifndef MOCK_PLAYER_HPP_
#define MOCK_PLAYER_HPP_

#include <gmock/gmock.h>

#include "Abstract/Player.hpp"

namespace UT
{
    namespace Mock
    {
        class Player : public ::Abstract::Player
        {
        public:
            Player( const std::string& name ) :
                ::Abstract::Player( name )
            {
            }

            MOCK_METHOD( void, move, (unsigned int, unsigned int), ( override ) );
            MOCK_METHOD( (unsigned int), getCoinCount, (), ( const, override ) );
            MOCK_METHOD( (unsigned int), getLocation, (), ( const, override ) );

            MOCK_METHOD( bool, isInPenalty, (), ( const, override ) );

            MOCK_METHOD( void, receiveReward, (), ( override ) );
            MOCK_METHOD( void, moveToPenalty, (), ( override ) );
            MOCK_METHOD( void, removeFromPenalty, (), ( override ) );

            MOCK_METHOD( (unsigned short), rollDice, (), ( const, override ) );
            MOCK_METHOD( bool, answer, (const std::string&), ( const, override ) );
        };
    }
}
#endif // MOCK_PLAYER_HPP_
