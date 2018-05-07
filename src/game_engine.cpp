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
    p_tree_of_statements_.reset(new BTree());
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
    p_tree_of_statements_.reset(new BTree(initial_text));
    //Initial Actual Node is the start node
    this->setActualNode(getStart());
    this->pushLastNode(getStart());
}

///!POSITIONING METHODS
//! A method that returns the start of the tree of statements.
/*!
    \return a shared pointer to the root of the tree 
    of the statements.
*/
PStringNode GameEngine::getStart(void)
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
int GameEngine::setActualNode(PStringNode p_next_node)
{
    try
    {
        p_actual_node_ = p_next_node;
    }
    catch (int e)
    {
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
int GameEngine::pushLastNode(void)
{
    try
    {
        stack_of_last_nodes_.push(getActualNode());
    }
    catch (int e)
    {
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
int GameEngine::pushLastNode(PStringNode p_next_node)
{
    try
    {
        stack_of_last_nodes_.push(p_next_node);
    }
    catch (int e)
    {
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
int GameEngine::moveToYes(void)
{
    if (getYes() == nullptr)
        return Error;
    pushLastNode(); //Stores the last node on the stack
    if (setActualNode(getYes()) == Error)
        return Error; //Move to the Yes statement
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
int GameEngine::moveToNo(void)
{
    if (getNo() == nullptr)
        return Error;
    pushLastNode(); //Stores the last node on the stack
    if (setActualNode(getNo()) == Error)
        return Error; //Move to the Yes statement
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
int GameEngine::moveBack(void)
{
    if (!(stack_of_last_nodes_.empty()))
    {
        setActualNode(popLastNode());
        return Success;
    }
    return Error;
};

//! A method that sets the game engine to an initial state.
/*!
    \description  Tries to:
    Reset the tree of statements to a new binary tree 
    with root valued as "New Game".
    Changes the actual node to the binary tree's root.
    Empties the stack then pushes the actual node to
    it.
    If it fails return an Error(enum 0).
    If not, it return a Success(enum 1). 
    \return The integer 1(Success) or 0(Error)
*/
int GameEngine::restart(void)
{
    try
    {
        p_tree_of_statements_.reset(new BTree("New game"));
        setActualNode(getStart());

        while (!stack_of_last_nodes_.empty())
        {
            popLastNode();
        }

        pushLastNode(getStart());
    }
    catch (int e)
    {
        return Error;
    }

    return Success;
};

///!READING AND WRITING METHODS
//! A method that returns the value of the actual node.
/*!
    \return a string copy of the text inside
    actual node.
*/
string GameEngine::readActualNode(void)
{
    return getActualNode()->getText();
};

//! A method to that sets the value of the actual node.
/*!
    \description 
    Try to change the text of the actual node
    with the given string passed as param.
    If it fails return an Error(enum 0).
    If not, return a Success(enum 1).
    \param An already created string.
    \return The integer 1(Success) or 0(Error)
*/
int GameEngine::writeInActualNode(string new_text)
{
    try
    {
        return getActualNode()->setText(new_text);
    }
    catch (int e)
    {
        return Error;
    }
};

//! A method that creates a new node with empty text at left of the actual node.
/*!
    \description 
    Verifies if there's already a node in
    the left branch of the actual node.
    If yes, returns an Error(enum 0).
    If no, creates a new node with empty
    value and sets left branch to point
    to it then return a Success(enum 1).
    \return The integer 1(Success) or 0(Error)
*/
int GameEngine::newYesAnswer()
{
    if (getYes() != nullptr)
        return Error;
    getActualNode()->insertLeftNode();
    return Success;
};

//! A method that creates a new node with a given value at left of the actual node.
/*!
    \description 
    Verifies if there's already a node in
    the left branch of the actual node.
    If yes, returns an Error(enum 0).
    If no, creates a new node with
    value equal to the one given as param
    and sets left branch to point to it 
    then return a Success(enum 1).
    \param An already created string.
    \return The integer 1(Success) or 0(Error)
*/
int GameEngine::newYesAnswer(string initial_text)
{
    if (getYes() != nullptr)
        return Error;
    getActualNode()->insertLeftNode(initial_text);
    return Success;
};

//! A method that creates a new node with empty text at right of the actual node.
/*!
    \description 
    Verifies if there's already a node in
    the right branch of the actual node.
    If yes, returns an Error(enum 0).
    If no, creates a new node with empty
    value and sets right branch to point
    to it then return a Success(enum 1).
    \return The integer 1(Success) or 0(Error)
*/
int GameEngine::newNoAnswer(void)
{
    if (getNo() != nullptr)
        return Error;
    getActualNode()->insertRightNode();
    return Success;
};

//! A method that creates a new node with a given value at right of the actual node.
/*!
    \description 
    Verifies if there's already a node in
    the right branch of the actual node.
    If yes, returns an Error(enum 0).
    If no, creates a new node with
    value equal to the one given as param
    and sets right branch to point to it 
    then return a Success(enum 1).

    \param An already created string.
    \return The integer 1(Success) or 0(Error)
*/
int GameEngine::newNoAnswer(string initial_text)
{
    if (getNo() != nullptr)
        return Error;
    getActualNode()->insertRightNode(initial_text);
    return Success;
};

///! DELETING METHODS
//! A method that deletes the actual node and those bellow it.
/*!
    \description Tries to:
    Stores the actual node pointer temporalily 
    as the node to be deleted.
    Verifies if it's the root. If it is
    call restart() method. 
    If not, changes actual node to the pointer
    of the last node visited by popping stack
    of last nodes.
    Then if the node to be deleted is the 
    left node of the actual node. Calls 
    clearLeft() method. If not, verifies 
    if it is the right node and if it is
    right node of the actual node. Calls
    clearRight(). 
    Then calls reset() on the node to be
    deleted.
    If any of this fails, return an 
    Error(enum 0).
    Else it return a Success(enum 1).

    \return The integer 1(Success) or 0(Error)
*/
int GameEngine::removeActualNode(void)
{
    try
    {
        PStringNode p_node_to_be_deleted = getActualNode();
        if (p_node_to_be_deleted == getStart())
            return restart();
        setActualNode(popLastNode());
        if (p_node_to_be_deleted == getYes())
        {
            getActualNode()->clearLeft();
        }
        else if (p_node_to_be_deleted == getNo())
        {
            getActualNode()->clearRight();
        }
        p_node_to_be_deleted.reset();
    }
    catch (int e)
    {
        return Error;
    }
    return Success;
};

///! YesOrNo Logic
//! A method creates a new Question with a given value as the left branch of the actual node.
/*!
    \description Tries to:
    Create a newYesAnswer with the given
    param value as the initial text.
    Sets the left branch of the actual node
    to points to the new created node.
    Then creates a new empty left and a new 
    empty right nodes on the branches of 
    the firstly created node.
    If something fails, returns Error(enum 0).
    Else it returns Success(enum 1).
    \param An already created string to be the initial value.
    \return The integer 1(Success) or 0(Error)
*/
int GameEngine::newYesQuestion(string initial_question)
{
    PStringNode newQuestionNode;
    try
    {
        newYesAnswer(initial_question);
        newQuestionNode = this->getYes();
        newQuestionNode->insertLeftNode();
        newQuestionNode->insertRightNode();
    }
    catch (int e)
    {
        return Error;
    }
    return Success;
};

//! A method that returns the left node of the actual node.
/*!
    \return a shared pointer of the left node of the 
    actual node.
*/
PStringNode GameEngine::getYes(void)
{
    return getActualNode()->getLeftNode();
};

//! A method that returns the right node of the actual node.
/*!
    \return a shared pointer of the right node of the 
    actual node.
*/
PStringNode GameEngine::getNo(void)
{
    return getActualNode()->getRightNode();
};

///! Question Logic
//! A method that checks if the node has branches.
/*!     
    \description Return a Success(enum 1) 
    if there's no branches. Otherwise 
    returns an Error(enum 0). 
    \return The integer 1(Success) or 0(Error)
*/
int GameEngine::checkGuess(void)
{
    if (getYes() == nullptr && getNo() == nullptr)
        return Success;
    return Error;
};

///!FILE MANAGING
//! A method that loads a game engine state that was saved as "autosave"
/*!     
    \return The integer 1(Success) or 0(Error)
*/
int GameEngine::loadGame(void)
{
    return loadGame("autosave");
};

//! A method that loads a game engine state with a given name
/*!     
    \Description
    try to:
    Open a file with the given name that is inside the the 
    folder saved_games that should be a subdirectory of the
    folder that the programs is running. The file_name
    should not be passed with a file extension. It'll be 
    put by the algorithm.
    If it fails at any point, the method will return an Error
    (integer 0);
    If this Succeeds then the game engine will be restarted.
    After this, the algorithm calls a method readFile() and 
    verifies if it will return an Error(integer 0) if so
    loadGame() return a Error(integer 0).
     If not the file pointeris freed and returns a 
     Success(Integer 1).
    \param An already existent string of a file
     name(without extension)that was already created inside 
     the folder ./saved_games/
    \return The integer 1(Success) or 0(Error)
*/
int GameEngine::loadGame(string file_name)
{
    fstream p_file_to_read;
    try
    {
        p_file_to_read.open("./saved_games/" + file_name + ".txt", std::fstream::in);
        if (!p_file_to_read.is_open())
            return Error;
    }
    catch (int e)
    {
        return Error;
    }
    restart();
    if (readFile(p_file_to_read) == Error)
        return Error;

    p_file_to_read.close();
    return Success;
};

//! A method that save a game engine state as "autosave"
/*!     
    \return The integer 1(Success) or 0(Error)
*/
int GameEngine::saveGame(void)
{
    return saveGame("autosave");
};

//! A method that saves a game engine state with a given name
/*!     
    \Description
    try to:
    Open or creates(if not existent)a file with the given
    name that is inside the the folder saved_games that 
    will be a subdirectory of the folder that the 
    programs is running. 
    The file_name should not be passed with a file extension.
     It'll be put by the algorithm.
    If it fails at any point, the method will return an Error
    (integer 0);
    If this Succeeds the algorithm calls a method writeInFile()
    and verifies if it will return an Error(integer 0) if so
    saveGame() returns a Error(integer 0). 
    If not the game engine returns to the state before by poping
    last state node and seting it to be the actual node then file
     pointer is freed and it returns a Success(Integer 1).
    \param An already existent string.
    \return The integer 1(Success) or 0(Error)
*/
int GameEngine::saveGame(string file_name)
{
    fstream p_file_to_write;
    pushLastNode();            //Armazena o contexto atual da árvore
    setActualNode(getStart()); //Começa a ler a do início da árvore
    try
    {
        p_file_to_write.open("./saved_games/" + file_name + ".txt", std::fstream::out | std::fstream::trunc);
        if (!p_file_to_write.is_open())
            return Error;
    }
    catch (int e)
    {
        return Error;
    }
    if (writeInFile(p_file_to_write) == Error)
        return Error;
    setActualNode(popLastNode()); //Retorna ao contexto anterior.
    p_file_to_write.close();

    return Success;
};

//! A method that writes on a file the tree of statements of game engine.
/*!     
    \Description
    try to:
    write in the file the actual node value followed 
    by the separator ';'then it checks if it's possible 
    to move to the left branch. If it's not, then it's 
    an empty branch so it writes '#;' on the file. If it 
    can move to the left branch. The method calls itself
    recursively. If the recursion return an Error(integer 0)
    the actual method also return an Error(integer 0). Else
    it moves back to the node that was read before calling the
    recursion and does the same to the right branch.
    If any of this fails, the method returns an Error(integer 0).
    If everything Succeeds, it return a Success(integer 1).

    \param An already existent pointer to a file already opened.
    \return The integer 1(Success) or 0(Error)
*/
int GameEngine::writeInFile(fstream &p_file_to_write)
{
    //First the engine write the actual statement on file
    //them check if the Yes statement exist.
    //If not, it write an # and checks the No statement
    //If yes, it moves to the node and do the same.
    try
    {
        p_file_to_write << readActualNode() << ";";

        if (moveToYes() == Error)
        {
            p_file_to_write << "#;";
        }
        else
        {
            if (writeInFile(p_file_to_write) == Error)
                return Error;
            moveBack();
        }

        if (moveToNo() == Error)
        {
            p_file_to_write << "#;";
        }
        else
        {
            if (writeInFile(p_file_to_write) == Error)
                return Error;
            moveBack();
        }
    }
    catch (int e)
    {
        return Error;
    }
    return Success;
}

//! A method that reads a file and writes on the tree of statements of a game engine.
/*!     
    \Description
    Game engine should have been restarted before calling
    this method.
    try to:
    Read the line pointed by the file pointer until 
    the separator ';' is found and stores it on the
    string node_statement.
    Verifies if it's already on the end of the file.
    If it's, returns a Error(integer 0).
    This occurs because the first read should be followed
    by two more separators.
    Else the method checks if the read string is 
    '#', if it is returns a Error(integer 0).
    This occurs because the first read should be a valid
    node.
    Else it writes the read string on the actual node.
    Then it creates a new left node, verifies if the
    creation was successfull(if not returns a Error(integer 0))
    and then calls itself recursively. If the recursion 
    returns an Error(integer 0) the new branch is undone.
    Else it moves back to the previous state where actual
    node was the first node wrote by this method.
    The it creates a right node of the actual node and does
    the same behaviour.
    If any of this fails, it returns an Error(integer 0).
    Else it returns a Success(integer 1).
    \param An already existent pointer to a file already opened.
    \return The integer 1(Success) or 0(Error)
*/
int GameEngine::readFile(fstream &p_file_to_read)
{
    string node_statement;
    try
    {
        getline(p_file_to_read, node_statement, ';');
        if (p_file_to_read.eof())
            return Error;
        if (node_statement.compare("#") == Equals)
            return Error;
        writeInActualNode(node_statement);

        newYesAnswer();
        if (moveToYes() == Error)
            return Error;
        if (readFile(p_file_to_read) == Error)
        {
            removeActualNode();
        }
        else
        {
            moveBack();
        }

        newNoAnswer();
        if (moveToNo() == Error)
            return Error;
        if (readFile(p_file_to_read) == Error)
        {
            removeActualNode();
        }
        else
        {
            moveBack();
        }
    }
    catch (int e)
    {
        return Error;
    }

    return Success;
};
