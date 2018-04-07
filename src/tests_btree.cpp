#ifndef  MP_TRABALHO1_CATCH_H_INCLUDED   
#define  MP_TRABALHO1_CATCH_H_INCLUDED
#include "catch.hpp"
#include "btree.hpp"


//! These tests will be focused on binary trees
//! They'll be considered fully functional if they pass in
//! four test cases: Create, Read, Update and Destroy

TEST_CASE( "Binary Tree CRUD", "[binary_tree]" ) {
  BTree * ptestTree = nullptr;
  ptestTree = new BTree();

  SECTION( "Creating a Tree and its leafs" ) {
    REQUIRE_FALSE( ptestTree == nullptr );
    }
}


#endif //CATCH_H_INCLUDED
