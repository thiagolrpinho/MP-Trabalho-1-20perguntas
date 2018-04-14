#ifndef GAME_QUESTION_HPP
#define GAME_QUESTION_HPP

#include <stack>
using std::stack;
#include <fstream>
using std::fstream;

#include "btree.hpp"

typedef shared_ptr<StringNode> PStringNode;
typedef stack<PStringNode> StackOfStringNodes;
/*
  This is library was built to abstract game engine in the game 20 questions.
  Each node represents an statement. 
  Trying to acess nullpointer is considered a don't know. The game should return
  "don't know" to the user and he/she will be asked what were the right answer. 
  A node with both branches null will be considered an Answer. If the answer
  is right, the game ends. If it's not, the user'll be asked to write the right
  one and the wrong answer will become a question of Yes or No which should
  lead to the right answer.
  A question is a node that is not null or have it's branches null.
  The game engine have two pointers, one to the start of the game and another
  to the actual node. 

*/

class GameEngine {
 
 private:
  shared_ptr<BTree> p_tree_of_statements_;
  PStringNode p_actual_node_;
  StackOfStringNodes stack_of_last_nodes_;  

 public:
 GameEngine();
 GameEngine( string initial_text );

 //Positioning logic
 PStringNode getStart(void);
 PStringNode getActualNode(void);
 PStringNode popLastNode(void);
 int setActualNode( PStringNode p_next_node );
 int pushLastNode( void ); //If no node is passed, Actual Node will be added to last
 int pushLastNode( PStringNode p_next_node );

 int moveToYes( void );
 int moveToNo( void );
 int moveBack( void );
 int restart( void );
 //Reading and writing values on nodes
 string readActualNode( void );
 int writeInActualNode( string new_text );
 
 //Remove Statements
 int removeActualNode( void );
 //YesOrNo Logic
 int newYesAnswer( void );
 int newYesAnswer(string initial_text);
 int newNoAnswer(string initial_text);
 int newYesQuestion(string initial_question);
 PStringNode getYes( void );
 PStringNode getNo( void );

 //Question Logic
 int checkGuess( void );

 //File managing
 int saveGame( void );
 int loadGame( void );
 int readFile( void );
 int writeInFile( fstream &p_file_to_write );

};



#endif