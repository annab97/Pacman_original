#ifndef PACMAN_H_INCLUDED
#define PACMAN_H_INCLUDED

#include "pacdef.h"
#include "field.h"
#include "pacman.h"
#include "ghost.h"

//basic
int Init_game(State** game_state);

int Restart();

int Close_game(State** game_state);

// game
int Step(State* game_state);

int Move_pacman(State* game_state, Direction dir);

#endif // PACMAN_H_INCLUDED
