#include "Game/Game.hpp"

#include <iostream>
#include <stdexcept>

#include "Utility/Logger.hpp"

Game::Game( std::shared_ptr<Abstract::QuestionFactory> questionFactory ) :
    mPlayers(),
    mQuestions()
{
    constexpr const unsigned int questionsPerTopic = 50;

    for( const auto topic : { Topic::Pop, Topic::Science, Topic::Sports, Topic::Rock } )
    {
        mQuestions[topic] = questionFactory->generateQuestions( topic, questionsPerTopic );
    }
}

void Game::addPlayer( std::shared_ptr<Abstract::Player> newPlayer )
{
    mPlayers.push_back( newPlayer );

    INFO( "%s was added", mPlayers.back()->getName().c_str() );
    INFO( "They are player number %d", mPlayers.size() );
}

void Game::play()
{
    if( !isPlayable() )
    {
        ERROR( "Game is not playable with current player count(%d). At least %d players are needed.",
               mPlayers.size(), msMinimumPlayerCount );
        return;
    }

    for( bool gameIsWon = false; !gameIsWon; )
    {
        for( auto playerIterator = mPlayers.begin(); !gameIsWon && playerIterator != mPlayers.end(); ++playerIterator )
        {
            handlePlayerTurn( *playerIterator );

            gameIsWon = hasPlayerCollectedEnoughCoins( ( *playerIterator )->getCoinCount() );
        }
    }
}

void Game::handlePlayerTurn( std::shared_ptr<Abstract::Player> currentPlayer )
{
    INFO( "%s is the current player", currentPlayer->getName().c_str() );

    const unsigned short roll = currentPlayer->rollDice();
    INFO( "They have rolled a %d", roll );

    if( playerMustSkipTurn( currentPlayer, roll ) )
    {
        return;
    }

    currentPlayer->move( roll );
    INFO( "%s's new location is %d", currentPlayer->getName().c_str(), currentPlayer->getLocation() );

    const std::string question = getNextQuestion( currentPlayer->getLocation() );
    INFO( question.c_str() );

    const bool correctAnswer = currentPlayer->answer( question );
    if( correctAnswer )
    {
        handleCorrectAnswer( currentPlayer );
    }
    else
    {
        handleIncorrectAnswer( currentPlayer );
    }
}

bool Game::playerMustSkipTurn( std::shared_ptr<Abstract::Player> currentPlayer, unsigned short lastRoll )
{
    // These two statements are intentionally not combined
    // removeFromPenalty is preferred to be not called when not necessary
    if( !currentPlayer->isInPenalty() )
    {
        return false;
    }

    if( lastRoll % 2 == 0 )
    {
        INFO( "%s is not getting out of the penalty box", currentPlayer->getName().c_str() );
        return true;
    }

    INFO( "%s is getting out of the penalty box", currentPlayer->getName().c_str() );
    currentPlayer->removeFromPenalty();

    return false;
}

void Game::handleCorrectAnswer( std::shared_ptr<Abstract::Player> currentPlayer )
{
    if( currentPlayer->isInPenalty() )
    {
        return;
    }

    INFO( "Answer was correct!!!!" );
    currentPlayer->receiveReward();
    INFO( "%s now has %d Gold Coins.", currentPlayer->getName().c_str(), currentPlayer->getCoinCount() );
}

void Game::handleIncorrectAnswer( std::shared_ptr<Abstract::Player> currentPlayer )
{
    INFO( "Question was incorrectly answered" );
    currentPlayer->moveToPenalty();
    INFO( "%s was sent to the penalty box", currentPlayer->getName().c_str() );
}

std::string Game::getNextQuestion( const unsigned short playerLocation )
{
    const Topic currentTopic = getCurrentCategory( playerLocation );
    INFO( "The category is %s", to_string( currentTopic ).c_str() );

    std::string question = mQuestions.at( currentTopic ).front();
    mQuestions.at( currentTopic ).pop_front();

    return question;
}

Topic Game::getCurrentCategory( const unsigned short location )
{
    switch( location % mQuestions.size() )
    {
        case 0: return Topic::Pop;
        case 1: return Topic::Science;
        case 2: return Topic::Sports;
        case 3: return Topic::Rock;
        default: throw std::runtime_error( "Impossible value found when determining current category!" );
    }
}
