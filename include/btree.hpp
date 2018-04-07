#ifndef BTREE_HPP
#define BTREE_HPP

#include "stringnode.hpp"


class BTree {
 private:
  StringNode* rootNode;

 public:
 //Methods
  BTree();
  BTree(string initialText);
  StringNode* getRoot(void) { return this->rootNode; };



};



#endif