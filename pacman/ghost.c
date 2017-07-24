#include "ghost.h"

void Init_Ghosts(State* game_state)
{
    game_state->Blinky=malloc(sizeof(Ghost));
    Ghost* blinky=game_state->Blinky;
    blinky->name=BLINKY;
    blinky->y=14;
    blinky->x=13;
    blinky->windowx=game_state->Blinky->x*8-4;
    blinky->windowy=game_state->Blinky->y*8-4;
    blinky->d=Standing;
}

void Step_Ghost(State* game_state,Ghost* ghost)
{
}

void Free_Ghosts(State* game_state)
{
    free(game_state->Blinky);
}
