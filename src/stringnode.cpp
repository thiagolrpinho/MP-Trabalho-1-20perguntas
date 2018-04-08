#include "stringnode.hpp"

StringNode::StringNode(void)
{
  rightBranch = leftBranch = nullptr;
  text.clear();
}

StringNode::StringNode(string initialText)
{
    rightBranch = leftBranch = nullptr;
    text.assign(initialText);
}

StringNode::~StringNode(){
    delete( rightBranch );
    rightBranch = nullptr;
    delete( leftBranch );
    leftBranch = nullptr;
    text.clear();
}

/*
    Each node can only have two branches and inserting the third
    should result on a flag error and the third node being discarted
*/

int StringNode::insertBranch(string initialNewBranchText){
    if ( this->getLeftBranch() == nullptr) {
        this->leftBranch = new StringNode(initialNewBranchText);
    } else if (this->getRightBranch() == nullptr) {
        this->rightBranch = new StringNode(initialNewBranchText);
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