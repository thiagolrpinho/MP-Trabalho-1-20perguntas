#include<string>
using std::string;

enum NodeOperationStatus {Error, Sucess};
enum StringEquivalence {Equals};

class StringNode{
 //Each string node is initialized with an empty text variable(nullptr)
 //and two empty branches, unless specified by the client wich can define
 //the initial text value for the node

 private:
  StringNode* leftBranch;
  StringNode* rightBranch;
  string text;

 public:
  //Methods
  StringNode();
  StringNode(string initialText);

  ~StringNode();

  StringNode* getLeftBranch(void) { return this->leftBranch; }
  StringNode* getRightBranch(void){ return this->rightBranch; }
  string getText(void) { return this->text; }

  int setText(string newText);

  int insertBranch(string initialNewBranchText);
};