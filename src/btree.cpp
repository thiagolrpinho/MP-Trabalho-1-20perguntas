#include "btree.hpp"



BTree::BTree(void){
  pRootNode.reset(new StringNode());
  
};

BTree::BTree(string initialText){
    pRootNode.reset(new StringNode(initialText));
};


