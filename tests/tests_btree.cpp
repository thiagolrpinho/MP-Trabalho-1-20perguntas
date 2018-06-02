#include "btree.hpp"

typedef shared_ptr<StringNode> PStringNode;
typedef shared_ptr<BTree> PBTree;

//! These tests will be focused on binary trees
//! They'll be considered fully functional if they pass in
//! four test cases: Create, Read, Update and Destroy

TEST_CASE( "Binary Tree Create and Read", "[binary_tree]" ) 
{
  /*!
    Here will be tested the capacity of create nodes and branches
    of the binary tree without affecting it's integrity
    Methods tested:
    stringnode->insertLeftNode()
    stringnode->insertRightNode()
    stringnode->getText()
  */
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
    REQUIRE_FALSE( p_non_empty_test_tree->getRoot()->insertLeftNode("É azul?") == Error);
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
    //p_root -> first_left
    REQUIRE( p_root->insertLeftNode("É manufaturado?") == Error );
  } //SECTION( "Inserting left branch on a non empty left branch results in error" ) 

    SECTION( "Inserting right branch on a non empty right branch results in error" ) 
  {
    PStringNode p_root = p_non_empty_test_tree->getRoot();
    p_root->insertRightNode("É vermelho?");
    //p_root -> first_right
    REQUIRE( p_root->insertRightNode("É orgânico?") == Error );
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
  //Here will be tested the capacity of update the binary tree
  //without affecting it's integrity
  // Methods tested:
  // stringnode->setText()
  PBTree p_non_empty_test_tree( new BTree("É moderno?") );

  SECTION( "Changing root node text value" )
  {
    PStringNode p_root = p_non_empty_test_tree->getRoot();
    //An text update should result in a Success
    REQUIRE( p_root->setText("É clássico?") == Success );
    //The inserted text should equal the text read from the tree
    REQUIRE( p_root->getText().compare("É clássico?") == Equals );
  } //SECTION( "Changing root node text value" )

  SECTION( "Changing branch node text value" )
  {
    PStringNode p_root = p_non_empty_test_tree->getRoot();
    //Fist we insert a new node with a dummy value
    p_root->insertLeftNode("Errou!");
    PStringNode p_node = p_root->getLeftNode();
    //Then we change it and verify if the change was made correctly
    REQUIRE( p_node->setText("Acertou!") == Success );
    REQUIRE_FALSE( p_node->getText().compare("Errou!") == Equals );
  } //SECTION( "Changing branch node text value" )
}//TestCase Binary Tree Update

TEST_CASE( "Binary Tree Delete", "[binary_tree]" ) {
   /*!
    Here will be tested the capacity of create nodes and branches
    of the binary tree without affecting it's integrity
    Methods tested:
    stringnode->clearLeft()
    stringnode->clearRight()
    stringnode->getText()
  */
  PBTree p_non_empty_test_tree( new BTree("É moderno?") );
  PStringNode p_root = p_non_empty_test_tree->getRoot();
  p_root->insertLeftNode("É novo?");
  p_root->insertRightNode("É velho?");
  
  SECTION( "a left branch can be deleted and those above it are not affected" )
  {
    //The left node is not empty before the deletion.
    REQUIRE_FALSE( p_root->getLeftNode() == nullptr );
    p_root->clearLeft();

    REQUIRE_FALSE( p_root == nullptr );
    REQUIRE( p_root->getLeftNode() == nullptr );
  } //SECTION( "a  left branch can be deleted and those above it are not affected" )

  SECTION( "a right branch can be deleted and those above it are not affected" )
  {
    //The right node is not empty before the deletion.
    REQUIRE_FALSE( p_root->getRightNode() == nullptr);
    p_root->clearRight();

    REQUIRE_FALSE( p_root == nullptr );
    REQUIRE(  p_root->getRightNode() == nullptr );
  } //SECTION( "a right branch can be deleted and those above it are not affected" )

  
  SECTION( "a branch can be deleted and those below it are deleted too")
  {
    PStringNode p_node = p_root->getLeftNode();
    p_node->insertLeftNode( "Abaixo?" );
    p_node->getLeftNode()->insertLeftNode( "Abaixo do abaixo?" );
    //p_root -> p_node -> second_left -> third_left

    REQUIRE_FALSE( p_node == nullptr );
    REQUIRE_FALSE( p_node->getLeftNode() == nullptr );
    REQUIRE_FALSE( p_node->getLeftNode()->getLeftNode() == nullptr );
    REQUIRE( p_node->getLeftNode()->getLeftNode()->getLeftNode() == nullptr );
    
    //Cut node should cut off recursively p_node and it's branches
    REQUIRE( p_node->cutNode() == Success );
    //After cutNode, there shouldn't be a no branches.
    REQUIRE( p_node->getLeftNode() == nullptr );
    REQUIRE( p_node->getText().empty() );
    //Shared_ptr guaranties that when there's no reference to the pointer, they're deallocated
  } //SECTION( "a branch can be deleted and those below it are deleted too")

  SECTION("A node can have it's left branch specifically deleted")
  {
    PStringNode p_node = p_root->getLeftNode();
    p_node->insertLeftNode( "Abaixo?" );
    p_node->getLeftNode()->insertLeftNode( "Abaixo do abaixo?" );

    REQUIRE( p_node->clearLeft() == Success );
    REQUIRE( p_node->getLeftNode() == nullptr );
  } //SECTION("A node can have it's left branch deleted")

  SECTION("A node can have it's right branch specifically deleted")
  {
    PStringNode p_node = p_root->getLeftNode();
    p_node->insertRightNode( "Abaixo?" );
    p_node->getRightNode()->insertRightNode( "Abaixo do abaixo?" );

    REQUIRE( p_node->clearRight() == Success );
    REQUIRE( p_node->getRightNode() == nullptr );
  } //SECTION("A node can have it's right branch deleted")
}//TEST CASE DELETE BINARY TREE

