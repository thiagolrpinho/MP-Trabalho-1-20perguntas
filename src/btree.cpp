#include "btree.hpp"



BTree::BTree(void){
  rootNode = new StringNode();
  
}

BTree::BTree(string initialText){
    rootNode = new StringNode(initialText);
};

int BTree::insertBranch(string initialNewBranchText){
    if ( this->getLeftBranch() == nullptr) {
        rootNode->leftBranch = new StringNode(initialNewBranchText);
    } else if (this->getRightBranch() == nullptr) {
        rootNode->rightBranch = new StringNode(initialNewBranchText);
    } else {
        return Error;
    }

    return Sucess;
};
