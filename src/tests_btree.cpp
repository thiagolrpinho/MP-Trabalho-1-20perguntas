#ifndef  MP_TRABALHO1_CATCH_H_INCLUDED   
#define  MP_TRABALHO1_CATCH_H_INCLUDED
#include "catch.hpp"
#include "btree.hpp"


//! These tests will be focused on binary trees
//! They'll be considered fully functional if they pass in
//! four test cases: Create, Read, Update and Destroy

TEST_CASE( "Binary Tree CRUD", "[binary_tree]" ) {
  string initialText = "É verde?";

  BTree* pEmptyTestTree = new BTree();
  BTree* pNonEmptyTestTree = new BTree(initialText);


  SECTION( "Creating an empty tree root" ) {
    StringNode* pRoot = pEmptyTestTree->getRoot();

    REQUIRE_FALSE( pEmptyTestTree == nullptr );
    REQUIRE( pRoot->getLeftBranch() == nullptr );
    REQUIRE( pRoot->getRightBranch() == nullptr);
    REQUIRE( pRoot->getText().empty());
    }

  SECTION( "Creating a non empty tree root"){
    REQUIRE( pNonEmptyTestTree->getRoot()->getText().compare("É verde?") == 0);
  }

  SECTION( "Inserting left branch on root")
  {
    
    REQUIRE_FALSE( pNonEmptyTestTree->getRoot()->insertBranch("É azul?") == Error);
    REQUIRE(pNonEmptyTestTree->getRoot()->getLeftBranch()->getText().compare("É azul?") == 0);
  }

  SECTION( "Inserting right branch on root")
  {
    StringNode* pRoot = pNonEmptyTestTree->getRoot();
    REQUIRE_FALSE( pRoot->insertBranch("É azul?") == Error);
    REQUIRE_FALSE( pRoot->insertBranch("É vermelho?") == Error);
    REQUIRE(pRoot->getLeftBranch()->getText().compare("É azul?") == Equals);
    REQUIRE(pRoot->getRightBranch()->getText().compare("É vermelho?") == Equals);
  }

  SECTION( "Inserting right branch on right branch of root")
  {
    StringNode* pRoot = pNonEmptyTestTree->getRoot();
    REQUIRE_FALSE( pRoot->insertBranch("É azul?") == Error);
    StringNode* pRightBranchOfRoot = pRoot->getRightBranch();

    REQUIRE_FALSE( pRightBranchOfRoot->insertBranch("É violeta?") == Error);
    REQUIRE( pRightBranchOfRoot->getText().compare("É violeta?") == Equals);
  }
}


#endif //CATCH_H_INCLUDED
