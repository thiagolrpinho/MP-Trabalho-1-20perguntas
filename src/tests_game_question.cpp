#include "game_question.hpp"

typedef shared_ptr<GameQuestion> PGAMEQUESTION;
/*
THESE TESTS WILL BE FOCUSED ON THE  QUESTIONS OF 
  THE 20_QUESTIONS GAME
  It'll be consired fully functional if they pass on
  four test cases:
    Create questions, Read questions, update question
    and delete questions
*/

TEST_CASE( "CREATE QUESTIONS", "[20_QUESTION_GAME_Questions]" )
{
  PGAMEQUESTION pGameQuestion(new GameQuestion( "Do you like cakes?" ));
  //The're will be two types of game nodes an answer which is a leaf(both 
  //branches are null) or a question which can have an answer or another question
  //on their branches
  SECTION( "creating some question" )
  {
    PGAMEQUESTION pGameQuestion(new GameQuestion());

    REQUIRE_FALSE( pGameQuestion == nullptr );
  }

  SECTION( "creating an empty question" )
  { 
    PGAMEQUESTION pEmptyGameQuestion(new GameQuestion());

    REQUIRE( pEmptyGameQuestion->getThisQuestion().empty());

  }

  SECTION( "creating a non empty question" )
  { 
    REQUIRE_FALSE( pGameQuestion->getThisQuestion().empty());
  }


  SECTION( "creating a don't know type of question" )
  { 
    pGameQuestion->newYesAnswer();
    REQUIRE(pGameQuestion->getYes() == nullptr);
    REQUIRE(pGameQuestion->getYes()->getText().empty());
  }
} //TEST CASE CREATING GAME QUESTION