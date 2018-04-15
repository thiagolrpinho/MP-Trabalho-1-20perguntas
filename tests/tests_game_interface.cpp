#include "game_interface.hpp"

typedef shared_ptr<GameInterface> PGameInterface;


/*
THESE TESTS WILL BE FOCUSED ON THE INTERFACE OF 
  THE 20_QUESTIONS GAME
  It'll be consired fully functional if it pass on
  four test cases:
    Existing, Perfoming a round.
*/


TEST_CASE( "Exists: ", "[20_QUESTION_GAME_INTERFACE]" )
{   
    PGameInterface p_new_interface(new GameInterface());
    SECTION("a game interface can be created")
    {   
        
        CHECK_FALSE( p_new_interface == nullptr );
    }

    SECTION(" a game interface have an engine")
    {
        REQUIRE_FALSE( p_new_interface->getEngine() == nullptr );
    }

}//TEST CASE EXISTS


TEST_CASE( "Round ", "[20_QUESTION_GAME_INTERFACE]" )
{   
    PGameInterface p_new_interface(new GameInterface());

    SECTION("It can perform a final round with answer")
    {   
     p_new_interface->getEngine()->writeInActualNode("É o céu!");
    CHECK( p_new_interface->doRound( ) == Sucess );
    }

    SECTION("It can perform a final round with don't know")
    {
       p_new_interface->getEngine()->writeInActualNode("É verde?");
       p_new_interface->getEngine()->newYesAnswer("É um sapo!");
       CHECK( p_new_interface->doRound( ) == Sucess );
    }

}//TEST CASE EXISTS