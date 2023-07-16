#ifndef RANDOM_PLAYER_HPP_
#define RANDOM_PLAYER_HPP_

#include "Abstract/Player.hpp"

namespace Random
{
    class Player : public ::Abstract::Player
    {
    public:
        Player( const std::string& name );
        ~Player();

        bool answer( const std::string& question ) const override;
    };
}

#endif // RANDOM_PLAYER_HPP_
