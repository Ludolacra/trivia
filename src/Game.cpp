#include "Game/Game.hpp"

#include <iostream>
#include <Utility/Logger.hpp>

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

Game::~Game()
{
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
        return;
    }

    for( bool gameIsFinished = false; !gameIsFinished; )
    {
        for( auto playerIterator = mPlayers.begin();
             !gameIsFinished && playerIterator != mPlayers.end();
             ++playerIterator )
        {
            handlePlayerTurn( *playerIterator );

            gameIsFinished = hasPlayerCollectedEnoughCoins( *playerIterator );
        }
    }
}

void Game::handlePlayerTurn( std::shared_ptr<Abstract::Player>& currentPlayer )
{
    INFO( "%s is the current player", currentPlayer->getName().c_str() );

    const unsigned short roll = currentPlayer->rollDice();
    INFO( "They have rolled a %d", roll );

    const bool playerSkipsTurn = handlePenalty( currentPlayer, roll );
    if( playerSkipsTurn )
    {
        return;
    }

    currentPlayer->move( roll );
    INFO( "%s's new location is %d", currentPlayer->getName().c_str(), currentPlayer->getLocation() );

    askQuestion( currentPlayer );
    const bool correctAnswer = currentPlayer->answer( "question" );
    if( correctAnswer )
    {
        handleCorrectAnswer( currentPlayer );
    }
    else
    {
        handleIncorrectAnswer( currentPlayer );
    }
}

bool Game::handlePenalty( std::shared_ptr<Abstract::Player>& currentPlayer, unsigned short lastRoll )
{
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

void Game::askQuestion( std::shared_ptr<Abstract::Player>& currentPlayer )
{
    const Topic currentTopic = getCurrentCategory( currentPlayer->getLocation() );
    INFO( "The category is %s", to_string( currentTopic ).c_str() );
    const std::string question = getNextQuestion( currentTopic );
    INFO( question.c_str() );
}

void Game::handleCorrectAnswer( std::shared_ptr<Abstract::Player>& currentPlayer )
{
    if( currentPlayer->isInPenalty() )
    {
        return;
    }

    INFO( "Answer was correct!!!!" );
    currentPlayer->receiveReward();
    INFO( "%s now has %d Gold Coins.", currentPlayer->getName().c_str(), currentPlayer->getCoinCount() );
}

void Game::handleIncorrectAnswer( std::shared_ptr<Abstract::Player>& currentPlayer )
{
    INFO( "Question was incorrectly answered" );
    currentPlayer->moveToPenalty();
    INFO( "%s was sent to the penalty box", currentPlayer->getName().c_str() );
}

std::string Game::getNextQuestion( const Topic topic )
{
    std::string question = mQuestions.at( topic ).front();
    mQuestions.at( topic ).pop_front();
    return question;
}

Topic Game::getCurrentCategory( const unsigned short location )
{
    switch( location % mQuestions.size() )
    {
        case 0: return Topic::Pop;
        case 1: return Topic::Science;
        case 2: return Topic::Sports;
        default: return Topic::Rock;
    }
}
