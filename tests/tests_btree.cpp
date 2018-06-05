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

  SECTION( "Inserting empty left branch on root")
  {
    //The insertion should not raise Errors.
    REQUIRE_FALSE( p_non_empty_test_tree->getRoot()->insertLeftNode() == Error);
    //The inserted value should be equal be a blank text
    REQUIRE(p_non_empty_test_tree->getRoot()->getLeftNode()->getText().compare("") == Equals);
  } //SECTION( "Inserting empty left branch on root")

  SECTION( "Inserting non empty left branch on root")
  {
    //The insertion should not raise Errors.
    REQUIRE_FALSE( p_non_empty_test_tree->getRoot()->insertLeftNode("É azul?") == Error);
    //The inserted value should be equal to the value read after the insertion
    REQUIRE(p_non_empty_test_tree->getRoot()->getLeftNode()->getText().compare("É azul?") == Equals);
  } //SECTION( "Inserting non empty left branch on root")

  SECTION( "Inserting empty right branch on root")
  {
    PStringNode p_root = p_non_empty_test_tree->getRoot();
     //The insertion should not raise Errors.
    REQUIRE_FALSE( p_root->insertRightNode() == Error);
    //The inserted value should be equal be a blank text
    REQUIRE(p_root->getRightNode()->getText().compare("") == Equals);
  } //SECTION( "Inserting empty right branch on root")

  SECTION( "Inserting non empty right branch on root")
  {
    PStringNode p_root = p_non_empty_test_tree->getRoot();
     //The insertion should not raise Errors.
    REQUIRE_FALSE( p_root->insertRightNode("É vermelho?") == Error);
    //The inserted value should be equal to the value read after the insertion
    REQUIRE(p_root->getRightNode()->getText().compare("É vermelho?") == Equals);
  } //SECTION( "Inserting non empty right branch on root")

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

  SECTION( "Inserting left branch on an empty non null left branch results in error" ) 
  {
    PStringNode p_root = p_non_empty_test_tree->getRoot();
    p_root->insertLeftNode("É azul?");
    //p_root -> first_left
    REQUIRE( p_root->insertLeftNode() == Error );
  } //SECTION( "Inserting left branch on an empty non null left branch results in error" ) 

  SECTION( "Inserting left branch on a non empty non null left branch results in error" ) 
  {
    PStringNode p_root = p_non_empty_test_tree->getRoot();
    p_root->insertLeftNode("É azul?");
    //p_root -> first_left
    REQUIRE( p_root->insertLeftNode("É manufaturado?") == Error );
  } //SECTION( "Inserting left branch on a non empty non null left branch results in error" ) 

  SECTION( "Inserting right branch on an empty non null right branch results in error" ) 
  {
    PStringNode p_root = p_non_empty_test_tree->getRoot();
    p_root->insertRightNode("É vermelho?");
    //p_root -> first_right
    REQUIRE( p_root->insertRightNode() == Error );
  } //SECTION( "Inserting right branch on an empty non null right branch results in error" ) 

  SECTION( "Inserting right branch on a non empty non null right branch results in error" ) 
  {
    PStringNode p_root = p_non_empty_test_tree->getRoot();
    p_root->insertRightNode("É vermelho?");
    //p_root -> first_right
    REQUIRE( p_root->insertRightNode("É orgânico?") == Error );
  } //SECTION( "Inserting right branch on a non empty non null right branch results in error" )

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

    p_node->insertRightNode( "Abaixo a direita?" );
    p_node->getRightNode()->insertRightNode( "Abaixo do abaixo da direita?" );

    REQUIRE_FALSE( p_node == nullptr );
    REQUIRE_FALSE( p_node->getLeftNode() == nullptr );
    REQUIRE_FALSE( p_node->getLeftNode()->getLeftNode() == nullptr );
    REQUIRE_FALSE( p_node->getRightNode() == nullptr );
    REQUIRE_FALSE( p_node->getRightNode()->getRightNode() == nullptr );
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

/* !
  Special test case to verifies if cutNode() is safe.
  Using some paths coverture logic.
*/
TEST_CASE( "Binary Tree CutNode", "[binary_tree]" ) 
{
  /* 
  If we analyse the code of StringNode::CutNode(void)
  and mark each boolean decision  and some keys statements
  with a tag letter  we could trace a decision path course
  to make easy to test possible bugs.

  int StringNode::cutNode(void )
  //The recursive call of cutNode()
  //will be named the A statement
  {
    try //TRY AND CATCH WILL BE IGNORED
    {
      // THIS IS THE B DECISION
        if ( this->getLeftNode() != nullptr )
        {
          //THIS IS THE A RECURSIVE CALL OF THE A STATEMENT
          this->p_left_node_->cutNode();
          this->p_left_node_.reset();
        }
        //If the B decision was not true
        //I'll say it took the 
        //E statement(even though it does nothing) to better ilustrate

        //THIS IS THE C STATEMENT
        if ( this->getRightNode() != nullptr )
        {
          //THIS IS THE A RECURSIVE CALL OF THE A STATEMENT
          this->p_right_node_->cutNode();
          this->p_right_node_.reset();
        }
        //If the C decision was not true
        //I'll say it took the 
        //F statement(even though it does nothing) to better ilustrate

        //THESE ARE THE D STATEMENTS
        this->text.clear();
        return Success;
    } catch (int e) {
        return Error;
    }
  }
  Following this, we can represent the behavior of 
  this method by:
  A = B 2(A|E) C 2(A|F) D
  Where N() denotes a decision with cardinality choose by the N number.

  So we can study:
  The special case 0:
    BECFD -> The node is a leaf. 
  The cases with 1 cycles deep:
    B BECFD C BECEF D -> The node has one leaf in each branch.
    B BECFD CFD       -> The node has one leaf on left branch.
    BEC BECFD D       -> The node has one leaf on right branch.
  The cases with 3 cycles deep gets a little more complex
  B 
    B 
      B 
        BECFD C BECEF 
      D 
    C 
      B 
        BECFD C BECEF 
      D 
    D 
  C 
    B 
      B 
        BECFD C BECEF 
      D 
    C 
      B 
        BECFD C BECEF 
      D 
    D 
  D
  -> This case can be ilustrate as a four layers full binary tree.

  By testing these four special cases, it's possible to induct the
  other scenarios. 
*/

  SECTION("")
  {
  } 

} //TEST_CASE( "Binary Tree CutNode", "[binary_tree]" ) 
