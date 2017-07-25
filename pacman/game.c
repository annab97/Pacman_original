#include "game.h"
#include <stdio.h>


//basic
int Init_game(State** game_state)
{
    *game_state=malloc(sizeof(State));
    Init_field(&((*game_state)->field));
    Init_pacman(*game_state);
    Init_Ghosts(*game_state);
    State* gs=*game_state;
    gs->modeid=0;
    gs->dotseaten=0;
    gs->points=0;
    gs->levelid=0;
    LevelState* stages=malloc(21*sizeof(LevelState));
    FILE* fp;
    fp=fopen("levelStates.dat","rb");
    if(fp==NULL)
    {
        perror("Coun't open file");
    }
    fread(stages,sizeof(LevelState),21,fp);
    fclose(fp);
    gs->ls=stages;
    return 0;
}

int Restart();

int Close_game(State** game_state)
{
    free((* game_state)->field);
    free((* game_state)->pacman);
    Free_Ghosts(*game_state);
    free(*game_state);
    free((*game_state)->ls);
    return 0;
}

int Change_mode(State* game_state)
{
    game_state->modeid++;
    game_state->currentState=game_state->ls[game_state->levelid].modes[game_state->modeid].name;
    Reverse_ghost_direction(game_state);
    if(game_state->Blinky->d==Standing)
        printf("%d",game_state->Blinky->d);
    return game_state->ls[game_state->levelid].modes[game_state->modeid].delay;
}

int Start_frightening(State* game_state)
{
    game_state->currentState=FRIGHTENING;
    Reverse_ghost_direction();
    return game_state->ls[game_state->levelid].fright_time*1000;
}

void End_frightening(State* game_state)
{
 game_state->currentState=game_state->ls[game_state->levelid].modes[game_state->modeid].name;
}
