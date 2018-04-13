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
    SECTION("Can decide if there's no statement on Yes")
    {   
        REQUIRE( p_new_game->getYes() == nullptr );
        REQUIRE( p_new_game->moveToYes() == Error );
    }

    SECTION("Can decide if there's no statement on NO")
    {   
        REQUIRE( p_new_game->getNo() == nullptr );
        REQUIRE( p_new_game->moveToNo() == Error );
    }
    
    SECTION("move to Yes if there's an statement on Yes")
    {
        p_new_game->newYesAnswer("É o céu?");
        REQUIRE_FALSE( p_new_game->getYes() == nullptr );
        REQUIRE( p_new_game->moveToYes() == Sucess );
    }

    SECTION( "move to No if there's an statement on No" )
    {
        p_new_game->newNoAnswer("É o céu?");
        REQUIRE_FALSE( p_new_game->getNo() == nullptr );
        REQUIRE( p_new_game->moveToNo() == Sucess );
    }

    SECTION("") 
    {
        
    }
}