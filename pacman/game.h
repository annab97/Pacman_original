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

int Change_mode(State* game_state);

int Start_frightening(State* game_state);

void End_frightening(State* game_state);

#endif // PACMAN_H_INCLUDED
