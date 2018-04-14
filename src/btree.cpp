#include "btree.hpp"



BTree::BTree(void){
  p_root_node_.reset( new StringNode() );
  
};

BTree::BTree(string initialText){
    p_root_node_.reset( new StringNode(initialText) );
};


