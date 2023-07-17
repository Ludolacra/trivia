#ifndef RANDOM_PLAYER_HPP_
#define RANDOM_PLAYER_HPP_

#include "Abstract/Player.hpp"

namespace Random
{
    class Player : public ::Abstract::Player
    {
    public:
        explicit Player( const std::string& name );
        ~Player() override;

        bool answer( const std::string& question ) const override;
    };
}

#endif // RANDOM_PLAYER_HPP_
