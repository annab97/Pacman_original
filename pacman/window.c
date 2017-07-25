#include "window.h"

#define TILE_SIZE 8*3

#define DRAW_TICK SDL_USEREVENT+1

#define PAC_TICK SDL_USEREVENT+2

#define BLINKY_TICK SDL_USEREVENT+3

#define INKY_TICK SDL_USEREVENT+4

#define CLYDE_TICK SDL_USEREVENT+5

#define MODE_TICK SDL_USEREVENT+6

typedef struct {
    Uint32 event_type;
    Uint32 nexttick;
}ActorTimer;

void Drawfield(SDL_Surface* img, SDL_Surface* screen, State* game_state)
{
     SDL_Rect src = {0,0,TILE_SIZE,TILE_SIZE};

    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLUMNS;j++)
        {

            switch(game_state->field->table[i][j])
            {
              case EMPTY:
              src.x=0*TILE_SIZE;
              src.y=4*TILE_SIZE;
              break;

              case UPWALL:
              src.x=26*TILE_SIZE;
              src.y=4*TILE_SIZE;
              break;
              case DOWNWALL:
              src.x=28*TILE_SIZE;
              src.y=4*TILE_SIZE;
              break;
               case LEFTWALL:
              src.x=19*TILE_SIZE;
              src.y=4*TILE_SIZE;
              break;
               case RIGHTWALL:
              src.x=18*TILE_SIZE;
              src.y=4*TILE_SIZE;
              break;
               case ULCORNER:
              src.x=17*TILE_SIZE;
              src.y=4*TILE_SIZE;
              break;
               case URCORNER:
              src.x=16*TILE_SIZE;
              src.y=4*TILE_SIZE;
              break;
               case DLCORNER:
              src.x=21*TILE_SIZE;
              src.y=4*TILE_SIZE;
              break;
               case DRCORNER:
              src.x=20*TILE_SIZE;
              src.y=4*TILE_SIZE;
              break;

               case ULT:
              src.x=25*TILE_SIZE;
              src.y=4*TILE_SIZE;
              break;
               case URT:
              src.x=24*TILE_SIZE;
              src.y=4*TILE_SIZE;
              break;
               case DLT:
              src.x=23*TILE_SIZE;
              src.y=4*TILE_SIZE;
              break;
               case DRT:
              src.x=22*TILE_SIZE;
              src.y=4*TILE_SIZE;
              break;
                case UULT:
              src.x=27*TILE_SIZE;
              src.y=5*TILE_SIZE;
              break;
                case UURT:
              src.x=26*TILE_SIZE;
              src.y=5*TILE_SIZE;
              break;

              case SUPWALL:
              src.x=30*TILE_SIZE;
              src.y=4*TILE_SIZE;
              break;
              case SDOWNWALL:
              src.x=20*TILE_SIZE;
              src.y=3*TILE_SIZE;
              break;
               case SLEFTWALL:
              src.x=25*TILE_SIZE;
              src.y=3*TILE_SIZE;
              break;
               case SRIGHTWALL:
              src.x=24*TILE_SIZE;
              src.y=3*TILE_SIZE;
              break;
               case SULCORNER:
              src.x=23*TILE_SIZE;
              src.y=3*TILE_SIZE;
              break;
               case SURCORNER:
              src.x=22*TILE_SIZE;
              src.y=3*TILE_SIZE;
              break;
               case SDLCORNER:
              src.x=27*TILE_SIZE;
              src.y=3*TILE_SIZE;
              break;
              case SDRCORNER:
              src.x=26*TILE_SIZE;
              src.y=3*TILE_SIZE;
              break;

              case GHULCORNER:
              src.x=29*TILE_SIZE;
              src.y=3*TILE_SIZE;
              break;
              case GHURCORNER:
              src.x=28*TILE_SIZE;
              src.y=3*TILE_SIZE;
              break;
              case GHDLCORNER:
              src.x=31*TILE_SIZE;
              src.y=3*TILE_SIZE;
              break;
              case GHDRCORNER:
              src.x=30*TILE_SIZE;
              src.y=3*TILE_SIZE;
              break;
              case GHDOOR:
              src.x=15*TILE_SIZE;
              src.y=5*TILE_SIZE;
              break;
              case GHBDOOR:
              src.x=17*TILE_SIZE;
              src.y=5*TILE_SIZE;
              break;
              case GHADOOR:
              src.x=16*TILE_SIZE;
              src.y=5*TILE_SIZE;
              break;

              case POINT:
              src.x=16*TILE_SIZE;
              src.y=0*TILE_SIZE;
              break;
              case ENERGISER:
              src.x=20*TILE_SIZE;
              src.y=0*TILE_SIZE;
              break;

              default:
              src.x=0*TILE_SIZE;
              src.y=0*TILE_SIZE;
              break;

            }
            SDL_Rect dest={j*TILE_SIZE,i*TILE_SIZE,0,0};
            SDL_BlitSurface(img, &src, screen, &dest);
        }
    }

}

