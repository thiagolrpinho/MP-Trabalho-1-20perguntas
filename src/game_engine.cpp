#include "game_engine.hpp"

typedef PStringNode PStringNode;

/*! \file game_engine.cpp
    \brief Module which contains the methods of the class game_engine
*/

//! A constructor that creates a game engine with a tree of statements.
    /*!
        \Description Creates a new game engine
        and creates a binary tree to be it's tree
        of statements.
        The root value of the binary tree is empty.
        It also sets the value pointed by the actual
        node to the root of the tree and pushs the 
        root in the stack of last nodes.
    */
GameEngine::GameEngine()
{
    p_tree_of_statements_.reset( new BTree() );
    //Initial Actual Node is the start node
    this->setActualNode(getStart());
    this->pushLastNode(getStart());
    
}

//! A constructor that creates a game engine with a tree of statements with a setted root.
    /*!
        \Description Creates a new game engine
        and creates a binary tree to be it's tree
        of statements.
        The root value of the binary tree is given
        by the param.
        It also sets the value pointed by the actual
        node to the root of the tree and pushs the 
        root in the stack of last nodes.
        \param An already created String.
    */
GameEngine::GameEngine(string initial_text)
{
    p_tree_of_statements_.reset( new BTree(initial_text) );
     //Initial Actual Node is the start node
    this->setActualNode( getStart() );
    this->pushLastNode( getStart() );
}

//!POSITIONING METHODS
//! A method that returns the start of the tree of statements.
    /*!
        \return a shared pointer to the root of the tree 
        of the statements.
    */
 PStringNode GameEngine::getStart( void )
 { 
     return p_tree_of_statements_->getRoot();
 };

//! A method that returns the actual node.
    /*!
        \return a shared pointer to the node pointed
        by the actual node of the game engine.
    */
 PStringNode GameEngine::getActualNode(void)
 {
      return p_actual_node_; 
 };

 //! A method sets the actual node to the value passed as param.
    /*!
        \description Try to set the actual node pointer
        to the pointer passed as a param.
        If it didn't succeeds returns Error(enum 0).
        Else it return Success.
        \param An already existent shared pointer of stringNode.
        \return An integer 0 for Error or 1 for Success.
    */
 int GameEngine::setActualNode( PStringNode p_next_node )
 { 
    try {
        p_actual_node_ = p_next_node;
    } catch (int e) {
        return Error;
    }
    return Success;
 };

 //! A method that pops out the last shared pointer stored by the stack of last nodes.
    /*!
        \description Gets the last shared pointer at the stack,
        stores it with a new variable and removes it from the stack. 
        Then returns the new variable.
        \param None.
        \return The shared pointer of the last node.
    */
  PStringNode GameEngine::popLastNode(void)
 {   
      PStringNode pLast = stack_of_last_nodes_.top();
      stack_of_last_nodes_.pop(); 
      return pLast;
 };

  //! A method that pushes the actual node to the stack of last nodes.
    /*!
        \description Tries to push the actual node to the
        stack. If it succeeds return Success(enum 1). 
        If not, return Error(enum 0).
        \return The integer 1(Success) or 0(Error)
    */
 int GameEngine::pushLastNode( void)
 { 
    try {
        stack_of_last_nodes_.push( getActualNode() );
    } catch (int e) {
        return Error;
    }
    return Success;
 };

  //! A method that pushes a given node to the stack of last nodes.
    /*!
        \description Tries to push the node given 
        by the param to the stack. If it succeeds
        return Success(enum 1). 
        If not, return Error(enum 0).
        \return The integer 1(Success) or 0(Error)
    */
 int GameEngine::pushLastNode( PStringNode p_next_node )
 { 
    try {
        stack_of_last_nodes_.push( p_next_node );
    } catch (int e) {
        return Error;
    }
    return Success;
 };

  //! A method that changes the actual node to his left node and stores the last node.
    /*!
        \description Verifies if the left node exists.
        If not, return Error(enum 0) else it pushes 
        the actual node to the stack of last nodes.
        Then it verifies if the actual node could be
        setted to be to the left node. If it fails
        return an Error.
        If it succeeds  return Success(enum 1). 
        \return The integer 1(Success) or 0(Error)
    */
 int GameEngine::moveToYes( void )
 {
     if ( getYes() == nullptr ) return Error;
     pushLastNode(); //Stores the last node on the stack
     if( setActualNode( getYes() ) == Error ) return Error;   //Move to the Yes statement
     return Success;
 };

  //! A method that changes the actual node to his right node and stores the last node.
    /*!
        \description Verifies if the right node exists.
        If not, return Error(enum 0) else it pushes 
        the actual node to the stack of last nodes.
        Then it verifies if the actual node could be
        setted to be to the right node. If it fails
        return an Error.
        If it succeeds  return Success(enum 1). 
        \return The integer 1(Success) or 0(Error)
    */
 int GameEngine::moveToNo( void )
 {
     if ( getNo() == nullptr ) return Error;
     pushLastNode(); //Stores the last node on the stack
     if( setActualNode( getNo() ) == Error ) return Error;   //Move to the Yes statement
     return Success;
 };

   //! A method that changes the actual node to the last node visited.
    /*!
        \description Verifies if the stack of node 
        is not empty.
        If it is return an Error(enum 0).
        If not, it sets the actual node to the value
        of the last node visited by popping it out
        from the last node stack. 
        Then it return a Success(enum 1). 
        \return The integer 1(Success) or 0(Error)
    */
 int GameEngine::moveBack( void)
 {
     if ( !(stack_of_last_nodes_.empty()) )
     {
         setActualNode( popLastNode() );
         return Success;
     }
    return Error;
 };

