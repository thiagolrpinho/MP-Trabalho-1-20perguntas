#include "game_engine.hpp"

typedef PStringNode PStringNode;

GameEngine::GameEngine()
{
    p_tree_of_statements_.reset( new BTree() );
    //Initial Actual Node is the start node
    this->setActualNode(getStart());
    this->pushLastNode(getStart());
    
}

GameEngine::GameEngine(string initial_text)
{
    p_tree_of_statements_.reset( new BTree(initial_text) );
     //Initial Actual Node is the start node
    this->setActualNode( getStart() );
    this->pushLastNode( getStart() );
}

//POSITIONING METHODS
 PStringNode GameEngine::getStart( void )
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

 int GameEngine::pushLastNode( void)
 { 
    try {
        stack_of_last_nodes_.push( getActualNode() );
    } catch (int e) {
        return Error;
    }
    return Sucess;
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

 int GameEngine::moveToYes( void )
 {
     if ( getYes() == nullptr ) return Error;
     pushLastNode(); //Stores the last node on the stack
     if( setActualNode( getYes() ) == Error ) return Error;   //Move to the Yes statement
     return Sucess;
 };


 int GameEngine::moveToNo( void )
 {
     if ( getNo() == nullptr ) return Error;
     pushLastNode(); //Stores the last node on the stack
     if( setActualNode( getNo() ) == Error ) return Error;   //Move to the Yes statement
     return Sucess;
 };

int GameEngine::restart( void ){
    try {
        p_actual_node_.reset();
        p_tree_of_statements_.reset();
    } catch (int e){
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
    if ( getYes() != nullptr ) return Error;
    getActualNode()->insertLeftNode();
    return Sucess; 
};

int GameEngine::newYesAnswer(string initial_text)
{ 
    if ( getYes() != nullptr ) return Error;
    getActualNode()->insertLeftNode( initial_text );
    return Sucess; 
};

int GameEngine::newNoAnswer(string initial_text)
{ 
    if ( getNo() != nullptr ) return Error;
    getActualNode()->insertRightNode( initial_text );
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

PStringNode GameEngine::getYes( void )
{ 
    return getActualNode()->getLeftNode(); 
};

PStringNode GameEngine::getNo( void )
{ 
    return getActualNode()->getRightNode(); 
};

//Question Logic

int GameEngine::checkGuess( void )
{
    if( getYes() == nullptr && getNo() == nullptr ) return Sucess;
    return Error;
};

//FILE MANAGING

int GameEngine::readFile( void )
{
    fstream p_file_to_read;
    try {
        p_file_to_read.open("./text.txt", std::fstream::in);
    } catch ( int e) {
        return Error;
    }

    p_file_to_read.close();
    return Sucess;
};

int GameEngine::saveGame( void )
{
    fstream p_file_to_write;
        try {
            p_file_to_write.open("./text.txt", std::fstream::out);
        } catch ( int e) {
            return Error;
        }

        p_file_to_write.close();
        return Sucess;
};

int GameEngine::writeInFile( fstream* pp_file_to_write )
{
    return Error;
}