void Drawghost(SDL_Surface* image,SDL_Surface* screen,Ghost* ghost, int startx, int starty)
{
    SDL_Rect src = {0,0,TILE_SIZE*2,TILE_SIZE*2};
    switch(ghost->d)
     {
        case Standing:
        case Down:
        src.x=(startx+4)*TILE_SIZE;
        src.y=starty*TILE_SIZE;
        break;
        case Right:
        src.x=(startx)*TILE_SIZE;
        src.y=starty*TILE_SIZE;
        break;
        case Up:
        src.x=(startx+12)*TILE_SIZE;
        src.y=starty*TILE_SIZE;
        break;
        case Left:
        src.x=(startx+8)*TILE_SIZE;
        src.y=starty*TILE_SIZE;
        break;
     }
     SDL_Rect dest={0,0,0,0};
     dest.y=ghost->windowy*3;
     dest.x=ghost->windowx*3;

     SDL_BlitSurface(image, &src, screen, &dest);
}

void Drawactors(SDL_Surface* image,SDL_Surface* screen,State* game_state)
{
     Drawghost(image,screen,game_state->Blinky,0,12);
     Drawghost(image,screen,game_state->Pinky,0,16);
     Drawghost(image,screen,game_state->Inky,16,16);
     Drawghost(image,screen,game_state->Clyde,0,18);

     //DRAWPACMAN
     SDL_Rect src = {0,0,TILE_SIZE*2,TILE_SIZE*2};
     switch(game_state->pacman->frame)
     {
        case FULL:
        src.x=0;
        src.y=14*TILE_SIZE;
        break;
        case LBIG:
         src.x=0;
        src.y=6*TILE_SIZE;
        break;
        case UBIG:
        src.x=2*TILE_SIZE;
        src.y=6*TILE_SIZE;
        break;
        case RBIG:
        src.x=8*TILE_SIZE;
        src.y=6*TILE_SIZE;
        break;
        case DBIG:
        src.x=10*TILE_SIZE;
        src.y=6*TILE_SIZE;
        break;
        case LSSMALL:
        case LSMALL:
        src.x=4*TILE_SIZE;
        src.y=6*TILE_SIZE;
        break;
        case USSMALL:
        case USMALL:
        src.x=6*TILE_SIZE;
        src.y=6*TILE_SIZE;
        break;
        case RSSMALL:
        case RSMALL:
        src.x=12*TILE_SIZE;
        src.y=6*TILE_SIZE;
        break;
        case DSSMALL:
        case DSMALL:
        src.x=14*TILE_SIZE;
        src.y=6*TILE_SIZE;
        break;
     }
     int y=game_state->pacman->windowy*3;
     int x=game_state->pacman->windowx*3;
     SDL_Rect dest={x,y,0,0};
     SDL_BlitSurface(image, &src, screen, &dest);


}

