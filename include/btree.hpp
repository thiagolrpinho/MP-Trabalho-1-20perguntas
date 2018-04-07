#ifndef BTREE_HPP
#define BTREE_HPP

#include "stringnode.hpp"

class BTree {
 private:
  StringNode* rootNode;

 public:
 //Methods
  BTree();
  StringNode* getLeftBranch(void){ return this->rootNode->leftBranch; }
  StringNode* getRightBranch(void){ return this->rootNode->rightBranch; }
  string* getText(void) { return this->rootNode->text;}

};



#endif