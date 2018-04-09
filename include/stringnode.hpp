#include <string>
using std::string;

#include <memory>
using std::shared_ptr;

//Node Operations can be sucessful or not, every
//method that would simply return void will instead
//return an Error ou Sucess.
enum NodeOperationStatus {Error, Sucess};
//The Compare method from the library String
//returns 0 when Equal.
enum StringEquivalence {Equals};

class StringNode{
 //Each string node is initialized with an empty text variable(nullptr)
 //and two empty branches, unless specified by the client wich can define
 //the initial text value for the node

 private:
  shared_ptr<StringNode> pLeftBranch;
  shared_ptr<StringNode> pRightBranch;
  string text;

 public:
  //Methods
  StringNode();
  StringNode(string initialText);

  //~StringNode();

  shared_ptr<StringNode> getLeftBranch(void) { return this->pLeftBranch; }
  shared_ptr<StringNode> getRightBranch(void){ return this->pRightBranch; }
  string getText(void) { return this->text; }

  int setText(string newText);

  int insertBranch(string initialNewBranchText);
};