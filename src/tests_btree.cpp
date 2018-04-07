#ifndef  MP_TRABALHO1_CATCH_H_INCLUDED   
#define  MP_TRABALHO1_CATCH_H_INCLUDED
#include "catch.hpp"
#include "btree.hpp"


//! These tests will be focused on binary trees
//! They'll be considered fully functional if they pass in
//! four test cases: Create, Read, Update and Destroy

TEST_CASE( "Binary Tree CRUD", "[binary_tree]" ) {
  string initialText = "É verde?";

  BTree* pEmptyTestTree    = new BTree();
  BTree* pNonEmptyTestTree = new BTree(initialText);


  SECTION( "Creating an empty tree root" ) {
    REQUIRE_FALSE( pEmptyTestTree == nullptr );
    REQUIRE( pEmptyTestTree->getLeftBranch() == nullptr );
    REQUIRE( pEmptyTestTree->getRightBranch() == nullptr);
    REQUIRE( pEmptyTestTree->getText().empty());
    }

  SECTION( "Creating a non empty tree root"){
    REQUIRE( pNonEmptyTestTree->getText().compare("É verde?") == 0);
  }

  SECTION( "Inserting left branch on root")
  {
    
    REQUIRE_FALSE( pNonEmptyTestTree->insertBranch("É azul?") == Error);
    REQUIRE(pNonEmptyTestTree->getLeftBranch()->text.compare("É azul?") == 0);
  }

  SECTION( "Inserting right branch on root")
  {
    REQUIRE_FALSE( pNonEmptyTestTree->insertBranch("É vermelho") == Error);
    REQUIRE(pNonEmptyTestTree->getLeftBranch()->text.compare("É azul?") == 0);
    REQUIRE(pNonEmptyTestTree->getRightBranch()->text.compare("É vermelho?") == 0);
  }
}


#endif //CATCH_H_INCLUDED
