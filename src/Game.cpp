#include "Game/Game.hpp"

#include <iostream>

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

    std::cout << mPlayers.back()->getName() << " was added" << std::endl;
    std::cout << "They are player number " << mPlayers.size() << std::endl;
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
    std::cout << currentPlayer->getName() << " is the current player" << std::endl;

    const unsigned short roll = currentPlayer->rollDice();
    std::cout << "They have rolled a " << roll << std::endl;

    const bool playerSkipsTurn = handlePenalty( currentPlayer, roll );
    if( playerSkipsTurn )
    {
        return;
    }

    currentPlayer->move( roll );
    std::cout << currentPlayer->getName() << "'s new location is " << currentPlayer->getLocation() << std::endl;

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
        std::cout << currentPlayer->getName() << " is not getting out of the penalty box" << std::endl;
        return true;
    }

    std::cout << currentPlayer->getName() << " is getting out of the penalty box" << std::endl;
    currentPlayer->removeFromPenalty();

    return false;
}

void Game::askQuestion( std::shared_ptr<Abstract::Player>& currentPlayer )
{
    const Topic currentTopic = getCurrentCategory( currentPlayer->getLocation() );
    std::cout << "The category is " << to_string( currentTopic ) << std::endl;
    const std::string question = getNextQuestion( currentTopic );
    std::cout << question << std::endl;
}

void Game::handleCorrectAnswer( std::shared_ptr<Abstract::Player>& currentPlayer )
{
    if( currentPlayer->isInPenalty() )
    {
        return;
    }

    std::cout << "Answer was correct!!!!" << std::endl;
    currentPlayer->receiveReward();
    std::cout << currentPlayer->getName() << " now has " << currentPlayer->getCoinCount() << " Gold Coins." << std::endl;
}

void Game::handleIncorrectAnswer( std::shared_ptr<Abstract::Player>& currentPlayer )
{
    std::cout << "Question was incorrectly answered" << std::endl;
    std::cout << currentPlayer->getName() << " was sent to the penalty box" << std::endl;
    currentPlayer->moveToPenalty();
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
