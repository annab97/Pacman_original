#include "ghost.h"

void Init_ghost(Ghost* ghost, GHOST name,int x,int y)
{
    ghost->name=name;
    ghost->y=y;
    ghost->x=x;
    ghost->windowx=ghost->x*8-4;
    ghost->windowy=ghost->y*8-4;
    ghost->d=Standing;
}
void Blinky_AI(State* game_state)
{
    Ghost* blinky=game_state->Blinky;
    switch(game_state->currentState)
    {
        case CHASE:
        blinky->Target.x=game_state->pacman->x;
        blinky->Target.y=game_state->pacman->y;
        break;
        case SCATTER:
        blinky->Target=blinky->home;
        break;
        case FRIGHTENING:
        blinky->d=Standing;
        blinky->Target=blinky->home;
        break;
    }

}
/*void Pinky_AI(State* game_state)
{
    Ghost* pinky=game_state->Pinky;
    switch(game_state->ls->modetable->modes[game_state->modeid].name)
    {
        case CHASE:
        Position pacpos={game_state->pacman.x,game_state->pacman->y};
        Position nextpos=Nextmove(pacpos,game_state->pacman->d);
        Position nnpos=Nextmove(pacpos,game_state->pacman->d);
        pinky->Target=nnpos;
        break;
        case SCATTER:
        pinky->Target=pinky->home;
        break;
        case FRIGHTENING:
        //frightening
        break;
    }

}*/
/*void Inky_AI(State* game_state)
{
    Ghost* inky=game_state->Inky;
    switch(game_state->ls->modetable->modes[game_state->modeid].name)
    {
        case CHASE:
        Position pacpos={game_state->pacman.x,game_state->pacman->y};
        Position nextpos=Nextmove(pacpos,game_state->pacman->d);
        Position nnpos=Nextmove(pacpos,game_state->pacman->d);
        pinky->Target=nnpos;
        break;
        case SCATTER:
        pinky->Target=pinky->home;
        break;
        case FRIGHTENING:
        //frightening
        break;
    }
}*/

void Init_Ghosts(State* game_state)
{
    game_state->Blinky=malloc(sizeof(Ghost));
    Init_ghost(game_state->Blinky,BLINKY,13,14);
    game_state->Blinky->NextTarget=Blinky_AI;
    game_state->Blinky->home.y=0; game_state->Blinky->home.x=COLUMNS-2;
    game_state->Blinky->Target=game_state->Blinky->home;

    game_state->Pinky=malloc(sizeof(Ghost));
    Init_ghost(game_state->Pinky,PINKY,11,17);

    game_state->Inky=malloc(sizeof(Ghost));
    Init_ghost(game_state->Inky,INKY,13,17);

    game_state->Clyde=malloc(sizeof(Ghost));
    Init_ghost(game_state->Clyde,CLYDE,15,17);
}

int Opposite(Direction d1,Direction d2)
{
    if(d1==Standing ||  d2==Standing)
        return 0;
    int opp=(d1>d2?d1-d2:d2-d1);
    return (opp==2);
}
int Forbidden(Position p)
{
    return ((p.y==13 && p.x==12) || (p.y==13 && p.x==15) || (p.y==25 && p.x==12) || (p.y==25 && p.x==15));
}
int Step_Ghost(State* game_state,Ghost* ghost)
{
    if(ghost->windowx%8==4 && ghost->windowy%8==4)
    {
        ghost->NextTarget(game_state);
        Position ghostpos; ghostpos.x=ghost->x; ghostpos.y=ghost->y;
        int min=ROWS*COLUMNS*ROWS*COLUMNS;
        int mini=0;
        for(int i=1;i<5;i++)
        {
            Position nextpos=Nextmove(ghostpos,i);
            if(game_state->field->table[nextpos.y][nextpos.x]<=2 &&
                !Opposite(ghost->d,i) && !(i==Up && Forbidden(nextpos)))
            {
                int dis=Distance(ghost->Target,nextpos);
                if(min>dis)
                {
                   min=dis;
                   mini=i;
                }
            }
        }
        ghost->d=mini;
    }
    switch(ghost->d)
    {
        case Standing:
        break;
        case Up:
        ghost->windowy-=2;
        ghost->y=ghost->windowy/8+1;
        break;
        case Down:
        ghost->windowy+=2;
        ghost->y=ghost->windowy/8+1;
        break;
        case Left:
        ghost->windowx-=2;
        ghost->x=ghost->windowx/8+1;
        break;
        case Right:
        ghost->windowx+=2;
        ghost->x=ghost->windowx/8+1;
    }
     if(ghost->windowx<4)
    {
        ghost->windowx=(COLUMNS-1)*8-6;
        ghost->x=COLUMNS-1;
    }
    if(ghost->windowx>=(COLUMNS-1)*8-4)
    {
        ghost->windowx=6;
        ghost->x=1;
    }
    if(ghost->y==17 && (ghost->x<6 || ghost->x>21))
    {
        return 45;
    }
    return 75;

}

Direction Opposite_dir(Direction dir)
{
    switch(dir)
    {
        case Standing:
        return Standing;
        case Up:
        return Down;
        case Down:
        return Up;
        case Left:
        return Right;
        case Right:
        return Left;
    }
}

void Reverse_ghost_direction(State* game_state)
{
    State* gm=game_state;
    gm->Blinky->d=Opposite_dir(gm->Blinky->d);
    gm->Pinky->d=Opposite_dir(gm->Pinky->d);
    gm->Inky->d=Opposite_dir(gm->Inky->d);
    gm->Clyde->d=Opposite_dir(gm->Clyde->d);
}

void Free_Ghosts(State* game_state)
{
    free(game_state->Blinky);
    free(game_state->Pinky);
    free(game_state->Inky);
    free(game_state->Clyde);
}
