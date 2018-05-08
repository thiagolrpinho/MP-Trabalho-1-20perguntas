#include "game_interface.hpp"

/*! \file game_interface.cpp
    \brief Module which contains the methods of the class game_interface.cpp
*/

//! A constructor that creates a game interface with an empty game engine.
  /*!
    \Description Creates a game interface
    and creates a new game engine with
    an empty tree of statements.
  */
GameInterface::GameInterface( void )
{
  p_game_engine_.reset( new GameEngine());
}




//! A method that returns a pointer to the game engine.
  /*!
    \return A shared pointer for the game engine of
    the game interface
  */
PGameEngine GameInterface::getEngine( void )
{
  return this->p_game_engine_;
}




//! A method that calls a Menu
  /*!
    \brief MENU will be able to start a new game, load a saved game, 
    save the actual game, exit the game or call the playing routine.
    
    \Description 
    First it shows to the user a brief description
    of the game. 
    Then it enters in a loop:
    Shows a menu of options and then capture the input 
    of the user keyboard.
    Then it switches between the options. 

    1 - Start New game
    Calls startNewGame() and verifies if there was 
    an Error(Integer 0).
    Then it calls playingRoutine() and verifies if there
    was an Error(Integer 0). If any Error is verified,
    the method stops and returns an Error.

    2 - Load game or continue last game
    Calls loadSavedGame() method and verifies if 
    there was an Error(Integer 0) then it calls
    playingRoutine() and verifies too. If there was
    an Error(Integer 0) the method stops and returns an Error.

    3 - Save the actual game
    Calls saveActualGame() and verifies if there
    was an Error(Integer 0) if so the method stops
    and return an Error(Integer 0).

    4 - Edit actual 
    Calls editRoutine() and verifies if there
    was an Error(Integer 0) if so the method
    stops and return an Error(Integer 0).
    
    5 - Exit game
    Calls exitGame() and verifies if it is
    equal to the code to end the game. If so
    the method return a Success(Integer 1).

    default - Just ask the user to write 
    \return An integer 0 for Error or 1 for Success.
  */
int GameInterface::openMenu( void )
{
  unsigned short int code_to_next_action;

  cout << "\n Welcome to the 20 games questions game. Version 0.9 \n";
  cout << " Made by Thiago Luis as a project for an University \n";
  cout << " of Brasilia's class. Date: April 2018. Last Update May 2018. \n";
  cout << " The game will try to guess what object you're thinking.\n";
  cout << " Using only yes or no questions. \n";
  
  do
  {
    cout << "\n Write: \n";
    cout << " 1 - To start new game. \n";
    cout << " 2 - To load a game or continue last game. \n";
    cout << " 3 - To save the actual game. \n";
    cout << " 4 - To edit the actual game. \n";
    cout << " 5 - To exit the game. \n \n";
    
    cin >> code_to_next_action;
    cin.ignore();

    switch(code_to_next_action)
    {
      case 1: 
        if ( startNewGame() == Error ) return Error;
        if ( playingRoutine() == Error ) return Error;
      break;

      case 2:
        if ( loadSavedGame() == Error ) return Error;
        if ( playingRoutine() == Error ) return Error;
      break;

      case 3:
        if ( saveActualGame() == Error) return Error;
      break;

      case 4:
        if ( editRoutine() == Error) return Error;
      break;

      case 5:
        if ( exitGame() == kEndGameCode ) return Success;
      break;

      default:
        cout << "\n Invalid choice, please try again. \n";
        continue;

    } //END OF SWITCH CASE

  } while( true );
  return Success;
}

//! A method that starts a new game.
  /*!
    \Description The method asks the user for
    an input from keyboard that should be the
    first initial answer of the tree of statements.
    Then it calls restart() and verifies if there
    was an Error(Integer 0) if so the method returns
    an Error(Integer 0).
    If not, it calls writeInActualNode() and returns
    what it returns. An Error(Integer 0) or a 
    Success(Integer 1).
    \return An integer 0 for Error or 1 for Success.
  */
int GameInterface::startNewGame( void )
{
  string user_input_first_answer_of_the_game;
  cout << "\n What's the initial answer of your game? \n";
  getline(cin, user_input_first_answer_of_the_game );
  if ( getEngine()->restart() == Error ) return Error;
  return getEngine()->writeInActualNode(user_input_first_answer_of_the_game);
}


//! A method that can load last game or load another game of the user's choice.
  /*!
    \Description The method asks the user if 
    \return An integer 0 for Error or 1 for Success.
  */
int GameInterface::loadSavedGame( void )
{
  string user_input_game_to_be_load;
  string user_input_yes_or_something_else;

  cout << "\n Would you like to continue your last game? \n";
  cout << " Write Yes if and only if you want. \n";
  cin >> user_input_yes_or_something_else;
  cin.ignore(); //Ignores ENTER input

  if ( validYesInput( user_input_yes_or_something_else ) == Success ) return getEngine()->loadGame("last_game");
  do{
    cout << "\n Please write the a valid txt filename that you want to load. \n";
    getline(cin, user_input_game_to_be_load );
  } while( getEngine()->loadGame(user_input_game_to_be_load) == Error );

  return Success;
} //LOAD SAVED GAME


/*
  This method can save the actual game as the last_game in a txt file of the users choice.
*/
int GameInterface::saveActualGame( void )
{
  string user_input_file_name_to_be_saved;

  do{
    cout << "\n Please write the a valid txt filename to you save on. \n";
    getline(cin, user_input_file_name_to_be_saved );
  } while( getEngine()->saveGame(user_input_file_name_to_be_saved) == Error );

  return Success;

}//SAVE ACTUAL GAME

int GameInterface::playingRoutine( void )
{
  cout << "\n";
  return doRound();
}//Playing Routine

