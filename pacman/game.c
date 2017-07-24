#include "game.h"


//basic
int Init_game(State** game_state)
{
    *game_state=malloc(sizeof(State));
    Init_field(&((*game_state)->field));
    Init_pacman(*game_state);
    Init_Ghosts(*game_state);
}

int Restart();

int Close_game(State** game_state)
{
    free((* game_state)->field);
    free((* game_state)->pacman);
    Free_Ghosts(*game_state);
    free(*game_state);

}
