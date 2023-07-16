#include "Game/Game.hpp"

#include <iostream>

Game::Game( std::shared_ptr<Abstract::QuestionFactory> questionFactory ) :
    mPlayers(),
    mCurrentPlayer( mPlayers.end() ),
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

bool Game::isPlayable()
{
    return ( mPlayers.size() >= 2 );
}

void Game::addPlayer( std::shared_ptr<Abstract::Player> newPlayer )
{
    mPlayers.push_back( newPlayer );

    std::cout << mPlayers.back()->getName() << " was added\n";
    std::cout << "They are player number " << mPlayers.size() << "\n";

    std::cout << std::flush;

    mCurrentPlayer = mPlayers.begin();
    if( mPlayers.end() == mCurrentPlayer )
    {
    }
}

void Game::setNextPlayer()
{
    ++mCurrentPlayer;
    if( mPlayers.end() == mCurrentPlayer )
    {
        mCurrentPlayer = mPlayers.begin();
    }
}

void Game::roll( int roll )
{
    std::cout << ( *mCurrentPlayer )->getName() << " is the current player" << std::endl;
    std::cout << "They have rolled a " << roll << std::endl;

    if( ( *mCurrentPlayer )->isInPenalty() )
    {
        if( roll % 2 == 0 )
        {
            std::cout << ( *mCurrentPlayer )->getName() << " is not getting out of the penalty box" << std::endl;
            return;
        }

        std::cout << ( *mCurrentPlayer )->getName() << " is getting out of the penalty box" << std::endl;
        ( *mCurrentPlayer )->removeFromPenalty();
    }

    ( *mCurrentPlayer )->move( roll );

    std::cout << ( *mCurrentPlayer )->getName() << "'s new location is " << ( *mCurrentPlayer )->getLocation() << std::endl;
    std::cout << "The category is " << to_string( currentCategory( ( *mCurrentPlayer )->getLocation() ) ) << std::endl;
    askQuestion();
}

void Game::askQuestion()
{
    auto& currentQuestions = mQuestions.at( currentCategory( ( *mCurrentPlayer )->getLocation() ) );

    std::cout << currentQuestions.front() << std::endl;
    currentQuestions.pop_front();
}

Topic Game::currentCategory( const unsigned short location )
{
    constexpr const unsigned short categoryCount = 4;
    switch( location % categoryCount )
    {
        case 0: return Topic::Pop;
        case 1: return Topic::Science;
        case 2: return Topic::Sports;
        default: return Topic::Rock;
    }
}

bool Game::wasCorrectlyAnswered()
{
    if( ( *mCurrentPlayer )->isInPenalty() )
    {
        setNextPlayer();
        return true;
    }

    std::cout << "Answer was correct!!!!" << std::endl;
    ( *mCurrentPlayer )->receiveReward();
    std::cout << ( *mCurrentPlayer )->getName()
              << " now has "
              << ( *mCurrentPlayer )->getCoinCount()
              << " Gold Coins." << std::endl;

    bool winner = didPlayerWin();
    setNextPlayer();

    return winner;
}

bool Game::wrongAnswer()
{
    std::cout << "Question was incorrectly answered" << std::endl;
    std::cout << ( *mCurrentPlayer )->getName() + " was sent to the penalty box" << std::endl;
    ( *mCurrentPlayer )->moveToPenalty();

    setNextPlayer();
    return true;
}

bool Game::didPlayerWin()
{
    return ( *mCurrentPlayer )->getCoinCount() != 6;
}
