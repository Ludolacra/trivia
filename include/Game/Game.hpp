#ifndef GAME_HPP_
#define GAME_HPP_

#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Abstract/QuestionFactory.hpp"
#include "Generative/QuestionFactory.hpp"
#include "Game/Topic.hpp"

class Game
{
public:
    Game( std::shared_ptr<Abstract::QuestionFactory> questionFactory = std::make_shared<Generative::QuestionFactory>() );
    ~Game();
    bool isPlayable();
    bool add( std::string playerName );

    int howManyPlayers();
    void roll( int roll );

    bool wasCorrectlyAnswered();
    bool wrongAnswer();

private:
    std::vector<std::string> players;
    std::map<Topic, std::list<std::string>> mQuestions;

    int places[6];
    int purses[6];

    bool inPenaltyBox[6];

    unsigned int currentPlayer;
    bool isGettingOutOfPenaltyBox;

    void askQuestion();
    Topic currentCategory( const unsigned short location );
    bool didPlayerWin();
};

#endif /* GAME_HPP_ */
