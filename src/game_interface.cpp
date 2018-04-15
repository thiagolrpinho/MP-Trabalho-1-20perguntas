#include "game_interface.hpp"


GameInterface::GameInterface( void )
{
  p_game_engine_.reset( new GameEngine());
}





PGameEngine GameInterface::getEngine( void )
{
  return this->p_game_engine_;
}

/*
 Each round should consist of:
    1)Read the statement.
    2) 
      if it's an answer, show it an wait to know if it's right.
    In case it's right, just finish the game. Case not, ask the
    user for a question that would lead to the right answer and
    the right answer on the Yes branch.
      If it's a question, ask it and wait for an answer.
    Verify if the answer statement is a "don't know". If it is,
    then ask the user what should be the right answer and write it
    there. If not, follow to step 3.
    3)Repeat until answer or a "don't know".
*/

int GameInterface::doRound( void )
{
  string actual_statement;

  
  //If it's an answer:
  if( getEngine()->checkGuess() == Sucess ) return gotAnswer();
  return gotQuestion();
  
  return Error;
}





/*
  if it's an answer, show it an wait to know if it's right.
  In case it's right, just finish the game. Case not, ask the
  user for a question that would lead to the right answer and
  the right answer on the Yes branch.
*/

int GameInterface::gotAnswer( void )
{
  string user_input_yes_or_something_else, user_input_right_yes_question;
  string user_input_right_answer;

  cout << " Answer: ";
  cout << getEngine()->readActualNode();
  cout <<"\n";
  cout << "  Is this correct? ";
  cout << " Write Yes if and only if it's correct. \n";
  cin >> user_input_yes_or_something_else;
  cin.ignore(); //Ignores ENTER input
  if ( validYesInput( user_input_yes_or_something_else ) == Sucess ) 
  {
    return Sucess;
    //TODO FINISH GAME METHOD
    //finishGame();
  }


  //The actual answer will become a question that will lead to the right answer
  cout << "\n What question which answering Yes would lead to your answer? \n";
  getline(cin, user_input_right_yes_question);

  if ( getEngine()->writeInActualNode( user_input_right_yes_question ) == Error )
  {
    return Error;
  }

  //The Yes Branch will have the right answer.
  cout << "\n What is the right answer? \n";
  getline(cin, user_input_right_answer);
  if ( getEngine()->newYesAnswer( user_input_right_answer ) == Error )
  {
    return Error;
  }

  return Sucess;
  //TODO FINISH GAME METHOD
  //finishGame();
  
};//GOT ANSWER



/*
  If it's a question, ask it and wait for an answer.
Verify if the answer statement is a "don't know". If it is,
then ask the user what should be the right answer and write it
there. If not, follow to step 3.
*/
int GameInterface::gotQuestion( void ) 
{
  string user_input_yes_or_something_else;
  string user_input_right_answer;

  cout << " Question: ";
  cout << getEngine()->readActualNode();
  cout <<"\n";
  cout << "  Is this correct? ";
  cout << " Write Yes if and only if it's correct. \n";
  cin >> user_input_yes_or_something_else;
  cin.ignore(); //Ignores ENTER input

  if ( validYesInput( user_input_yes_or_something_else ) == Sucess ) 
  {
    //If move results in Error, it's a don't know
    if( getEngine()->moveToYes() == Sucess ) 
    {
      doRound();
      return Sucess;
    } 
    //If it doesn't know, the game learns and stores it.
    cout << "\n Then I don't know what is the answer. \n";
    cout << "\n What is the right answer? \n";
    getline(cin, user_input_right_answer);
    if ( getEngine()->newYesAnswer( user_input_right_answer ) == Error )
    {
      return Error;
    }

    return Sucess;
    //TODO FINISH GAME METHOD
    //finishGame();

  } else { 
    if( getEngine()->moveToNo() == Sucess )
    { 
      doRound();
      return Sucess;
    }
    //If it doesn't know, the game learns and stores it.
    cout << "\n Then I don't know what is the answer. \n";
    cout << "\n What is the right answer? \n";
    getline(cin, user_input_right_answer);
    if ( getEngine()->newNoAnswer( user_input_right_answer ) == Error )
    {
      return Error;
    }

    return Sucess;
    //TODO FINISH GAME METHOD
    //finishGame();

  } //IF VALID YES INPUT

}; //GOT QUESTION


int GameInterface::validYesInput( string user_input )
{
   if ( user_input.compare("Yes") == Equals ) return Sucess;
   return Error;
};