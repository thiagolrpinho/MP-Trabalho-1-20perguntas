#include "game_engine.hpp"

typedef shared_ptr<GameEngine> PGameEngine;
typedef shared_ptr<StringNode> PStringNode;

/*
THESE TESTS WILL BE FOCUSED ON THE ENGINE SYSTEM OF 
  THE 20_QUESTIONS GAME
  It'll be consired fully functional if it pass on
  four test cases:
    Moving to Yes or No, Guessing, learn new guess
    and reseting.
*/


TEST_CASE( "Move to Yes or No", "[20_QUESTION_GAME_ENGINE]" )
{
    PGameEngine p_new_game( new GameEngine("É verde?") );
    SECTION("Can decide if there's no answer")
    {   
        REQUIRE( p_new_game->getYes() == nullptr );
        REQUIRE( p_new_game->moveToYes() == Error );
    }
}