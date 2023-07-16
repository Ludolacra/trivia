#include "Random/Player.hpp"

namespace Random
{
    Player::Player( const std::string& name ) :
        Abstract::Player( name )
    {
    }

    Player::~Player()
    {
    }

    bool Player::answer( const std::string& question ) const
    {
        (void)question;
        return false;
    }
}
