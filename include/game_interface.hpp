#ifndef GAME_INTERFACE_HPP
#define GAME_INTERFACE_HPP

#include "game_engine.hpp"
#include <iostream>
using std::cout;
using std::cin;
using std::getline;

const static unsigned short int kEndGameCode = 27182;

typedef shared_ptr<GameEngine> PGameEngine;

/*
/////////////////////////////////////////////////////////////////////////////////
  This is library was built to abstract game interface in the game 20 questions.
  It makes the communication between the user and the game engine. 
  Each round should consist of:
    1)Read the statement.
    2)If it's a question, ask it and wait for an answer.
    Verify if the answer statement is a "don't know". If it is,
    then ask the user what should be the right answer and write it
    there. If not, follow to step 3.
      if it's an answer, show it an wait to know if it's right.
    In case it's right, just finish the game. Case not, ask the
    user for a question that would lead to the right answer and
    the right answer on the correspondent branch.
    3)Repeat until answer or a "don't know".
/////////////////////////////////////////////////////////////////////////////////
*/

class GameInterface {
 private:
    PGameEngine p_game_engine_;
 
 public:
    GameInterface( void );

    PGameEngine getEngine( void );
    int doRound( void );
    int openMenu( void );

  //Menu Methods
    int startNewGame( void );
    int loadSavedGame( void );
    int saveActualGame( void );
    int exitGame(void);

  //Auxiliary methods
    int gotAnswer( void );
    int gotQuestion( void );
    int validYesInput( string user_input );
    int finishGame( void );
};

#endif
