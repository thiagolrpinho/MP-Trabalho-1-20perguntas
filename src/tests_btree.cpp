#ifndef  MP_TRABALHO1_CATCH_H_INCLUDED   
#define  MP_TRABALHO1_CATCH_H_INCLUDED
#include "catch.hpp"
#include "btree.hpp"


//! These tests will be focused on binary trees
//! They'll be considered fully functional if they pass in
//! four test cases: Create, Read, Update and Destroy

TEST_CASE( "Binary Tree CRUD", "[binary_tree]" ) {
  BTree* ptestTree = nullptr;
  ptestTree = new BTree();

  SECTION( "Creating an empty tree root" ) {
    REQUIRE_FALSE( ptestTree == nullptr );
    REQUIRE( ptestTree->getLeftBranch() == nullptr );
    REQUIRE( ptestTree->getRightBranch() == nullptr);
    REQUIRE( ptestTree->getText() == nullptr);
    }

  SECTION( "Creating a non empty tree root"){
    string initialText = "É verde?";
    BTree* pNonEmptyTestTree = new BTree(initialText);
    REQUIRE( pNonEmptyTestTree->getText()->compare("É verde?"));
  }
}


#endif //CATCH_H_INCLUDED
