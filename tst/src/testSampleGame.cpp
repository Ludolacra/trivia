#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Abstract/Player.hpp"
#include "Game/Game.hpp"

using namespace testing;

const std::string_view sampleGameOutput = R"(Clever was added
They are player number 1
Unlucky was added
They are player number 2
Clever is the current player
They have rolled a 1
Clever's new location is 1
The category is Science
Science Question 0
Answer was correct!!!!
Clever now has 1 Gold Coins.
Unlucky is the current player
They have rolled a 2
Unlucky's new location is 2
The category is Sports
Sports Question 0
Question was incorrectly answered
Unlucky was sent to the penalty box
Clever is the current player
They have rolled a 1
Clever's new location is 2
The category is Sports
Sports Question 1
Answer was correct!!!!
Clever now has 2 Gold Coins.
Unlucky is the current player
They have rolled a 2
Unlucky is not getting out of the penalty box
Clever is the current player
They have rolled a 1
Clever's new location is 3
The category is Rock
Rock Question 0
Answer was correct!!!!
Clever now has 3 Gold Coins.
Unlucky is the current player
They have rolled a 2
Unlucky is not getting out of the penalty box
Clever is the current player
They have rolled a 1
Clever's new location is 4
The category is Pop
Pop Question 0
Answer was correct!!!!
Clever now has 4 Gold Coins.
Unlucky is the current player
They have rolled a 2
Unlucky is not getting out of the penalty box
Clever is the current player
They have rolled a 1
Clever's new location is 5
The category is Science
Science Question 1
Answer was correct!!!!
Clever now has 5 Gold Coins.
Unlucky is the current player
They have rolled a 2
Unlucky is not getting out of the penalty box
Clever is the current player
They have rolled a 1
Clever's new location is 6
The category is Sports
Sports Question 2
Answer was correct!!!!
Clever now has 6 Gold Coins.
)";

namespace UT
{
    class ControlledPlayer : public ::Abstract::Player
    {
    public:
        using Player::Player;

        MOCK_METHOD( bool, answer, (const std::string&), ( const, override ) );
        MOCK_METHOD( unsigned short, rollDice, (), ( const, override ) );
    };

    TEST( ExampleGame, testGameWithASmartAndAnUnluckyPlayer )
    {
        auto cleverPlayer  = std::make_shared<ControlledPlayer>( "Clever" );
        auto unluckyPlayer = std::make_shared<ControlledPlayer>( "Unlucky" );

        EXPECT_CALL( *cleverPlayer, answer ).Times( 6 ).WillRepeatedly( Return( true ) );
        EXPECT_CALL( *cleverPlayer, rollDice ).Times( 6 ).WillRepeatedly( Return( 1 ) );
        EXPECT_CALL( *unluckyPlayer, rollDice ).Times( 5 ).WillRepeatedly( Return( 2 ) );
        EXPECT_CALL( *unluckyPlayer, answer ).WillOnce( Return( false ) );

        Game sampleGame;

        testing::internal::CaptureStdout();
        sampleGame.addPlayer( cleverPlayer );
        sampleGame.addPlayer( unluckyPlayer );
        sampleGame.play();
        const std::string result = testing::internal::GetCapturedStdout();

        ASSERT_EQ( result, sampleGameOutput );
    }
}
