#ifndef BTREE_HPP
#define BTREE_HPP

#include "stringnode.hpp"

/*
  This is library was built to structurize a binary tree of strings
*/

class BTree {
 //The BTree class itself will work as a header of the tree
 private:
  StringNode* rootNode;

 public:
 //Methods
  BTree();
  BTree(string initialText);
  StringNode* getRoot(void) { return this->rootNode; };



};



#endif