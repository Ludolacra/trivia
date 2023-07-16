#ifndef ABSTRACT_PLAYER_HPP_
#define ABSTRACT_PLAYER_HPP_

#include <string>

namespace Abstract
{
    class Player
    {
    public:
        Player( const std::string& name );
        virtual ~Player();

        inline const std::string& getName() const
        {
            return mName;
        }

        virtual void move( unsigned int steps, unsigned int boardSize = 12 );

        virtual unsigned int getCoinCount() const;
        virtual unsigned int getLocation() const;
        virtual bool isInPenalty() const;

        virtual void receiveReward();
        virtual void moveToPenalty();
        virtual void removeFromPenalty();

        virtual unsigned short rollDice() const;
        virtual bool answer( const std::string& question ) const = 0;

    private:
        std::string mName;
        unsigned int mCoins;
        unsigned int mBoardLocation;
        bool mIsPenalized;
    };
}
#endif // ABSTRACT_PLAYER_HPP_
