#include "game_engine.hpp"

typedef shared_ptr<StringNode> PStringNode;

GameEngine::GameEngine()
{
    p_tree_of_statements_.reset(new BTree());
    //Initial Actual Node is the start node
    this->setActualNode(getStart());
    this->pushLastNode(getStart());
    
}

GameEngine::GameEngine(string initial_text)
{
    p_tree_of_statements_.reset(new BTree(initial_text));
     //Initial Actual Node is the start node
    this->setActualNode(getStart());
    this->pushLastNode(getStart());
}

//POSITIONING METHODS
 PStringNode GameEngine::getStart(void)
 { 
     return p_tree_of_statements_->getRoot();
 };
 PStringNode GameEngine::getActualNode(void)
 {
      return p_actual_node_; 
 };
 
 int GameEngine::setActualNode( PStringNode p_next_node )
 { 
    try {
        p_actual_node_ = p_next_node;
    } catch (int e) {
        return Error;
    }
    return Sucess;
 };

  PStringNode GameEngine::popLastNode(void)
 {   
      PStringNode pLast = stack_of_last_nodes_.top();
      stack_of_last_nodes_.pop(); 
      return pLast;
 };

 int GameEngine::pushLastNode( PStringNode p_next_node )
 { 
    try {
        stack_of_last_nodes_.push( p_next_node );
    } catch (int e) {
        return Error;
    }
    return Sucess;
 };

//READING AND WRITING METHODS
string GameEngine::readActualNode( void )
{
    return getActualNode()->getText();
};

int GameEngine::writeInActualNode( string new_text )
{
    try {
        return getActualNode()->setText( new_text );
    } catch(int e) {
        return Error;
    }
};

int GameEngine::newYesAnswer()
{ 
    p_tree_of_statements_->getRoot()->insertLeftNode();
    return Sucess; 
};

int GameEngine::newYesAnswer(string initial_text)
{ 
    p_tree_of_statements_->getRoot()->insertLeftNode( initial_text );
    return Sucess; 
};

//DELETING METHODS
int GameEngine::removeActualNode( void )
{
    try {
        getActualNode().reset();
        setActualNode( popLastNode() );
    } catch(int e) {
        return Error;
    }
    return Sucess;
};

//YesOrNo Logic
int GameEngine::newYesQuestion( string initial_question )
{
    PStringNode newQuestionNode;
    try{
        newYesAnswer(initial_question);
        newQuestionNode = this->getYes();
        newQuestionNode->insertLeftNode();
        newQuestionNode->insertRightNode();
    } catch (int e){
        return Error;
    }
    return Sucess;
};

shared_ptr<StringNode> GameEngine::getYes()
{ 
    return p_tree_of_statements_->getRoot()->getLeftNode(); 
};

