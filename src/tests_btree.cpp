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
    REQUIRE( pRoot->getLeftNode() == nullptr );
    REQUIRE( pRoot->getRightNode() == nullptr);
    REQUIRE( pRoot->getText().empty());
  }

  SECTION( "Creating a non empty tree root"){
    REQUIRE( pNonEmptyTestTree->getRoot()->getText().compare("É verde?") == 0);
  }

  SECTION( "Inserting left branch on root")
  {
    
    REQUIRE_FALSE( pNonEmptyTestTree->getRoot()->insertNode("É azul?") == Error);
    REQUIRE(pNonEmptyTestTree->getRoot()->getLeftNode()->getText().compare("É azul?") == 0);
  }

  SECTION( "Inserting right branch on root")
  {
    shared_ptr<StringNode> pRoot = pNonEmptyTestTree->getRoot();
    REQUIRE_FALSE( pRoot->insertNode("É azul?") == Error);
    REQUIRE_FALSE( pRoot->insertNode("É vermelho?") == Error);
    REQUIRE(pRoot->getLeftNode()->getText().compare("É azul?") == Equals);
    REQUIRE(pRoot->getRightNode()->getText().compare("É vermelho?") == Equals);
  }

  SECTION( "Inserting left branch on left branch of root")
  {
    shared_ptr<StringNode> pRoot = pNonEmptyTestTree->getRoot();
    REQUIRE_FALSE( pRoot->insertNode("É azul?") == Error);
    shared_ptr<StringNode> pLeftNodeOfRoot = pRoot->getLeftNode();

    REQUIRE_FALSE( pLeftNodeOfRoot->insertNode("É violeta?") == Error);
    REQUIRE( pLeftNodeOfRoot->getLeftNode()->getText().compare("É violeta?") == Equals);
  }

   SECTION( "Inserting right and left branch on left branch of root" )
  {
    shared_ptr<StringNode> pRoot = pNonEmptyTestTree->getRoot();
    REQUIRE_FALSE( pRoot->insertNode("É azul?") == Error);
    shared_ptr<StringNode> pLeftNodeOfRoot = pRoot->getLeftNode();

    REQUIRE_FALSE( pLeftNodeOfRoot->insertNode("É violeta?") == Error);
    REQUIRE( pLeftNodeOfRoot->getLeftNode()->getText().compare("É violeta?") == Equals);
    REQUIRE_FALSE( pLeftNodeOfRoot->insertNode("É de comer?") == Error);
    REQUIRE( pLeftNodeOfRoot->getRightNode()->getText().compare("É de comer?") == Equals);
  }

  SECTION( "Inserting third branch on same node results in error" ) 
  {
    shared_ptr<StringNode> pRoot = pNonEmptyTestTree->getRoot();
    pRoot->insertNode("É azul?");

    shared_ptr<StringNode> pLeftNodeOfRoot = pRoot->getLeftNode();
    pLeftNodeOfRoot->insertNode("É violeta?");
    pLeftNodeOfRoot->insertNode("É de comer?");
    REQUIRE( pLeftNodeOfRoot->insertNode("É manufaturado?") == Error );
  }

  SECTION( "Inserting three levels deep of root" )
  {
    shared_ptr<StringNode> pRoot = pNonEmptyTestTree->getRoot();
    REQUIRE_FALSE( pRoot->insertNode("É azul?") == Error);
    shared_ptr<StringNode> pLeftNodeOfRoot = pRoot->getLeftNode();

    REQUIRE_FALSE( pLeftNodeOfRoot->insertNode("É violeta?") == Error);
    REQUIRE( pLeftNodeOfRoot->getLeftNode()->getText().compare("É violeta?") == Equals);
    
    shared_ptr<StringNode> pSecondFromRoot = pLeftNodeOfRoot->getLeftNode();
    REQUIRE_FALSE( pSecondFromRoot->insertNode("É amarelo?") == Error);
    REQUIRE( pSecondFromRoot->getLeftNode()->getText().compare("É amarelo?") == Equals);

    shared_ptr<StringNode> pThirdFromRoot = pSecondFromRoot->getLeftNode();
    REQUIRE_FALSE( pThirdFromRoot->insertNode("É dourado?") == Error);
    REQUIRE( pThirdFromRoot->getLeftNode()->getText().compare("É dourado?") == Equals);
    
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
    pRoot->insertNode("Errou!");

    shared_ptr<StringNode> pNode = pRoot->getLeftNode();
    REQUIRE( pNode->setText("Acertou!") == Sucess );
    REQUIRE_FALSE( pNode->getText().compare("Errou!") == Equals );
  }
}//TestCase Binary Tree Update

TEST_CASE( "Binary Tree Delete", "[binary_tree]" ) {
  BTree* pNonEmptyTestTree = new BTree("É moderno?");
  shared_ptr<StringNode> pRoot = pNonEmptyTestTree->getRoot();
  pRoot->insertNode("É novo?");
  
  
  SECTION( "root can be deleted" )
  {
    REQUIRE_FALSE( pRoot->getText().empty() );
    REQUIRE_FALSE( pRoot->getLeftNode() == nullptr );
    pRoot.reset();
    REQUIRE( pRoot == nullptr );
  }

  SECTION( "a branch can be deleted and those above it are not affected" )
  {
    shared_ptr<StringNode> pNode = pRoot->getLeftNode();
    REQUIRE_FALSE( pNode->getText().empty() );

    pNode.reset();

    REQUIRE_FALSE( pRoot == nullptr );
    REQUIRE( pNode == nullptr );
  }
  
  SECTION( "a branch can be deleted and those below it are deleted too")
  {
    shared_ptr<StringNode> pNode = pRoot->getLeftNode();
    pNode->insertNode( "Abaixo?" );
    pNode->getLeftNode()->insertNode( "Abaixo do abaixo?" );

    REQUIRE_FALSE( pNode == nullptr );
    REQUIRE_FALSE( pNode->getLeftNode() == nullptr );
    REQUIRE_FALSE( pNode->getLeftNode()->getLeftNode() == nullptr );
    REQUIRE( pNode->getLeftNode()->getLeftNode()->getLeftNode() == nullptr );

    pNode->cutNode();
    
    REQUIRE( pNode->getLeftNode() == nullptr );
  }

}//TEST CASE DELETE BINARY TREE


#endif //CATCH_H_INCLUDED
