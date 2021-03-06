#include "game_engine.hpp"

typedef shared_ptr<GameEngine> PGameEngine;
typedef shared_ptr<StringNode> PStringNode;

/*
THESE TESTS WILL BE FOCUSED ON THE  STATEMENTS OF 
  THE 20_QUESTIONS GAME
  It'll be consired fully functional if they pass on
  four test cases:
    Create statements, Read statements, update statements
    and delete statements
*/

TEST_CASE( "CREATE STATEMENTS", "[20_QUESTION_GAME_STATEMENT]" )
{
  //The're will be two types of game nodes an answer which is a leaf(both 
  //branches are null) or a question which can have an answer or another question
  //on their branches

  PGameEngine pGameEngine( new GameEngine( "Do you like cakes?" ) );

  SECTION( "creating game engine" )
  {
    PGameEngine pEmptyGameEngine( new GameEngine() );


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

TEST_CASE( "READ STATEMENTS", "[20_QUESTION_GAME_STATEMENT]" )
{
  PGameEngine pGameEngine(new GameEngine( "Do you like cakes?" ));

  SECTION( "An statement on root can be read" )
  {
    REQUIRE( pGameEngine->readActualNode().compare( "Do you like cakes?" ) == Equals );
  }

  SECTION( "An statement on branch can be read")
  {
    REQUIRE( pGameEngine->newYesQuestion("Do you like apples?") == Success );
    PStringNode pBranchStatement(pGameEngine->getYes() );
    REQUIRE( pGameEngine->setActualNode(pBranchStatement) == Success );
    REQUIRE( pGameEngine->readActualNode().compare( "Do you like apples?" ) == Equals);
  }
} //TEST CASE READ STATEMENTS


TEST_CASE( "UPDATE STATEMENTS", "[20_QUESTION_GAME_STATEMENT]" )
{
  PGameEngine pGameEngine(new GameEngine( "Do you like cakes?" ));

  SECTION( "An statement on root can be updated" )
  {
    REQUIRE( pGameEngine->writeInActualNode("Do you like pies?") == Success );
    REQUIRE( pGameEngine->readActualNode().compare("Do you like pies?") == Equals );
  }

  SECTION( "An statement on branch can be updated")
  {
    REQUIRE( pGameEngine->newYesQuestion("Do you like apples?") == Success );
    PStringNode pBranchStatement(pGameEngine->getYes() );
    REQUIRE( pGameEngine->setActualNode(pBranchStatement) == Success );
    REQUIRE( pGameEngine->writeInActualNode("Do you like watermellon?") == Success );
    REQUIRE( pGameEngine->readActualNode().compare("Do you like watermellon?") == Equals );
  }
} //TEST CASE UPDATE STATEMENTS

TEST_CASE( "DELETE STATEMENTS", "[20_QUESTION_GAME_STATEMENT]" )
{
  PGameEngine PGameEngine(new GameEngine());

  SECTION( "A statament can be deleted" )
  { 
    REQUIRE( PGameEngine->removeActualNode() == Success);
  }

  SECTION( "The engine will backtrace to the  statement before the one erased" ){
    PGameEngine->newYesQuestion( "É um anfíbio?" );

    PGameEngine->setActualNode(PGameEngine->getYes());

    PGameEngine->removeActualNode();

    REQUIRE( PGameEngine->getActualNode() == PGameEngine->getStart() );
  }

    SECTION( "The engine will backtrace to the  statement before the one erased many times" )
    {
    PGameEngine->newYesQuestion( "É um anfíbio?" );
    PGameEngine->pushLastNode( PGameEngine->getActualNode() );
    PGameEngine->setActualNode( PGameEngine->getYes() );

    PGameEngine->newYesQuestion( "É venenoso?" );
    PGameEngine->pushLastNode( PGameEngine->getActualNode() );
    PGameEngine->setActualNode( PGameEngine->getYes() );

    PGameEngine->removeActualNode();
    REQUIRE( PGameEngine->readActualNode().compare( "É um anfíbio?" ) == Equals );

    PGameEngine->removeActualNode();
    REQUIRE( PGameEngine->getActualNode() == PGameEngine->getStart() );
  } //The engine will backtrace many times

}