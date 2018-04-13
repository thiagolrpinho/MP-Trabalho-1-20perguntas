#include "game_engine.hpp"

typedef shared_ptr<GameEngine> PGameEngine;
typedef shared_ptr<StringNode> PStringNode;

/*
THESE TESTS WILL BE FOCUSED ON THE  QUESTIONS OF 
  THE 20_QUESTIONS GAME ENGINE STATEMENTS
  It'll be consired fully functional if they pass on
  four test cases:
    Create statements, Read statements, update statements
    and delete statements
*/

TEST_CASE( "CREATE STATEMENTS", "[20_QUESTION_GAME_ENGINE]" )
{
  //The're will be two types of game nodes an answer which is a leaf(both 
  //branches are null) or a question which can have an answer or another question
  //on their branches

  PGameEngine pGameEngine(new GameEngine( "Do you like cakes?" ));

  SECTION( "creating game engine" )
  {
    PGameEngine pGameEngine(new GameEngine());

    REQUIRE_FALSE( pGameEngine == nullptr );
  }

  SECTION( "creating an empty statement" )
  { 
    PGameEngine pEmptyGameEngine(new GameEngine());

    REQUIRE( pEmptyGameEngine->readActualNode().empty());

  }

  SECTION( "creating a non empty statement" )
  { 
    REQUIRE_FALSE( pGameEngine->readActualNode().empty());
  }


  SECTION( "creating an empty answer" )
  { 
    REQUIRE( pGameEngine->getYes() == nullptr );

    pGameEngine->newYesAnswer();

    REQUIRE_FALSE( pGameEngine->getYes() == nullptr );

    PStringNode pEmptyAnswer( pGameEngine->getYes() );

    REQUIRE( pEmptyAnswer->getText().empty() );
    REQUIRE( pEmptyAnswer->getLeftNode() == nullptr );
    REQUIRE( pEmptyAnswer->getRightNode() == nullptr );
  }

  SECTION( "creating a non-empty answer" )
  { 
    REQUIRE( pGameEngine->getYes() == nullptr );

    pGameEngine->newYesAnswer("É um pônei!");

    REQUIRE_FALSE( pGameEngine->getYes() == nullptr );

    PStringNode pAnswer( pGameEngine->getYes() );

    REQUIRE_FALSE( pAnswer->getText().empty() );
    REQUIRE( pAnswer->getLeftNode() == nullptr );
    REQUIRE( pAnswer->getRightNode() == nullptr );
  }

   SECTION( "creating a question" )
  { 
    REQUIRE( pGameEngine->getYes() == nullptr );
     
    pGameEngine->newYesQuestion("É um pônei?");

    REQUIRE_FALSE( pGameEngine->getYes() == nullptr );

    PStringNode pQuestion( pGameEngine->getYes() );

    REQUIRE_FALSE( pQuestion->getText().empty() );
    REQUIRE_FALSE( pQuestion->getLeftNode() == nullptr);

  }

} //TEST CASE CREATING  STATEMENTS

TEST_CASE( "READ STATEMENTS", "[20_QUESTION_GAME_ENGINE]" )
{
  PGameEngine pGameEngine(new GameEngine( "Do you like cakes?" ));

  SECTION( "An statement on root can be read" )
  {
    REQUIRE( pGameEngine->readActualNode().compare( "Do you like cakes?" ) == Equals );
  }

  SECTION( "An statement on branch can be read")
  {
    REQUIRE( pGameEngine->newYesQuestion("Do you like apples?") == Sucess );
    PStringNode pBranchStatement(pGameEngine->getYes() );
    REQUIRE( pGameEngine->setActualNode(pBranchStatement) == Sucess );
    REQUIRE( pGameEngine->readActualNode().compare( "Do you like apples?" ) == Equals);
  }
} //TEST CASE READ STATEMENTS


TEST_CASE( "UPDATE STATEMENTS", "[20_QUESTION_GAME_ENGINE]" )
{
  PGameEngine pGameEngine(new GameEngine( "Do you like cakes?" ));

  SECTION( "An statement on root can be updated" )
  {
    REQUIRE( pGameEngine->writeInActualNode("Do you like pies?") == Sucess );
    REQUIRE( pGameEngine->readActualNode().compare("Do you like pies?") == Equals );
  }

  SECTION( "An statement on branch can be updated")
  {
    REQUIRE( pGameEngine->newYesQuestion("Do you like apples?") == Sucess );
    PStringNode pBranchStatement(pGameEngine->getYes() );
    REQUIRE( pGameEngine->setActualNode(pBranchStatement) == Sucess );
    REQUIRE( pGameEngine->writeInActualNode("Do you like watermellon?") == Sucess );
    REQUIRE( pGameEngine->readActualNode().compare("Do you like watermellon?") == Equals );
  }
} //TEST CASE UPDATE STATEMENTS