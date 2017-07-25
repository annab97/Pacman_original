#ifndef GHOST_H_INCLUDED
#define GHOST_H_INCLUDED

#include "pacdef.h"

void Init_Ghosts(State* game_state);

int Step_Ghost(State* game_state,Ghost* ghost);

void Free_Ghosts(State* game_state);

#endif // GHOST_H_INCLUDED
