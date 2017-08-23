#ifndef GHOST_H_INCLUDED
#define GHOST_H_INCLUDED

#include "pacdef.h"

void Init_Ghosts(State* game_state);

int Step_Ghost(State* game_state,Ghost* ghost);

void Reverse_ghost_direction(State* game_state);

void Go_frightening(Ghost* ghost);

void Flash_ghosts(State* game_state);

void Stop_frightening(Ghost* ghost);

void Free_Ghosts(State* game_state);

#endif // GHOST_H_INCLUDED
