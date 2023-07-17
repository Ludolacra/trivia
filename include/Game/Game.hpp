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
    explicit Game( std::shared_ptr<Abstract::QuestionFactory> questionFactory = std::make_shared<Generative::QuestionFactory>() );
    ~Game();

    void addPlayer( std::shared_ptr<Abstract::Player> newPlayer );
    void play();

private:
    std::vector<std::shared_ptr<Abstract::Player>> mPlayers;
    std::map<Topic, std::list<std::string>> mQuestions;

    inline bool isPlayable() const
    {
        return mPlayers.size() >= 2;
    }

    inline bool hasPlayerCollectedEnoughCoins( std::shared_ptr<Abstract::Player>& currentPlayer )
    {
        return currentPlayer->getCoinCount() == 6;
    }

    void handlePlayerTurn( std::shared_ptr<Abstract::Player>& currentPlayer );
    bool handlePenalty( std::shared_ptr<Abstract::Player>& currentPlayer, unsigned short lastRoll );
    void askQuestion( std::shared_ptr<Abstract::Player>& currentPlayer );
    void handleCorrectAnswer( std::shared_ptr<Abstract::Player>& currentPlayer );
    void handleIncorrectAnswer( std::shared_ptr<Abstract::Player>& currentPlayer );

    std::string getNextQuestion( const Topic topic );

    Topic getCurrentCategory( const unsigned short location );
};

#endif /* GAME_HPP_ */
