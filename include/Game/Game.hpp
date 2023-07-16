#ifndef GAME_HPP_
#define GAME_HPP_

#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Abstract/Player.hpp"
#include "Abstract/QuestionFactory.hpp"
#include "Generative/QuestionFactory.hpp"
#include "Game/Topic.hpp"

class Game
{
public:
    Game( std::shared_ptr<Abstract::QuestionFactory> questionFactory = std::make_shared<Generative::QuestionFactory>() );
    ~Game();

    void addPlayer( std::shared_ptr<Abstract::Player> newPlayer );

    bool isPlayable();

    void roll( int roll );

    bool wasCorrectlyAnswered();
    bool wrongAnswer();

private:
    std::vector<std::shared_ptr<Abstract::Player>> mPlayers;
    std::vector<std::shared_ptr<Abstract::Player>>::iterator mCurrentPlayer;
    std::map<Topic, std::list<std::string>> mQuestions;

    void setNextPlayer();

    void askQuestion();
    Topic currentCategory( const unsigned short location );
    bool didPlayerWin();
};

#endif /* GAME_HPP_ */
