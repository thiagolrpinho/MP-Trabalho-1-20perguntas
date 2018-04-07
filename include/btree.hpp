#ifndef BTREE_HPP
#define BTREE_HPP

#include "stringnode.hpp"
enum BTreeStatus {Error, Sucess};

class BTree {
 private:
  StringNode* rootNode;

 public:
 //Methods
  BTree();
  BTree(string initialText);
  StringNode* getLeftBranch(void){ return this->rootNode->leftBranch; }
  StringNode* getRightBranch(void){ return this->rootNode->rightBranch; }
  string getText(void) { return this->rootNode->text;}

  int insertBranch(string initialNewBranchText);

};



#endif