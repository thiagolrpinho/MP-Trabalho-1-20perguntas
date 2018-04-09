#include "stringnode.hpp"


StringNode::StringNode(void)
{
  pRightBranch = pLeftBranch = nullptr;
  text.clear();
}

StringNode::StringNode(string initialText)
{
    pRightBranch = pLeftBranch = nullptr;
    text.assign(initialText);
}
/*
StringNode::~StringNode(){
    delete( pRightBranch );
    pRightBranch = nullptr;
    delete( pLeftBranch );
    pLeftBranch = nullptr;
    text.clear();
}
*/
/*
    Each node can only have two branches and inserting the third
    should result on a flag error and the third node being discarted
*/

int StringNode::insertBranch(string initialNewBranchText){
    if ( this->getLeftBranch() == nullptr) {
        this->pLeftBranch.reset(new StringNode(initialNewBranchText));
    } else if (this->getRightBranch() == nullptr) {
        this->pRightBranch.reset(new StringNode(initialNewBranchText));
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