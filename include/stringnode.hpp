#ifndef CATCH_H
#define CATCH_H
#include "catch.hpp"
#endif

#include <string>
using std::string;

#include <memory>
using std::shared_ptr;
using std::make_shared;

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
  shared_ptr<StringNode> p_left_node_;
  shared_ptr<StringNode> p_right_node_;
  string text;

 public:
  //Methods
  StringNode();
  StringNode(string initial_text);

  ~StringNode();

  shared_ptr<StringNode> getLeftNode(void) { return this->p_left_node_; }
  shared_ptr<StringNode> getRightNode(void){ return this->p_right_node_; }
  string getText(void) { return this->text; }

  int setText(string newText);
  int insertNode(string initial_new_node_text);
  int insertLeftNode();
  int insertLeftNode(string initial_new_node_text);
  int insertRightNode();
  int insertRightNode(string initial_new_node_text);
  int cutNode();
  int clearLeft( void );
  int clearRight( void );
};