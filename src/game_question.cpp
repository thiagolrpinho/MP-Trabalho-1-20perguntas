#include "game_question.hpp"


GameQuestion::GameQuestion()
{
    pBTree.reset(new BTree());
}

GameQuestion::GameQuestion(string initialText)
{
    pBTree.reset(new BTree(initialText));
}

int GameQuestion::newYesAnswer()
{ 
    pBTree->getRoot()->insertLeftNode();
    return Sucess; 
};

shared_ptr<StringNode> GameQuestion::getYes()
{ 
    return pBTree->getRoot()->getLeftNode();     
};

