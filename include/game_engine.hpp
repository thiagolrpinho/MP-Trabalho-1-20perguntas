#ifndef GAME_QUESTION_HPP
#define GAME_QUESTION_HPP

#include "btree.hpp"

typedef shared_ptr<StringNode> PStringNode;
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
  shared_ptr<BTree> pTreeOfStatements;
  PStringNode pActualNode;

 public:
 GameEngine();
 GameEngine(string initialText);

 //Positioning logic
 PStringNode getStart(void);
 PStringNode getActualNode(void);
 int setActualNode( PStringNode pNextNode );

 //Reading and writing values on nodes
 string readActualNode( void );
 int writeInActualNode( string newText );
 
 //Remove Statements
 int removeActualNode( void );
 //YesOrNo Logic
 int newYesAnswer(void);
 int newYesAnswer(string initialText);
 int newYesQuestion(string initialQuestion);
 PStringNode getYes(void);

};



#endif