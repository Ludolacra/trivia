#ifndef GAME_HPP_
#define GAME_HPP_

#include <string>
#include <list>
#include <vector>
#include <memory>

#include "Abstract/QuestionFactory.hpp"
#include "Generative/QuestionFactory.hpp"

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

    int places[6];
    int purses[6];

    bool inPenaltyBox[6];

    std::list<std::string> popQuestions;
    std::list<std::string> scienceQuestions;
    std::list<std::string> sportsQuestions;
    std::list<std::string> rockQuestions;

    unsigned int currentPlayer;
    bool isGettingOutOfPenaltyBox;

    void askQuestion();
    std::string currentCategory( const unsigned short location );
    bool didPlayerWin();
};

#endif /* GAME_HPP_ */
