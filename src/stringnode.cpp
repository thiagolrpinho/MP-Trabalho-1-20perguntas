#include "stringnode.hpp"

/*! \file stringnode.cpp
    \brief Module which contains the methods of the object stringnode.
*/

StringNode::StringNode(void)
{
  p_right_node_ = p_left_node_ = nullptr;
  text.clear();
}

StringNode::StringNode(string  initial_text )
{
    p_right_node_ = p_left_node_ = nullptr;
    text.assign( initial_text );
}

StringNode::~StringNode(){
    p_right_node_.reset();
    p_left_node_.reset();
    text.clear();
}


/*
    Each node can only have two branches and inserting the third
    should result on a flag error and the third node being discarted
*/

//! A method that create a new node with an initial string chosen
    /*!
        \Description verifies if left node is empty, if it is creates
        a new node and sets it's value to the initial_new_node_text
        value. Then it'll return a Success which is an enum with value
        1.
        If left node is not empty then it tries the rightNode.
        If the right one is empty, creates a new node there and sets
        it's value to the value of the same argument. Then it'll return
         a Success which is an enum with value 1.
        If neither are empty, nothing is done and the method return an 
        Error which is an enum with value 0.
        \param An already existent string which will be the value of
        the new node.
        \return An int 0 for Error or 1 for Success
    */
int StringNode::insertNode( string initial_new_node_text ){
    if ( this->getLeftNode() == nullptr ) {
        this->p_left_node_.reset( new StringNode(initial_new_node_text) );
    } else if (this->getRightNode() == nullptr) {
        this->p_right_node_.reset( new StringNode(initial_new_node_text) );
    } else {
        return Error;
    }

    return Success;
};


//! A method that creates the a blank left node of an empty branch.
    /*!
        \Description Verifies if the left node already exists 
        returns an Error(Integer 0). If not creates a new node
        and sets it's value to empty and returns a Success(Inte-
        ger 1).
        \param None.
        \return An int 0 for Error or 1 for Success
    */
int StringNode::insertLeftNode(){
    if ( this->getLeftNode() == nullptr ) {
        this->p_left_node_.reset( new StringNode() );
    } else {
        return Error;
    }
    return Success;
};

//! A method that creates the a setted left node of an empty branch
    /*!
        \Description Verifies if the left node already exists 
        returns an Error(Integer 0). If not creates a new node
        and sets it's value to the value of the param
         then returns a Success(Integer 1).
        \param An already existent string which will be the
        value of the new node.
        \return An int 0 for Error or 1 for Success
    */
int StringNode::insertLeftNode( string initial_new_node_text ){
    if ( this->getLeftNode() == nullptr ) {
        this->p_left_node_.reset( new StringNode(initial_new_node_text) );
    } else {
        return Error;
    }
    return Success;
};

//! A method that creates the a blank right node of an empty branch.
    /*!
        \Description Verifies if the right node already exists 
        returns an Error(Integer 0). If not creates a new node
        and sets it's value to empty and returns a Success(Inte-
        ger 1).
        \param None.
        \return An int 0 for Error or 1 for Success
    */
int StringNode::insertRightNode( ){
    if ( this->getRightNode() == nullptr ) {
        this->p_right_node_.reset( new StringNode() );
    } else {
        return Error;
    }
    return Success;
};

//! A method that creates the a setted right node of an empty branch
    /*!
        \Description Verifies if the right node already exists 
        returns an Error(Integer 0). If not creates a new node
        and sets it's value to the value of the param
         then returns a Success(Integer 1).
        \param An already existent string which will be the
        value of the new node.
        \return An int 0 for Error or 1 for Success
    */
int StringNode::insertRightNode(string initial_new_node_text){
    if ( this->getRightNode() == nullptr ) {
        this->p_right_node_.reset( new StringNode(initial_new_node_text) );
    } else {
        return Error;
    }
    return Success;
};


//! A method that sets the value of a node.
    /*!
        \Description Try to assign a new value to
        node. If it fails returns an Error(Integer 0)
        else it returns a Success(Integer 1).
        \param An already existing string. 
        \return An int 0 for Error or 1 for Success
    */
int StringNode::setText(string newText)
{
  try {
    this->text.assign(newText);
  } catch (int e) {
      return Error;
  }
  return Success;
}


//Reset each node after cleaning the nodes below it
int StringNode::cutNode(void )
{
    try
    {
        //If there's a branch, clean this branch
        if ( this->getLeftNode() != nullptr )
        {
            this->p_left_node_->cutNode();
            this->p_left_node_.reset();
        }
        
        if ( this->getRightNode() != nullptr )
        {
            this->p_right_node_->cutNode();
            this->p_right_node_.reset();
        }

        this->text.clear();
        return Success;
    } catch (int e) {
        return Error;
    }
}

int StringNode::clearLeft( void )
{
    try {
        this->p_left_node_.reset();
    } catch ( int e) {
        return Error;
    }
    return Success;
}

int StringNode::clearRight( void )
{
    try {
        this->p_right_node_.reset();
    } catch ( int e) {
        return Error;
    }
    
    return Success;
}