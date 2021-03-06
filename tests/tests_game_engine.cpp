#include "game_engine.hpp"

typedef shared_ptr<GameEngine> PGameEngine;
typedef shared_ptr<StringNode> PStringNode;

/*
THESE TESTS WILL BE FOCUSED ON THE ENGINE SYSTEM OF 
  THE 20_QUESTIONS GAME
  It'll be consired fully functional if it pass on
  four test cases:
    Moving to Yes or No, Guessing, saving, loading and restarting.
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
        REQUIRE( p_new_game->moveToYes() == Success );
    }

    SECTION( "move to No if there's an statement on No" )
    {
        p_new_game->newNoAnswer("É o céu?");
        REQUIRE_FALSE( p_new_game->getNo() == nullptr );
        REQUIRE( p_new_game->moveToNo() == Success );
    }
} //TEST CASE MOVE TO YES OR NO


TEST_CASE( "GUESSING", "[20_QUESTION_GAME_ENGINE]" )
{
    PGameEngine p_new_game( new GameEngine("É verde?") );

    SECTION( "Game engine can check if it's a guess" )
    {
        //The actual statement is a leaft, so it should be
        //a guess
        REQUIRE( p_new_game->checkGuess() == Success );

        p_new_game->newYesAnswer( "É um peixe?" );
        //Now, the actual statement is not a leaf, 
        //so it's a question
        REQUIRE( p_new_game->checkGuess() == Error );
        p_new_game->moveToYes();
        REQUIRE( p_new_game->checkGuess() == Success );
    }
} //TEST CASE GUESSING

TEST_CASE( "Restart", "[20_QUESTION_GAME_ENGINE]" )
{
    PGameEngine p_new_game( new GameEngine("É verde?") );

    SECTION( "a game can be restarted" )
    {
        REQUIRE( p_new_game->restart() == Success);
    }
    
};

TEST_CASE( "Game can be saved on a file", "[20_QUESTION_GAME_ENGINE]")
{
    PGameEngine p_new_game( new GameEngine("É verde?") );
    p_new_game->newNoAnswer( "É Azul?" );
    p_new_game->moveToNo();
    p_new_game->newYesAnswer( "É o céu!");
   

    SECTION("Game engine can write on files already opened")
    {
        fstream p_file_to_write;
        p_file_to_write.open("./saved_games/test_write.txt", std::fstream::out);
        REQUIRE( p_file_to_write.is_open() );
        REQUIRE( p_new_game->writeInFile( p_file_to_write ) == Success);
        p_file_to_write.close();
    }

    
    SECTION( "Game engine can open files to write" )
    {
        REQUIRE( p_new_game->saveGame() == Success );
    }

}//TEST_CASE GAME SAVE

TEST_CASE( "Game load", "[20_QUESTION_GAME_ENGINE]")
{
    
    PGameEngine p_game_to_be_saved( new GameEngine("É verde?") );
    p_game_to_be_saved->newNoAnswer( "É Azul?" );
    p_game_to_be_saved->moveToNo();
    p_game_to_be_saved->newYesAnswer( "É o céu!" );

    p_game_to_be_saved->saveGame("test_load");

    PGameEngine p_new_game( new GameEngine() );

    SECTION("Game engine can read files already opened")
    {
        fstream p_file_to_read;
        p_file_to_read.open("./saved_games/test_load", std::fstream::in);
        REQUIRE( p_file_to_read.is_open() );
        REQUIRE( p_new_game->readFile( p_file_to_read ) == Success);
        p_file_to_read.close();

        CHECK( p_new_game->getActualNode() == p_new_game->getStart() );
        REQUIRE( p_new_game->readActualNode().compare("É verde?") == Equals );
        REQUIRE( p_new_game->moveToYes() == Error );
        REQUIRE( p_new_game->moveToNo() == Success );
        CHECK( p_new_game->readActualNode().compare( "É Azul?" ) == Equals );
        REQUIRE( p_new_game->moveToNo() == Error );
        REQUIRE( p_new_game->moveToYes() == Success );
        CHECK( p_new_game->readActualNode().compare( "É o céu!" ) == Equals );
    }

    SECTION( "Game engine can load games" )
    {
        REQUIRE( p_new_game->loadGame() == Success );
    }
}