#ifndef BTREE_HPP
#define BTREE_HPP

#include "stringnode.hpp"

/*
  This is library was built to structurize a binary tree of strings
*/

class BTree {
 //The BTree class itself will work as a header of the tree
 private:
  shared_ptr<StringNode> pRootNode;

 public:
 //Methods
  BTree();
  BTree(string initialText);
  shared_ptr<StringNode> getRoot(void) { return this->pRootNode; };



};



#endif