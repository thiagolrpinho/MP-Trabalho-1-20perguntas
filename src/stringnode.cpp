#include "stringnode.hpp"


StringNode::StringNode(void)
{
  pRightNode = pLeftNode = nullptr;
  text.clear();
}

StringNode::StringNode(string initialText)
{
    pRightNode = pLeftNode = nullptr;
    text.assign(initialText);
}

StringNode::~StringNode(){
    pRightNode.reset();
    pLeftNode.reset();
    text.clear();
}


/*
    Each node can only have two branches and inserting the third
    should result on a flag error and the third node being discarted
*/

int StringNode::insertNode(string initialNewNodeText){
    if ( this->getLeftNode() == nullptr) {
        this->pLeftNode.reset(new StringNode(initialNewNodeText));
    } else if (this->getRightNode() == nullptr) {
        this->pRightNode.reset(new StringNode(initialNewNodeText));
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
            this->pLeftNode->cutNode();
            this->pLeftNode.reset();
        }
        
        if ( this->getRightNode() != nullptr )
        {
            this->pRightNode->cutNode();
            this->pRightNode.reset();
        }

        this->text.clear();
        return Sucess;
    } catch (int e) {
        return Error;
    }
}
