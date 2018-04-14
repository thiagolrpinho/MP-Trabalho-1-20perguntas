#include "stringnode.hpp"


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

int StringNode::insertNode( string initial_new_node_text ){
    if ( this->getLeftNode() == nullptr ) {
        this->p_left_node_.reset( new StringNode(initial_new_node_text) );
    } else if (this->getRightNode() == nullptr) {
        this->p_right_node_.reset( new StringNode(initial_new_node_text) );
    } else {
        return Error;
    }

    return Sucess;
};


int StringNode::insertLeftNode(){
    if ( this->getLeftNode() == nullptr ) {
        this->p_left_node_.reset( new StringNode() );
    } else {
        return Error;
    }
    return Sucess;
};

int StringNode::insertLeftNode( string initial_new_node_text ){
    if ( this->getLeftNode() == nullptr ) {
        this->p_left_node_.reset( new StringNode(initial_new_node_text) );
    } else {
        return Error;
    }
    return Sucess;
};

int StringNode::insertRightNode(string initial_new_node_text){
    if ( this->getRightNode() == nullptr ) {
        this->p_right_node_.reset( new StringNode(initial_new_node_text) );
    } else {
        return Error;
    }
    return Sucess;
};

int StringNode::insertRightNode( ){
    if ( this->getRightNode() == nullptr ) {
        this->p_right_node_.reset( new StringNode() );
    } else {
        return Error;
    }
    return Sucess;
};




int StringNode::setText(string newText)
{
  try {
    this->text.assign(newText);
  } catch (int e) {
      return Error;
  }
  return Sucess;
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
        return Sucess;
    } catch (int e) {
        return Error;
    }
}
