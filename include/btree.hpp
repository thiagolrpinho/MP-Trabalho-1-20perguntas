#ifndef BTREE_HPP
#define BTREE_HPP

#include "stringnode.hpp"

typedef shared_ptr<StringNode> PStringNode;
/*
  This is library was built to structurize a binary tree of strings
*/

class BTree {
 //The BTree class itself will work as a header of the tree
 private:
  PStringNode p_root_node_;

 public:
 //Methods
  BTree();
  BTree(string initial_text);
  PStringNode getRoot(void) { return this->p_root_node_; };



};



#endif