int GameInterface::editRoutine( void )
{
  cout << "\n Welcome to the edit routine. \n";
  cout << " Here you can visit each statement and decide to edit or delete it \n";
  if ( doEditRound() == Error ) return Error;
  return finishGame();
}

int GameInterface::exitGame( void )
{   
  string user_input_yes_or_something_else;
  cout << "\n Are you sure? \n";
  cout << " Write Yes if and only if you want. \n";
  cin >> user_input_yes_or_something_else;
  cin.ignore(); //Ignores ENTER input

  if ( validYesInput( user_input_yes_or_something_else ) == Error ) return Success;
  cout << "\n Right then. See you soon. \n";
  return kEndGameCode;
} //EXIT GAME


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
  
  //If it's an answer:
  if( getEngine()->checkGuess() == Success ) return gotAnswer();
  return gotQuestion();
  
  return Error;
} //DO Round

int GameInterface::doEditRound( void )
{
  string user_input_yes_or_something_else;
  string user_new_statement;

  cout << "\n Actual statement is: \n";
  cout << getEngine()->readActualNode() << " \n";
  cout << " Wanna erase this statement and those bellow it? \n";
  cout << " Write Yes if and only if it's correct. \n";
  cin >> user_input_yes_or_something_else;
  cin.ignore(); //Ignores ENTER input
  if ( validYesInput( user_input_yes_or_something_else ) == Success ) 
  {
    if ( getEngine()->removeActualNode() == Error) return Error;
    return doEditRound();
  }

  cout << " Wanna edit it's text? \n";
  cout << " Write Yes if and only if it's correct. \n";
  cin >> user_input_yes_or_something_else;
  cin.ignore(); //Ignores ENTER input
  if ( validYesInput( user_input_yes_or_something_else ) == Success ) 
  {
    do {
     getline(cin,user_new_statement);
    } while ( getEngine()->writeInActualNode(user_new_statement) == Error );
  }

  cout << " Want to edit one of it's branchs? \n";
  cout << " Write Yes to if and only if you want. \n";
  cin >> user_input_yes_or_something_else;
  cin.ignore(); //Ignores ENTER input
  if ( validYesInput( user_input_yes_or_something_else ) == Success ) 
  {
    cout << " The Yes branch? \n";
    cout << " Write Yes if and only if it's correct. \n";
    cin >> user_input_yes_or_something_else;
    cin.ignore(); //Ignores ENTER input
    if ( validYesInput( user_input_yes_or_something_else ) == Success ) 
    {
      if ( getEngine()->moveToYes() == Error )
      {
        cout << " Sorry, there's no statement on Yes. \n";
        cout << " Please, try again. \n";
        
      } 
      return doEditRound();
    }

    cout << " The No statement? \n ";
    cout << " Write Yes if and only if it's correct. \n";
    cin >> user_input_yes_or_something_else;
    cin.ignore(); //Ignores ENTER input
    if ( validYesInput( user_input_yes_or_something_else ) == Success ) 
    {
      if ( getEngine()->moveToNo() == Error )
      {
        cout << " Sorry, there's no statement on No. \n";
        cout << " Please, try again. \n";
      } 
      return doEditRound();
    }
  }

  cout << " Wanna go back to the previous statement? \n ";
  cout << " Write Yes if and only if it's correct. \n";
  cin >> user_input_yes_or_something_else;
  cin.ignore(); //Ignores ENTER input
  if ( validYesInput( user_input_yes_or_something_else ) == Success ) 
  {
    if ( getEngine()->moveBack() == Error )
    {
      cout << " Sorry, there's no statement before this one \n";
      cout << " Please, try again. \n";
    } 
    return doEditRound();
  }

  return Success;
} //Do edit round


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
  if ( validYesInput( user_input_yes_or_something_else ) == Success ) 
  {
    return finishGame();
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

  return finishGame();
  
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

  if ( validYesInput( user_input_yes_or_something_else ) == Success ) 
  {
    //If move results in Error, it's a don't know
    if( getEngine()->moveToYes() == Success ) 
    {
      
      return doRound();
    } 
    //If it doesn't know, the game learns and stores it.
    cout << "\n Then I don't know what is the answer. \n";
    cout << "\n What is the right answer? \n";
    getline(cin, user_input_right_answer);
    if ( getEngine()->newYesAnswer( user_input_right_answer ) == Error )
    {
      return Error;
    }

    return finishGame();

  } else { 
    if( getEngine()->moveToNo() == Success )
    { 
      
      return doRound();
    }
    //If it doesn't know, the game learns and stores it.
    cout << "\n Then I don't know what is the answer. \n";
    cout << "\n What is the right answer? \n";
    getline(cin, user_input_right_answer);
    if ( getEngine()->newNoAnswer( user_input_right_answer ) == Error )
    {
      return Error;
    }

    return finishGame();

  } //IF VALID YES INPUT

}; //GOT QUESTION


int GameInterface::validYesInput( string user_input )
{
   if ( user_input.compare("Yes") == Equals ) return Success;
   if ( user_input.compare("YES") == Equals ) return Success;
   if ( user_input.compare("yES") == Equals ) return Success;
   if ( user_input.compare("Y") == Equals ) return Success;
   if ( user_input.compare("y") == Equals ) return Success;

   if ( user_input.compare("Sim") == Equals ) return Success;
   if ( user_input.compare("sim") == Equals ) return Success;
   if ( user_input.compare("s") == Equals ) return Success;
   return Error;
};

int GameInterface::finishGame( void )
{
  cout << "\n Thank you for playing the 20 questions game.\n \n";
  if ( getEngine()->saveGame("last_game") == Error ) return Error;

  return Success;
  
}
