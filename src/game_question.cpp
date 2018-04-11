#include "game_question.hpp"


GameQuestion::GameQuestion()
{
    pBTree.reset(new BTree());
}

GameQuestion::GameQuestion(string initialText)
{
    pBTree.reset(new BTree(initialText));
}

