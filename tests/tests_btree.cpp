#include "btree.hpp"

typedef shared_ptr<StringNode> PStringNode;
typedef shared_ptr<BTree> PBTree;

//! These tests will be focused on binary trees
//! They'll be considered fully functional if they pass in
//! four test cases: Create, Read, Update and Destroy

TEST_CASE( "Binary Tree Create and Read", "[binary_tree]" ) 
{
  string initial_text = "É verde?";

  //First we create test trees
  PBTree p_empty_test_tree( new BTree() );
  PBTree p_non_empty_test_tree( new BTree(initial_text) );

  SECTION( "Creating an empty branchless tree root" ) 
  {
    PStringNode p_root = p_empty_test_tree->getRoot();

    //The test tree and it's root should exist
    REQUIRE_FALSE( p_empty_test_tree == nullptr );
    REQUIRE_FALSE( p_root == nullptr );
    //A branchless root shouldn't have branches
    REQUIRE( p_root->getLeftNode() == nullptr );
    REQUIRE( p_root->getRightNode() == nullptr);
    //an empty root mustn't have text.
    REQUIRE( p_root->getText().empty());
  } // SECTION( "Creating an empty branchless tree root" )

  SECTION( "Creating a non empty tree root")
  {
    //a non empty root must have text.
    REQUIRE( p_non_empty_test_tree->getRoot()->getText().compare("É verde?") == Equals);
  } //SECTION( "Creating a non empty tree root")

  SECTION( "Inserting left branch on root")
  {
    //The insertion should not raise Errors.
    REQUIRE_FALSE( p_non_empty_test_tree->getRoot()->inserLeftNode("É azul?") == Error);
    //The inserted value should be equal to the value read after the insertion
    REQUIRE(p_non_empty_test_tree->getRoot()->getLeftNode()->getText().compare("É azul?") == Equals);
  } //SECTION( "Inserting left branch on root")

  SECTION( "Inserting right branch on root")
  {
    PStringNode p_root = p_non_empty_test_tree->getRoot();
     //The insertion should not raise Errors.
    REQUIRE_FALSE( p_root->insertRightNode("É vermelho?") == Error);
    //The inserted value should be equal to the value read after the insertion
    REQUIRE(p_root->getRightNode()->getText().compare("É vermelho?") == Equals);
  } //SECTION( "Inserting right branch on root")

  SECTION( "Inserting left branch on left branch of root")
  {
    PStringNode p_root = p_non_empty_test_tree->getRoot();
    REQUIRE_FALSE( p_root->insertLeftNode("É azul?") == Error);
    PStringNode p_left_node_of_root = p_root->getLeftNode();


    REQUIRE_FALSE( p_left_node_of_root->insertLeftNode("É violeta?") == Error);
    REQUIRE( p_left_node_of_root->getLeftNode()->getText().compare("É violeta?") == Equals);
  } //SECTION( "Inserting left branch on left branch of root")

   SECTION( "Inserting right and left branch on left branch of root" )
  {
    PStringNode p_root = p_non_empty_test_tree->getRoot();
    REQUIRE_FALSE( p_root->insertLeftNode("É azul?") == Error);
    PStringNode p_left_node_of_root = p_root->getLeftNode();

    REQUIRE_FALSE( p_left_node_of_root->insertLeftNode("É violeta?") == Error);
    REQUIRE( p_left_node_of_root->getLeftNode()->getText().compare("É violeta?") == Equals);
    REQUIRE_FALSE( p_left_node_of_root->insertRightNode("É de comer?") == Error);
    REQUIRE( p_left_node_of_root->getRightNode()->getText().compare("É de comer?") == Equals);
  } //SECTION( "Inserting right and left branch on left branch of root" )

  SECTION( "Inserting left branch on a non empty left branch results in error" ) 
  {
    PStringNode p_root = p_non_empty_test_tree->getRoot();
    p_root->insertLeftNode("É azul?");
    PStringNode p_left_node_of_root = p_root->getLeftNode();

    REQUIRE( p_left_node_of_root->insertLeftNode("É manufaturado?") == Error );
  } //SECTION( "Inserting left branch on a non empty left branch results in error" ) 

    SECTION( "Inserting right branch on a non empty right branch results in error" ) 
  {
    PStringNode p_root = p_non_empty_test_tree->getRoot();
    p_root->insertRightNode("É vermelho?");
    PStringNode p_right_node_of_root = p_root->getLeftNode();

    REQUIRE( p_right_node_of_root->insertRightNode("É orgânico?") == Error );
  } //SECTION( "Inserting right branch on a non empty right branch results in error" ) 

  SECTION( "Inserting three levels deep of root" )
  {
    PStringNode p_root = p_non_empty_test_tree->getRoot();
    REQUIRE_FALSE( p_root->insertLeftNode("É azul?") == Error);
    // actual state of tree = root -> first_left

    PStringNode p_left_node_of_root = p_root->getLeftNode();
    REQUIRE_FALSE( p_left_node_of_root->insertLeftNode("É violeta?") == Error);
    REQUIRE( p_left_node_of_root->getLeftNode()->getText().compare("É violeta?") == Equals);
    // actual state of tree = root -> first_left -> second_left
    
    PStringNode pSecondFromRoot = p_left_node_of_root->getLeftNode();
    REQUIRE_FALSE( pSecondFromRoot->insertLeftNode("É amarelo?") == Error);
    REQUIRE( pSecondFromRoot->getLeftNode()->getText().compare("É amarelo?") == Equals);
    // actual state of tree = root -> first_left -> second_left -> third_left

    PStringNode pThirdFromRoot = pSecondFromRoot->getLeftNode();
    REQUIRE_FALSE( pThirdFromRoot->insertLeftNode("É dourado?") == Error);
    REQUIRE( pThirdFromRoot->getLeftNode()->getText().compare("É dourado?") == Equals);
    // actual state of tree = root -> first_left -> second_left -> third_left -> forth_left
  } //SECTION( "Inserting three levels deep of root" )
} //TestCase Binary Tree Create and Read

