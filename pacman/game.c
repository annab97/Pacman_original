#include "game.h"
#include "pacman.h"


//basic
int Init_game(State** game_state)
{
    *game_state=malloc(sizeof(State));
    Init_field(&((*game_state)->field));
    Init_pacman(*game_state);
}

int Restart();

int Close_game(State** game_state)
{
    free((* game_state)->field);
    free((* game_state)->pacman);
    free(*game_state);
}

// game
int Step(State* game_state)
{
    Step_pacman(game_state);
    return 1;
}

int Move_pacman(State* game_state, Direction dir)
{
    New_direction(game_state, dir);
}
