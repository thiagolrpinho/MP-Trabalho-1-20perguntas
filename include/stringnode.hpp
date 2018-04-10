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
  shared_ptr<StringNode> pLeftNode;
  shared_ptr<StringNode> pRightNode;
  string text;

 public:
  //Methods
  StringNode();
  StringNode(string initialText);

  ~StringNode();

  shared_ptr<StringNode> getLeftNode(void) { return this->pLeftNode; }
  shared_ptr<StringNode> getRightNode(void){ return this->pRightNode; }
  string getText(void) { return this->text; }

  int setText(string newText);
  int insertNode(string initialNewNodeText);
  int cutNode();
};