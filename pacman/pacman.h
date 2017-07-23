#ifndef PACMAN_H_INCLUDED
#define PACMAN_H_INCLUDED

#include "pacdef.h"
#include "game.h"

void Init_pacman(State* game_state);

void Step_pacman(State* game_state);

void New_direction(State* game_state, Direction dir);

#endif // PACMAN_H_INCLUDED
