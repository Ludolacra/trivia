#include "Game/Game.hpp"

#include "Random/Player.hpp"
#include "Utility/Logger.hpp"


int main()
{
    Utility::Logger::Init( std::make_unique<Utility::CoutLogger>() );

    Game aGame;

    aGame.addPlayer( std::make_shared<Random::Player>( "Chet" ) );
    aGame.addPlayer( std::make_shared<Random::Player>( "Pat" ) );
    aGame.addPlayer( std::make_shared<Random::Player>( "Sue" ) );

    aGame.play();

    Utility::Logger::Destroy();
}
