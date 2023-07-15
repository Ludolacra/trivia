#include "Game/Game.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>

#include "Game/Topic.hpp"

using namespace std;

Game::Game( std::shared_ptr<Abstract::QuestionFactory> questionFactory ) :
    places(), purses(), currentPlayer( 0 )
{
    constexpr const unsigned int questionsPerTopic = 50;

    popQuestions     = questionFactory->generateQuestions( Topic::Pop, questionsPerTopic );
    scienceQuestions = questionFactory->generateQuestions( Topic::Science, questionsPerTopic );
    sportsQuestions  = questionFactory->generateQuestions( Topic::Sports, questionsPerTopic );
    rockQuestions    = questionFactory->generateQuestions( Topic::Rock, questionsPerTopic );
}

Game::~Game()
{
}


bool Game::isPlayable()
{
    return ( howManyPlayers() >= 2 );
}

bool Game::add( string playerName )
{
    players.push_back( playerName );
    places[howManyPlayers()]       = 0;
    purses[howManyPlayers()]       = 0;
    inPenaltyBox[howManyPlayers()] = false;

    cout << playerName << " was added" << endl;
    cout << "They are player number " << players.size() << endl;
    return true;
}

int Game::howManyPlayers()
{
    return players.size();
}

void Game::roll( int roll )
{
    cout << players[currentPlayer] << " is the current player" << endl;
    cout << "They have rolled a " << roll << endl;

    if( inPenaltyBox[currentPlayer] )
    {
        if( roll % 2 != 0 )
        {
            isGettingOutOfPenaltyBox = true;

            cout << players[currentPlayer] << " is getting out of the penalty box" << endl;
            places[currentPlayer] = places[currentPlayer] + roll;
            if( places[currentPlayer] > 11 )
                places[currentPlayer] = places[currentPlayer] - 12;

            cout << players[currentPlayer] << "'s new location is " << places[currentPlayer] << endl;
            cout << "The category is " << currentCategory() << endl;
            askQuestion();
        }
        else
        {
            cout << players[currentPlayer] << " is not getting out of the penalty box" << endl;
            isGettingOutOfPenaltyBox = false;
        }
    }
    else
    {

        places[currentPlayer] = places[currentPlayer] + roll;
        if( places[currentPlayer] > 11 )
            places[currentPlayer] = places[currentPlayer] - 12;

        cout << players[currentPlayer] << "'s new location is " << places[currentPlayer] << endl;
        cout << "The category is " << currentCategory() << endl;
        askQuestion();
    }
}

void Game::askQuestion()
{
    const std::string currCategory = currentCategory();
    if( currCategory == "Pop" )
    {
        cout << popQuestions.front() << endl;
        popQuestions.pop_front();
    }
    else if( currCategory == "Science" )
    {
        cout << scienceQuestions.front() << endl;
        scienceQuestions.pop_front();
    }
    else if( currCategory == "Sports" )
    {
        cout << sportsQuestions.front() << endl;
        sportsQuestions.pop_front();
    }
    else if( currCategory == "Rock" )
    {
        cout << rockQuestions.front() << endl;
        rockQuestions.pop_front();
    }
}


string Game::currentCategory()
{
    constexpr const unsigned short categoryCount = 4;
    switch( places[currentPlayer] % categoryCount )
    {
        case 0: return "Pop";
        case 1: return "Science";
        case 2: return "Sports";
        default: return "Rock";
    }
}

bool Game::wasCorrectlyAnswered()
{
    if( inPenaltyBox[currentPlayer] )
    {
        if( isGettingOutOfPenaltyBox )
        {
            cout << "Answer was correct!!!!" << endl;
            purses[currentPlayer]++;
            cout << players[currentPlayer]
                 << " now has "
                 << purses[currentPlayer]
                 << " Gold Coins." << endl;

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

        cout << "Answer was corrent!!!!" << endl;
        purses[currentPlayer]++;
        cout << players[currentPlayer]
             << " now has "
             << purses[currentPlayer]
             << " Gold Coins." << endl;

        bool winner = didPlayerWin();
        currentPlayer++;
        if( currentPlayer == players.size() )
            currentPlayer = 0;

        return winner;
    }
}

bool Game::wrongAnswer()
{
    cout << "Question was incorrectly answered" << endl;
    cout << players[currentPlayer] + " was sent to the penalty box" << endl;
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
