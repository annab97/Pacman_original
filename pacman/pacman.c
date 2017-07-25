#include "pacman.h"

void Init_pacman(State* game_state)
{
    game_state->pacman=malloc(sizeof(Pacman));
    Pacman* pac=game_state->pacman;
    pac->x=13;
    pac->y=26;
    pac->windowx=pac->x*8-4;
    pac->windowy=pac->y*8-4;
    pac->next_step=Standing;
    pac->frame=FULL;
    pac->d=Standing;
    pac->nextd=Standing;
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



int Step_pacman(State* game_state){
    int hasEaten=0;

    PACFRAME nf=Next_frame(game_state->pacman);
    Pacman* pac=game_state->pacman;

    Position pacpos={pac->x,pac->y};
    Position nextpos=Nextmove(pacpos,pac->nextd);
    Position spos=Nextmove(pacpos,pac->d);

    /*if(pac->cornering!=0)
    {
        if(pac->d==Right && pac.windowx%8>=0 && pac.windowx%8<4)
        {
            if(pac->cornering==Up)
                pac->windowy-=2;
            if(pac->cornering==Down)
                pac->windowy+=2;
        }
        if(pac->d==Left && pac.windowx%8>=0 && pac.windowx%8<4)
        {
            if(pac->cornering==Up)
            {
                pac->windowy-=2;
                pac
            }
            if(pac->cornering==Down)
                pac->windowy+=2;
        }
    }*/

    if(pac->windowx%8==4 && pac->windowy%8==4)
    {

            //try_turn
            if(game_state->field->table[spos.y][spos.x]<=2)
                pac->next_step=pac->d;
            else
                pac->next_step=Standing;
            pac->d=pac->next_step;


    }
    if(pac->nextd!= pac->d && game_state->field->table[nextpos.y][nextpos.x]<=2)
    {

        switch(pac->nextd)
        {
            case Standing:
            break;
            case Up:
            pac->windowy-=2;
            if(pac->windowx%8==4)
                pac->d=pac->nextd;
            if(pac->d==Right && pac->windowx%8>4)
                pac->windowx-=4;
            if(pac->d==Left && pac->windowx%8<4)
                pac->windowx+=4;
            break;
            case Down:
            pac->windowy+=2;
            if(pac->windowx%8==4)
                pac->d=pac->nextd;
            if(pac->d==Right && pac->windowx%8>4)
                pac->windowx-=4;
            if(pac->d==Left && pac->windowx%8<4)
                pac->windowx+=4;
            break;
            case Left:
            pac->windowx-=2;
            if(pac->windowy%8==4)
                pac->d=pac->nextd;
            if(pac->d==Down && pac->windowy%8>4)
                pac->windowy-=4;
            if(pac->d==Up && pac->windowy%8<4)
                pac->windowy+=4;
            break;
            case Right:
            pac->windowx+=2;
            if(pac->windowy%8==4)
                pac->d=pac->nextd;
            if(pac->d==Down && pac->windowy%8>4)
                pac->windowy-=4;
            if(pac->d==Up && pac->windowy%8<4)
                pac->windowy+=4;
            break;
        }
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
    if(pac->windowx<4)
    {
        pac->windowx=(COLUMNS-1)*8-6;
        pac->x=COLUMNS-1;
    }
    if(pac->windowx>=(COLUMNS-1)*8-4)
    {
        pac->windowx=6;
        pac->x=1;
    }
    if(game_state->field->table[pac->y][pac->x]==POINT)
    {
        game_state->points+=10;
        hasEaten=1;
        game_state->field->table[pac->y][pac->x]=EMPTY;
    }
    if(game_state->field->table[pac->y][pac->x]==ENERGISER)
    {
        game_state->points+=50;
        hasEaten=2;
        game_state->field->table[pac->y][pac->x]=0;
    }
    game_state->pacman->frame=nf;
    return hasEaten;

}

void Move_pacman(State* game_state, Direction dir)
{
    game_state->pacman->nextd=dir;
}
