#ifndef  MP_TRABALHO1_CATCH_H_INCLUDED   
#define  MP_TRABALHO1_CATCH_H_INCLUDED
#include "catch.hpp"
#include "btree.hpp"


//! These tests will be focused on binary trees
//! They'll be considered fully functional if they pass in
//! four test cases: Create, Read, Update and Destroy

TEST_CASE( "Binary Tree Create and Read", "[binary_tree]" ) {
  string initialText = "É verde?";

  BTree* pEmptyTestTree = new BTree();
  BTree* pNonEmptyTestTree = new BTree(initialText);


  SECTION( "Creating an empty tree root" ) {
    shared_ptr<StringNode> pRoot = pEmptyTestTree->getRoot();

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
    shared_ptr<StringNode> pRoot = pNonEmptyTestTree->getRoot();
    REQUIRE_FALSE( pRoot->insertBranch("É azul?") == Error);
    REQUIRE_FALSE( pRoot->insertBranch("É vermelho?") == Error);
    REQUIRE(pRoot->getLeftBranch()->getText().compare("É azul?") == Equals);
    REQUIRE(pRoot->getRightBranch()->getText().compare("É vermelho?") == Equals);
  }

  SECTION( "Inserting left branch on left branch of root")
  {
    shared_ptr<StringNode> pRoot = pNonEmptyTestTree->getRoot();
    REQUIRE_FALSE( pRoot->insertBranch("É azul?") == Error);
    shared_ptr<StringNode> pLeftBranchOfRoot = pRoot->getLeftBranch();

    REQUIRE_FALSE( pLeftBranchOfRoot->insertBranch("É violeta?") == Error);
    REQUIRE( pLeftBranchOfRoot->getLeftBranch()->getText().compare("É violeta?") == Equals);
  }

   SECTION( "Inserting right and left branch on left branch of root" )
  {
    shared_ptr<StringNode> pRoot = pNonEmptyTestTree->getRoot();
    REQUIRE_FALSE( pRoot->insertBranch("É azul?") == Error);
    shared_ptr<StringNode> pLeftBranchOfRoot = pRoot->getLeftBranch();

    REQUIRE_FALSE( pLeftBranchOfRoot->insertBranch("É violeta?") == Error);
    REQUIRE( pLeftBranchOfRoot->getLeftBranch()->getText().compare("É violeta?") == Equals);
    REQUIRE_FALSE( pLeftBranchOfRoot->insertBranch("É de comer?") == Error);
    REQUIRE( pLeftBranchOfRoot->getRightBranch()->getText().compare("É de comer?") == Equals);
  }

  SECTION( "Inserting third branch on same node results in error" ) 
  {
    shared_ptr<StringNode> pRoot = pNonEmptyTestTree->getRoot();
    pRoot->insertBranch("É azul?");

    shared_ptr<StringNode> pLeftBranchOfRoot = pRoot->getLeftBranch();
    pLeftBranchOfRoot->insertBranch("É violeta?");
    pLeftBranchOfRoot->insertBranch("É de comer?");
    REQUIRE( pLeftBranchOfRoot->insertBranch("É manufaturado?") == Error );
  }

  SECTION( "Inserting three levels deep of root" )
  {
    shared_ptr<StringNode> pRoot = pNonEmptyTestTree->getRoot();
    REQUIRE_FALSE( pRoot->insertBranch("É azul?") == Error);
    shared_ptr<StringNode> pLeftBranchOfRoot = pRoot->getLeftBranch();

    REQUIRE_FALSE( pLeftBranchOfRoot->insertBranch("É violeta?") == Error);
    REQUIRE( pLeftBranchOfRoot->getLeftBranch()->getText().compare("É violeta?") == Equals);
    
    shared_ptr<StringNode> pSecondFromRoot = pLeftBranchOfRoot->getLeftBranch();
    REQUIRE_FALSE( pSecondFromRoot->insertBranch("É amarelo?") == Error);
    REQUIRE( pSecondFromRoot->getLeftBranch()->getText().compare("É amarelo?") == Equals);

    shared_ptr<StringNode> pThirdFromRoot = pSecondFromRoot->getLeftBranch();
    REQUIRE_FALSE( pThirdFromRoot->insertBranch("É dourado?") == Error);
    REQUIRE( pThirdFromRoot->getLeftBranch()->getText().compare("É dourado?") == Equals);
    
  } 
} //TestCase Binary Tree Create and Read

TEST_CASE( "Binary Tree Update", "[binary_tree]" ) {
  BTree* pNonEmptyTestTree = new BTree("É moderno?");

  SECTION( "Changing root node text value" )
  {
    shared_ptr<StringNode> pRoot = pNonEmptyTestTree->getRoot();
    REQUIRE( pRoot->setText("É clássico?") == Sucess );
    REQUIRE( pRoot->getText().compare("É clássico?") == Equals );
  }

  SECTION( "Changing branch node text value" )
  {
    shared_ptr<StringNode> pRoot = pNonEmptyTestTree->getRoot();
    pRoot->insertBranch("Errou!");

    shared_ptr<StringNode> pBranch = pRoot->getLeftBranch();
    REQUIRE( pBranch->setText("Acertou!") == Sucess );
    REQUIRE_FALSE( pBranch->getText().compare("Errou!") == Equals );
  }
}//TestCase Binary Tree Update

TEST_CASE( "Binary Tree Delete", "[binary_tree]" ) {
  BTree* pNonEmptyTestTree = new BTree("É moderno?");
  shared_ptr<StringNode> pRoot = pNonEmptyTestTree->getRoot();
  pRoot->insertBranch("É novo?");
  
  
  SECTION( "root can be deleted" )
  {
    REQUIRE_FALSE( pRoot->getText().empty() );
    REQUIRE_FALSE( pRoot->getLeftBranch() == nullptr );
    pRoot.reset();
    REQUIRE( pRoot == nullptr );
  }

  SECTION( "a branch can be deleted and those above it are not affected" )
  {
    shared_ptr<StringNode> pBranch = pRoot->getLeftBranch();
    REQUIRE_FALSE( pBranch->getText().empty() );

    pBranch.reset();

    REQUIRE_FALSE( pRoot == nullptr );
    REQUIRE(pBranch == nullptr);
  }
  
  SECTION( "a branch can be deleted and those below it are deleted too")
  {
    shared_ptr<StringNode> pBranch = pRoot->getLeftBranch();
    pBranch->insertBranch("Abaixo?");
    StringNode* pBelowBranch = pBranch->getLeftBranch().get();

    REQUIRE_FALSE( pBranch == nullptr );
    REQUIRE_FALSE( pBelowBranch == nullptr );

    pBranch->cutBranch();
    pBranch.reset();
    REQUIRE( pBranch == nullptr );
    REQUIRE_FALSE( pBelowBranch->getText().compare("Abaixo?") == Equals );
    REQUIRE( pBelowBranch == nullptr );
  }
}


#endif //CATCH_H_INCLUDED