void Draw(SDL_Surface* screen, State* game_state,SDL_Surface* image)
{


    Drawfield(image,screen, game_state);
    Drawactors(image, screen, game_state);
    SDL_Flip(screen);
}

Uint32 Actor_tick (Uint32 ms, void* param)
{
    ActorTimer* timer=(ActorTimer*) param;
    SDL_Event ev;
    ev.type = timer->event_type;
    SDL_PushEvent(&ev);
    //printf("%d\n",timer->nexttick);
    //printf("%d\n",*(int*) param);
    return timer->nexttick;   /* ujabb varakozas */
}

Uint32 Draw_tick (Uint32 ms, void* param)
{
    SDL_Event ev;
    ev.type = DRAW_TICK;
    SDL_PushEvent(&ev);
    return ms;   /* ujabb varakozas */
}

Uint32 Mode_tick(Uint32 ms, void* param)
{
    SDL_Event ev;
    ev.type = MODE_TICK;
    SDL_PushEvent(&ev);
    return 0;
}


Result Init_window()
{
    SDL_Surface *screen;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    screen = SDL_SetVideoMode(224*3, 288*3, 0, SDL_ANYFORMAT);
    if (!screen) {
        fprintf(stderr, "Window coudn't be opened\n");
        exit(1);
    }
    SDL_WM_SetCaption("original pacman", "pacman");
    SDL_Surface* image=IMG_Load("../images/pac.png");
    if (!image) {
        fprintf(stderr, "Couldn't load image");
        exit(1);
    }
    State* game_state;
    Init_game(&game_state);

    Draw(screen,game_state,image);
    SDL_Event ev;
    ActorTimer Pac_timer={PAC_TICK,33};
    ActorTimer Blinky_timer={BLINKY_TICK,Pac_timer.nexttick*80/75};
    SDL_TimerID pact = SDL_AddTimer(33, Actor_tick, &Pac_timer);
    SDL_TimerID blinky_t = SDL_AddTimer(Blinky_timer.nexttick, Actor_tick, &Blinky_timer);
    SDL_TimerID drawt = SDL_AddTimer(16.5, Draw_tick, NULL);

    int delay=game_state->ls[game_state->levelid].modes[game_state->modeid].delay;
    SDL_TimerID mode_timer=SDL_AddTimer(delay,Mode_tick,NULL);
     while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
        switch(ev.type)
        {
            case PAC_TICK:
                ;int hasEaten=Step_pacman(game_state);
                if(hasEaten==1)
                    Pac_timer.nexttick=16.5+33;
                else if(hasEaten==2)
                    Pac_timer.nexttick=4*16.5+33;
                else
                    Pac_timer.nexttick=33;
            break;
            case BLINKY_TICK:
                ;int nexttime=Step_Ghost(game_state,game_state->Blinky);
                Blinky_timer.nexttick=33*80/nexttime;
            break;
            case DRAW_TICK:
                Draw(screen,game_state,image);
            break;
            case MODE_TICK:
                delay=Change_mode(game_state);
                if(delay!=-1)
                    mode_timer=SDL_AddTimer(delay,Mode_tick,NULL);
            break;
            case SDL_KEYDOWN:
                switch(ev.key.keysym.sym)
                {
                    case SDLK_LEFT:
                    Move_pacman(game_state,Left);
                    break;
                    case SDLK_RIGHT:
                    Move_pacman(game_state,Right);
                    break;
                    case SDLK_UP:
                    Move_pacman(game_state,Up);
                    break;
                    case SDLK_DOWN:
                    Move_pacman(game_state,Down);
                    break;
                }
            break;
        }
    }
    Close_game(&game_state);
    SDL_RemoveTimer(pact);
    SDL_RemoveTimer(drawt);
     SDL_FreeSurface(image);
    SDL_Quit();
    return SUCCESFULL;
}

int Close_window();