int GameEngine::restart( void ){
    try {
        p_tree_of_statements_.reset( new BTree("New game") );
        setActualNode(getStart());
    
        while ( !stack_of_last_nodes_.empty())
        {
            popLastNode();
        }

        pushLastNode(getStart());
    } catch (int e){
        return Error;
    }

    return Success;
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
    return Success; 
};



int GameEngine::newYesAnswer(string initial_text)
{ 
    if ( getYes() != nullptr ) return Error;
    getActualNode()->insertLeftNode( initial_text );
    return Success; 
};

int GameEngine::newNoAnswer( void )
{ 
    if ( getNo() != nullptr ) return Error;
    getActualNode()->insertRightNode();
    return Success; 
};

int GameEngine::newNoAnswer(string initial_text)
{ 
    if ( getNo() != nullptr ) return Error;
    getActualNode()->insertRightNode( initial_text );
    return Success; 
};

//DELETING METHODS
int GameEngine::removeActualNode( void )
{
    try {
        PStringNode p_node_to_be_deleted = getActualNode();
        if( p_node_to_be_deleted == getStart()) return restart();
        setActualNode( popLastNode() );
        if ( p_node_to_be_deleted == getYes() )
        {
            getActualNode()->clearLeft();
        } else if ( p_node_to_be_deleted == getNo() ) 
        {
            getActualNode()->clearRight();
        } 
            p_node_to_be_deleted.reset();
    } catch(int e) {
        return Error;
    }
    return Success;
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
    return Success;
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
    if( getYes() == nullptr && getNo() == nullptr ) return Success;
    return Error;
};

//FILE MANAGING

int GameEngine::loadGame( void )
{
    return loadGame("autosave");
};

int GameEngine::loadGame( string file_name )
{
    fstream p_file_to_read;
    try {
        p_file_to_read.open("./saved_games/" + file_name + ".txt", std::fstream::in);
        if(!p_file_to_read.is_open()) return Error;
    } catch ( int e) {
        return Error;
    }
    restart();
    if ( readFile( p_file_to_read ) == Error ) return Error;

    p_file_to_read.close();
    return Success;
};

int GameEngine::saveGame( void )
{
    return saveGame("autosave");
};

int GameEngine::saveGame( string file_name )
{
  fstream p_file_to_write;
  pushLastNode(); //Armazena o contexto atual da árvore
  setActualNode( getStart() ); //Começa a ler a do início da árvore
  try {
    p_file_to_write.open("./saved_games/" + file_name + ".txt", std::fstream::out | std::fstream::trunc);
    if(!p_file_to_write.is_open()) return Error;
  } catch ( int e) {
    return Error;
  }
  if ( writeInFile(p_file_to_write) == Error ) return Error;
  setActualNode( popLastNode() ); //Retorna ao contexto anterior.
    p_file_to_write.close();

    return Success;
};

int GameEngine::writeInFile( fstream &p_file_to_write )
{
  //First the engine write the actual statement on file
  //them check if the Yes statement exist.
  //If not, it write an # and checks the No statement
  //If yes, it moves to the node and do the same.
  try {
      p_file_to_write << readActualNode() << ";";

      if ( moveToYes() == Error )
      {
      p_file_to_write << "#;";
      } else {
          if ( writeInFile( p_file_to_write ) == Error ) return Error;
          moveBack();
      }

      if ( moveToNo() == Error)
      {
          p_file_to_write << "#;";
      } else {
          if ( writeInFile( p_file_to_write ) == Error ) return Error;
          moveBack();
      }
  } catch (int e){
      return Error;
  }
  return Success;
}

int GameEngine::readFile( fstream &p_file_to_read )
{
    string node_statement;
    try {
        getline(p_file_to_read, node_statement, ';');
        if( p_file_to_read.eof() ) return Error;
        if ( node_statement.compare("#") == Equals ) return Error;
        writeInActualNode( node_statement );

        newYesAnswer();
        if( moveToYes() == Error) return Error;
        if( readFile( p_file_to_read ) == Error )
        {
            removeActualNode();
        } else { 
            moveBack();
        }

        newNoAnswer();
        if( moveToNo() == Error ) return Error;
        if( readFile( p_file_to_read ) == Error )
        {
            removeActualNode();
        } else { 
            moveBack();
        }
    
    } catch ( int e ) {
        return Error;
    }

    return Success;
};
