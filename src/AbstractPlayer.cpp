#include "Abstract/Player.hpp"

#include <cstdlib>
#include <ctime>

#include "Game/Game.hpp"


namespace Abstract
{
    Player::Player( const std::string& name ) :
        mName( name ),
        mCoins( 0 ),
        mBoardLocation( 0 ),
        mIsPenalized( false )
    {
        std::srand( std::time( nullptr ) );
    }

    void Player::move( unsigned int steps )
    {
        mBoardLocation += steps;
        if( mBoardLocation >= Game::BoardSize )
        {
            mBoardLocation %= Game::BoardSize;
        }
    }

    unsigned int Player::getCoinCount() const
    {
        return mCoins;
    }

    unsigned int Player::getLocation() const
    {
        return mBoardLocation;
    }

    bool Player::isInPenalty() const
    {
        return mIsPenalized;
    }

    void Player::receiveReward()
    {
        ++mCoins;
    }

    void Player::moveToPenalty()
    {
        mIsPenalized = true;
    }

    void Player::removeFromPenalty()
    {
        mIsPenalized = false;
    }

    unsigned short Player::rollDice() const
    {
        return std::rand() % 5 + 1;
    }
}
