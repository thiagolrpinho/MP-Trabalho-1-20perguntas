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


/*TEST_CASE( "Round ", "[20_QUESTION_GAME_INTERFACE]" )
{   
    PGameInterface p_new_interface(new GameInterface());
    //SET GAME STATE TO SECOND SECTION
    p_new_interface->getEngine()->writeInActualNode("É o céu!");
    p_new_interface->getEngine()->saveGame("test_final_answer");

    SECTION("It can perform a final round with answer")
    { 
      p_new_interface->getEngine()->loadGame("test_final_answer");
      CHECK( p_new_interface->doRound( ) == Sucess );
    }


    //SET GAME STATE TO SECOND SECTION
    p_new_interface->getEngine()->writeInActualNode("É verde?");
    p_new_interface->getEngine()->newYesAnswer("É um sapo!");
    p_new_interface->getEngine()->saveGame("test_final_dont_know");
    p_new_interface->getEngine()->moveToYes();
    p_new_interface->getEngine()->removeActualNode();

    SECTION("It can perform a final round with don't know")
    {
      p_new_interface->getEngine()->loadGame("test_final_dont_know");
      CHECK( p_new_interface->doRound( ) == Sucess );
    }


    //SET GAME STATE TO THIRD SECTION
    p_new_interface->getEngine()->newYesAnswer("É um anfíbio?");
    p_new_interface->getEngine()->moveToYes();
    p_new_interface->getEngine()->newYesAnswer("Ele coacha?");
    p_new_interface->getEngine()->moveToYes();
    p_new_interface->getEngine()->newYesAnswer("É um sapo!");
    p_new_interface->getEngine()->saveGame("test_multiple_rounds");

    SECTION("It can perform multiple rounds")
    {
      p_new_interface->getEngine()->loadGame("test_multiple_rounds");
      
      CHECK( p_new_interface->doRound( ) == Sucess );
    }

}//TEST CASE EXISTS
*/


TEST_CASE( "Menu", "[20_QUESTION_GAME_INTERFACE]" )
{   
    PGameInterface p_interface_with_menu( new GameInterface());
    /*
    SECTION("can start new game")
    {
        REQUIRE( p_interface_with_menu->startNewGame() == Sucess );
    }

    SECTION("can load a saved game")
    {
        REQUIRE( p_interface_with_menu->loadSavedGame() == Sucess );
    }

    SECTION("can save the actual game")
    {
        REQUIRE( p_interface_with_menu->saveActualGame() == Sucess );
    }

    SECTION("can exit the game")
    {
        REQUIRE( p_interface_with_menu->exitGame() == kEndGameCode );
    }
    */
    
    SECTION("Has a menu")
    {
        REQUIRE( p_interface_with_menu->openMenu() == Sucess );
    }
    
} //TEST CASE 