TEST_CASE( "Binary Tree Update", "[binary_tree]" ) {
  PBTree p_non_empty_test_tree( new BTree("É moderno?") );

  SECTION( "Changing root node text value" )
  {
    PStringNode p_root = p_non_empty_test_tree->getRoot();
    REQUIRE( p_root->setText("É clássico?") == Success );
    REQUIRE( p_root->getText().compare("É clássico?") == Equals );
  }

  SECTION( "Changing branch node text value" )
  {
    PStringNode p_root = p_non_empty_test_tree->getRoot();
    p_root->insertNode("Errou!");

    PStringNode p_node = p_root->getLeftNode();
    REQUIRE( p_node->setText("Acertou!") == Success );
    REQUIRE_FALSE( p_node->getText().compare("Errou!") == Equals );
  }
}//TestCase Binary Tree Update

TEST_CASE( "Binary Tree Delete", "[binary_tree]" ) {
  PBTree p_non_empty_test_tree( new BTree("É moderno?") );
  PStringNode p_root = p_non_empty_test_tree->getRoot();
  p_root->insertNode("É novo?");
  
  
  SECTION( "root can be deleted" )
  {
    REQUIRE_FALSE( p_root->getText().empty() );
    REQUIRE_FALSE( p_root->getLeftNode() == nullptr );
    p_root.reset();
    REQUIRE( p_root == nullptr );
  }

  SECTION( "a branch can be deleted and those above it are not affected" )
  {
    PStringNode p_node = p_root->getLeftNode();
    REQUIRE_FALSE( p_node->getText().empty() );

    p_node.reset();

    REQUIRE_FALSE( p_root == nullptr );
    REQUIRE( p_node == nullptr );
  }
  
  SECTION( "a branch can be deleted and those below it are deleted too")
  {
    PStringNode p_node = p_root->getLeftNode();
    p_node->insertNode( "Abaixo?" );
    p_node->getLeftNode()->insertNode( "Abaixo do abaixo?" );

    REQUIRE_FALSE( p_node == nullptr );
    REQUIRE_FALSE( p_node->getLeftNode() == nullptr );
    REQUIRE_FALSE( p_node->getLeftNode()->getLeftNode() == nullptr );
    REQUIRE( p_node->getLeftNode()->getLeftNode()->getLeftNode() == nullptr );

    p_node->cutNode();
    
    REQUIRE( p_node->getLeftNode() == nullptr );
    //Shared_ptr garanties that when there's no reference to the pointer, they're deallocated
  }

  SECTION("A node can have it's left branch deleted")
  {
    PStringNode p_node = p_root->getLeftNode();
    p_node->insertNode( "Abaixo?" );
    p_node->getLeftNode()->insertNode( "Abaixo do abaixo?" );

    REQUIRE( p_node->clearLeft() == Success);
    REQUIRE( p_node->getLeftNode() == nullptr );
  }

  SECTION("A node can have it's right branch deleted")
  {
    PStringNode p_node = p_root->getLeftNode();
    p_node->insertRightNode( "Abaixo?" );
    p_node->getRightNode()->insertRightNode( "Abaixo do abaixo?" );

    REQUIRE( p_node->clearRight() == Success);
    REQUIRE( p_node->getRightNode() == nullptr );
  }

}//TEST CASE DELETE BINARY TREE

