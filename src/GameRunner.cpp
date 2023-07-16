#include <stdlib.h>
#include "Game/Game.hpp"

#include "Random/Player.hpp"

static bool notAWinner;

int main()
{

    srand( time( NULL ) );
    Game aGame;

    aGame.addPlayer( std::make_shared<Random::Player>( "Chet" ) );
    aGame.addPlayer( std::make_shared<Random::Player>( "Pat" ) );
    aGame.addPlayer( std::make_shared<Random::Player>( "Sue" ) );

    do
    {

        aGame.roll( rand() % 5 + 1 );

        if( rand() % 9 == 7 )
        {
            notAWinner = aGame.wrongAnswer();
        }
        else
        {
            notAWinner = aGame.wasCorrectlyAnswered();
        }
    } while( notAWinner );
}
