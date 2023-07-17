#include "Game/Game.hpp"

#include "Random/Player.hpp"


int main()
{
    Game aGame;

    aGame.addPlayer( std::make_shared<Random::Player>( "Chet" ) );
    aGame.addPlayer( std::make_shared<Random::Player>( "Pat" ) );
    aGame.addPlayer( std::make_shared<Random::Player>( "Sue" ) );

    aGame.play();
}
