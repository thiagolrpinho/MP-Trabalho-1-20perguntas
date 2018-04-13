#include "game_engine.hpp"

typedef shared_ptr<StringNode> PStringNode;

GameEngine::GameEngine()
{
    pTreeOfStatements.reset(new BTree());
    //Initial Actual Node is the start node
    this->setActualNode(getStart());
}

GameEngine::GameEngine(string initialText)
{
    pTreeOfStatements.reset(new BTree(initialText));
     //Initial Actual Node is the start node
    this->setActualNode(getStart());
}

//POSITIONING METHODS
 PStringNode GameEngine::getStart(void)
 { 
     return pTreeOfStatements->getRoot();
 };
 PStringNode GameEngine::getActualNode(void)
 {
      return pActualNode; 
 };
 int GameEngine::setActualNode( PStringNode pNextNode )
 { 
    try {
        pActualNode = pNextNode;
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

int GameEngine::writeInActualNode( string newText )
{
    try {
        return getActualNode()->setText( newText );
    } catch(int e) {
        return Error;
    }
};

int GameEngine::newYesAnswer()
{ 
    pTreeOfStatements->getRoot()->insertLeftNode();
    return Sucess; 
};

int GameEngine::newYesAnswer(string initialText)
{ 
    pTreeOfStatements->getRoot()->insertLeftNode(initialText);
    return Sucess; 
};

//DELETING METHODS
int GameEngine::removeActualNode( void )
{
    return 0;
};

//YesOrNo Logic
int GameEngine::newYesQuestion(string initialQuestion)
{
    PStringNode newQuestionNode;
    try{
        newYesAnswer(initialQuestion);
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
    return pTreeOfStatements->getRoot()->getLeftNode(); 
};

