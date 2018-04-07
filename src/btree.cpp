#include "btree.hpp"

BTree::BTree(void){
  rootNode = new StringNode();
  
}

BTree::BTree(string initialText){
    rootNode = new StringNode(initialText);
};

