#include "game_interface.hpp"

typedef shared_ptr<GameInterface> PGameInterface;


int main(void)
{
    PGameInterface p_20_questions_game(new GameInterface);
    p_20_questions_game->openMenu();
    return 0;
}