#include "pacman.h"

void Init_pacman(State* game_state)
{
    game_state->pacman=malloc(sizeof(Pacman));
    Pacman* pac=game_state->pacman;
    pac->x=13;
    pac->y=26;
    pac->windowx=pac->x*8-4;
    pac->windowy=pac->y*8-4;
    pac->next_step=Left;
    pac->frame=FULL;
    pac->d=Left;
    pac->nextd=Left;
}

Position Nextmove(Position pos, Direction dir)
{
    Position nextpos;
    nextpos.x=pos.x;
    nextpos.y=pos.y;
    switch(dir)
    {
        case Standing:
        break;
        case Up:
        nextpos.y--;
        break;
        case Down:
        nextpos.y++;
        break;
        case Right:
        nextpos.x++;
        break;
        case Left:
        nextpos.x--;
        break;
    }
    return nextpos;
}

PACFRAME Next_frame(Pacman* pac)
{
    if(pac->d==Standing)
        return pac->frame;
    if(pac->frame>=LSSMALL)
        return FULL;
    if(pac->frame==FULL)
        return pac->d;
    PACFRAME p=((pac->frame-1)/4+1)*4+pac->d;
    return ((pac->frame-1)/4+1)*4+pac->d;
}

Go_straight(Pacman* pac)
{
    pac->next_step=pac->d;

}


void Step_pacman(State* game_state){
    PACFRAME nf=Next_frame(game_state->pacman);
    Pacman* pac=game_state->pacman;

    if(pac->windowx%8==4 && pac->windowy%8==4)
    {

            //try_turn
            Position pacpos={pac->x,pac->y};
            Position nextpos=Nextmove(pacpos,pac->nextd);
            Position spos=Nextmove(pacpos,pac->d);
            //Position nnpos=Nextmove(nextpos,pac->nextd);
            if(game_state->field->table[nextpos.y][nextpos.x]<=2)
                pac->next_step=pac->nextd;
            else if(game_state->field->table[spos.y][spos.x]<=2)
                pac->next_step=pac->d;
            else
                pac->next_step=Standing;
            pac->d=pac->next_step;


    }
    switch(pac->d)
    {
        case Standing:
        break;
        case Up:
        pac->windowy-=2;
        pac->y=pac->windowy/8+1;
        break;
        case Down:
        pac->windowy+=2;
        pac->y=pac->windowy/8+1;
        break;
        case Left:
        pac->windowx-=2;
        pac->x=pac->windowx/8+1;
        break;
        case Right:
        pac->windowx+=2;
        pac->x=pac->windowx/8+1;
        break;
    }
    game_state->pacman->frame=nf;

}

void New_direction(State* game_state, Direction dir)
{
    game_state->pacman->nextd=dir;
}
