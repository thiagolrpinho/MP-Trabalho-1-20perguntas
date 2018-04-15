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

 int GameEngine::moveBack( void)
 {
     if ( !(stack_of_last_nodes_.empty()) )
     {
         setActualNode( popLastNode() );
         return Sucess;
     }
    return Error;
 };

int GameEngine::restart( void ){
    try {
        p_tree_of_statements_.reset( new BTree() );
        setActualNode(getStart());
    
        while ( !stack_of_last_nodes_.empty())
        {
            popLastNode();
        }

        pushLastNode(getStart());
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

int GameEngine::newNoAnswer( void )
{ 
    if ( getNo() != nullptr ) return Error;
    getActualNode()->insertRightNode();
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
        PStringNode p_node_to_be_deleted = getActualNode();
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
    return Sucess;
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

        return Sucess;
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
    return Sucess;
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

    return Sucess;
};
