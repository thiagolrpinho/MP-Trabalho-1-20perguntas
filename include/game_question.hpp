#ifndef GAME_QUESTION_HPP
#define GAME_QUESTION_HPP

#include "btree.hpp"

/*
  This is library was built to abstract game questions in the game 20 questions
*/

class GameQuestion {
 
 private:
  shared_ptr<BTree> pBTree;
  shared_ptr<StringNode> pActualNode;

 public:
 GameQuestion();
 GameQuestion(string initialText);
 string getThisQuestion(void){ return pBTree->getRoot()->getText(); };


};



#endif