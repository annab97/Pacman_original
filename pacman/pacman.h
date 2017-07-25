#ifndef PACMAN_H_INCLUDED
#define PACMAN_H_INCLUDED

#include "pacdef.h"


void Init_pacman(State* game_state);

int Step_pacman(State* game_state);

void Move_pacman(State* game_state, Direction dir);

#endif // PACMAN_H_INCLUDED
