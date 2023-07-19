#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

#include "Abstract/Player.hpp"

using namespace testing;

namespace UT
{
    class Player : public Abstract::Player
    {
    public:
        Player( const std::string& name ) :
            Abstract::Player( name )
        {
        }

        MOCK_METHOD( bool, answer, (const std::string&), ( const, override ) );
    };

    TEST( PlayerTest, nameIsReturned )
    {
        const std::string aName( "dummy" );
        Player testedPlayer( aName );

        ASSERT_EQ( aName, testedPlayer.getName() );
    }

    TEST( PlayerTest, coinsAreUpdated )
    {
        Player testedPlayer( "" );

        ASSERT_EQ( 0u, testedPlayer.getCoinCount() );
        testedPlayer.receiveReward();
        ASSERT_EQ( 1u, testedPlayer.getCoinCount() );
    }

    TEST( PlayerTest, penaltyIsUpdated )
    {
        Player testedPlayer( "" );

        ASSERT_FALSE( testedPlayer.isInPenalty() );
        testedPlayer.moveToPenalty();
        ASSERT_TRUE( testedPlayer.isInPenalty() );
        testedPlayer.removeFromPenalty();
        ASSERT_FALSE( testedPlayer.isInPenalty() );
    }

    TEST( PlayerTest, playerIsMoved )
    {
        Player testedPlayer( "" );

        ASSERT_EQ( 0u, testedPlayer.getLocation() );
        testedPlayer.move( 5 );
        ASSERT_EQ( 5u, testedPlayer.getLocation() );
    }

    TEST( PlayerTest, bigMoveIsRolledOver )
    {
        Player testedPlayer( "" );

        ASSERT_EQ( 0u, testedPlayer.getLocation() );
        testedPlayer.move( 5, 3 );
        ASSERT_EQ( 2u, testedPlayer.getLocation() );
    }

    TEST( PlayerTest, bigMoveIsRolledOverDefaultBoradSize )
    {
        Player testedPlayer( "" );

        ASSERT_EQ( 0u, testedPlayer.getLocation() );
        testedPlayer.move( 6 );
        ASSERT_EQ( 6u, testedPlayer.getLocation() );
        testedPlayer.move( 5 );
        ASSERT_EQ( 11u, testedPlayer.getLocation() );
        testedPlayer.move( 1 );
        ASSERT_EQ( 0u, testedPlayer.getLocation() );
    }
}
