#include "Game/Game.hpp"

#include <iostream>

Game::Game( std::shared_ptr<Abstract::QuestionFactory> questionFactory ) :
    players(),
    mQuestions(),
    places(),
    purses(),
    currentPlayer( 0 )
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
    return ( howManyPlayers() >= 2 );
}

bool Game::add( std::string playerName )
{
    players.push_back( playerName );
    places[howManyPlayers()]       = 0;
    purses[howManyPlayers()]       = 0;
    inPenaltyBox[howManyPlayers()] = false;

    std::cout << playerName << " was added" << std::endl;
    std::cout << "They are player number " << players.size() << std::endl;
    return true;
}

int Game::howManyPlayers()
{
    return players.size();
}

void Game::roll( int roll )
{
    std::cout << players[currentPlayer] << " is the current player" << std::endl;
    std::cout << "They have rolled a " << roll << std::endl;

    if( inPenaltyBox[currentPlayer] )
    {
        if( roll % 2 != 0 )
        {
            isGettingOutOfPenaltyBox = true;

            std::cout << players[currentPlayer] << " is getting out of the penalty box" << std::endl;
            places[currentPlayer] = places[currentPlayer] + roll;
            if( places[currentPlayer] > 11 )
                places[currentPlayer] = places[currentPlayer] - 12;

            std::cout << players[currentPlayer] << "'s new location is " << places[currentPlayer] << std::endl;
            std::cout << "The category is " << to_string( currentCategory( places[currentPlayer] ) ) << std::endl;
            askQuestion();
        }
        else
        {
            std::cout << players[currentPlayer] << " is not getting out of the penalty box" << std::endl;
            isGettingOutOfPenaltyBox = false;
        }
    }
    else
    {
        places[currentPlayer] = places[currentPlayer] + roll;
        if( places[currentPlayer] > 11 )
            places[currentPlayer] = places[currentPlayer] - 12;

        std::cout << players[currentPlayer] << "'s new location is " << places[currentPlayer] << std::endl;
        std::cout << "The category is " << to_string( currentCategory( places[currentPlayer] ) ) << std::endl;
        askQuestion();
    }
}

void Game::askQuestion()
{
    auto& currentQuestions = mQuestions.at( currentCategory( places[currentPlayer] ) );

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
    if( inPenaltyBox[currentPlayer] )
    {
        if( isGettingOutOfPenaltyBox )
        {
            std::cout << "Answer was correct!!!!" << std::endl;
            purses[currentPlayer]++;
            std::cout << players[currentPlayer]
                      << " now has "
                      << purses[currentPlayer]
                      << " Gold Coins." << std::endl;

            bool winner = didPlayerWin();
            currentPlayer++;
            if( currentPlayer == players.size() )
                currentPlayer = 0;

            return winner;
        }
        else
        {
            currentPlayer++;
            if( currentPlayer == players.size() )
                currentPlayer = 0;
            return true;
        }
    }
    else
    {
        std::cout << "Answer was corrent!!!!" << std::endl;
        purses[currentPlayer]++;
        std::cout << players[currentPlayer]
                  << " now has "
                  << purses[currentPlayer]
                  << " Gold Coins." << std::endl;

        bool winner = didPlayerWin();
        currentPlayer++;
        if( currentPlayer == players.size() )
            currentPlayer = 0;

        return winner;
    }
}

bool Game::wrongAnswer()
{
    std::cout << "Question was incorrectly answered" << std::endl;
    std::cout << players[currentPlayer] + " was sent to the penalty box" << std::endl;
    inPenaltyBox[currentPlayer] = true;

    currentPlayer++;
    if( currentPlayer == players.size() )
        currentPlayer = 0;
    return true;
}

bool Game::didPlayerWin()
{
    return !( purses[currentPlayer] == 6 );
}
