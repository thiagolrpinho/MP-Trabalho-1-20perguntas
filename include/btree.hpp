#ifndef BTREE_HPP
#define BTREE_HPP

#include<string>
using std::string;

class BTree {
 private:
  BTree* leftBranch;
  BTree* rightBranch;
  string text;

 public:
  BTree();
  BTree* getleftBranch(void){ return this->leftBranch; }
  BTree* getRightBranch(void){ return this->rightBranch; }
  string getText(void) { return this->text;}

};

#endif