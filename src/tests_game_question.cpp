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
  SECTION( "creating some question" )
  {
    PGAMEQUESTION pGameQuestion(new GameQuestion());

    REQUIRE_FALSE( pGameQuestion == nullptr );
  }

  SECTION( "creating a empty question" )
  { 
    PGAMEQUESTION pEmptyGameQuestion(new GameQuestion());

    REQUIRE( pEmptyGameQuestion->getThisQuestion()  == "Equals ");

  }
}