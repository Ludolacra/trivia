#include "Game/Game.hpp"

#include "Random/Player.hpp"
#include "Utility/Logger.hpp"


// LCOV_EXCL_START
int main()
{
    Utility::Logger::Init( std::make_unique<Utility::CoutLogger>() );

    try
    {
        Game aGame;

        aGame.addPlayer( std::make_shared<Random::Player>( "Chet" ) );
        aGame.addPlayer( std::make_shared<Random::Player>( "Pat" ) );
        aGame.addPlayer( std::make_shared<Random::Player>( "Sue" ) );

        aGame.play();
    }
    catch( ... )
    {
        ERROR( "Unknown error happened during the game!" );
    }

    Utility::Logger::Destroy();
}
// LCOV_EXCL_STOP
