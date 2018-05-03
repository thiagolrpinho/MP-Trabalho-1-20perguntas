#include "btree.hpp"

/*! \file btree.cpp
    \brief Module which contains the methods of the class btree
*/

//! A constructor that creates a binary tree with a root with an empty value.
    /*!
        \Description Creates a new binary tree 
        and creates a new node to be it's root.
        The root value is empty.
    */
BTree::BTree(void){
  p_root_node_.reset( new StringNode() );
  
};

//! A constructor that creates a binary tree with a root with an given value.
    /*!
        \Description Creates a new binary tree 
        and creates a new node to be it's root.
        The root value is given as param.
        \param An already created string.
    */
BTree::BTree(string initialText){
    p_root_node_.reset( new StringNode(initialText) );
};


