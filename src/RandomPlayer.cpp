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

    Player::~Player()
    {
    }

    bool Player::answer( const std::string& question ) const
    {
        (void)question;
        return std::rand() % 9 != 7;
    }
}
