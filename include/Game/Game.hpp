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
    static constexpr unsigned short BoardSize = 12;

    explicit Game( std::shared_ptr<Abstract::QuestionFactory> questionFactory =
                       std::make_shared<Generative::QuestionFactory>() );
    ~Game() = default;

    void addPlayer( std::shared_ptr<Abstract::Player> newPlayer );
    void play();

private:
    static constexpr unsigned short msMinimumPlayerCount   = 2;
    static constexpr unsigned short msConisNeededToWinGame = 6;

    std::vector<std::shared_ptr<Abstract::Player>> mPlayers;
    std::map<Topic, std::list<std::string>> mQuestions;

    inline bool isPlayable() const
    {
        return mPlayers.size() >= msMinimumPlayerCount;
    }

    inline bool hasPlayerCollectedEnoughCoins( const unsigned short coinCount )
    {
        return coinCount == msConisNeededToWinGame;
    }

    /*
        These functions control the gameflow.
        It can be argued that since they operate on the player, they should be moved to members of the Player class
        i"ve decided agains that to keep as much of the logic the this class as possible.
    */
    void handlePlayerTurn( std::shared_ptr<Abstract::Player> currentPlayer );
    bool playerMustSkipTurn( std::shared_ptr<Abstract::Player> currentPlayer, unsigned short lastRoll );
    void handleCorrectAnswer( std::shared_ptr<Abstract::Player> currentPlayer );
    void handleIncorrectAnswer( std::shared_ptr<Abstract::Player> currentPlayer );

    std::string getNextQuestion( const unsigned short playerLocation );
    Topic getCurrentCategory( const unsigned short location );
};

#endif /* GAME_HPP_ */
