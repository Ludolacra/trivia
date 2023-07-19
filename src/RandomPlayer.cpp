#include "Random/Player.hpp"

#include <cstdlib>
#include <ctime>


namespace Random
{
    Player::Player( const std::string& name ) :
        Abstract::Player( name )
    {
        std::srand( std::time( nullptr ) );
    }

    bool Player::answer( const std::string& question ) const
    {
        (void)question;
        // The randomly answering player basically has 11.1% chance to incorrectly answer
        return std::rand() % 9 != 7;
    }
}
