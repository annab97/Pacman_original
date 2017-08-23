#include "window.h"

#define TILE_SIZE 8*3

#define DRAW_TICK SDL_USEREVENT+1

#define PAC_TICK SDL_USEREVENT+2

#define BLINKY_TICK SDL_USEREVENT+3

#define INKY_TICK SDL_USEREVENT+4

#define CLYDE_TICK SDL_USEREVENT+5

#define MODE_TICK SDL_USEREVENT+6

#define FRIGHT_END SDL_USEREVENT+7

#define FLASH_START SDL_USEREVENT+8

#define DRAW_FREQUENCY 16.5

#define FAST_FLASH_FREQUENCY 8

#define FLASH_FREQUENCY 10

#define PAC_SPEED 33

typedef struct {
    Uint32 event_type;
    Uint32 nexttick;
}ActorTimer;

void Drawfield(SDL_Surface* img, SDL_Surface* screen, State* game_state,int counter)
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
              if(counter%(FAST_FLASH_FREQUENCY*2)<FAST_FLASH_FREQUENCY)
              {
                src.x=20*TILE_SIZE;
                src.y=0*TILE_SIZE;
              }
              else{
                src.x=0*TILE_SIZE;
              src.y=4*TILE_SIZE;
              }
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

void Drawghost(SDL_Surface* image,SDL_Surface* screen,Ghost* ghost, int startx, int starty,ModeName mn, int counter)
{
    SDL_Rect src = {0,0,TILE_SIZE*2,TILE_SIZE*2};

    if(ghost->status==GS_FLASHING && counter%(FLASH_FREQUENCY*2)<FLASH_FREQUENCY)
    {
        src.y=8*TILE_SIZE;
     src.x=12*TILE_SIZE;
    }
    else if(ghost->status==GS_FRIGHTENING || ghost->status==GS_FLASHING)
    {
     src.y=8*TILE_SIZE;
     src.x=16*TILE_SIZE;
    }else
    {
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
     }
     if((ghost->windowx+ghost->windowy)%4==0)
     {
        src.x+=2*TILE_SIZE;
     }
     SDL_Rect dest={0,0,0,0};
     dest.y=ghost->windowy*3;
     dest.x=ghost->windowx*3;

     SDL_BlitSurface(image, &src, screen, &dest);
}

void Drawactors(SDL_Surface* image,SDL_Surface* screen,State* game_state,int counter)
{
     ModeName current=game_state->currentState;
     Drawghost(image,screen,game_state->Blinky,0,12,current,counter);
     Drawghost(image,screen,game_state->Pinky,0,16,current, counter);
     Drawghost(image,screen,game_state->Inky,16,16,current, counter);
     Drawghost(image,screen,game_state->Clyde,0,18,current, counter);

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

void Drawlives(SDL_Surface* image, SDL_Surface* screen, int lives)
{
    SDL_Rect src = {0,6*TILE_SIZE,TILE_SIZE*2,TILE_SIZE*2};
    for(int i=0;i<lives;i++)
    {
      SDL_Rect dest={(i+1)*TILE_SIZE*2,34*TILE_SIZE,0,0};
      SDL_BlitSurface(image, &src, screen, &dest);
    }
}


void Drawlevels(SDL_Surface* image, SDL_Surface* screen, State* game_state)
{
    int start=game_state->levelid>7?game_state->levelid-6:0;
    for(int i=0; i+start<=game_state->levelid;i++)
    {
        SDL_Rect src = {0,0,TILE_SIZE*2,TILE_SIZE*2};
        src.x=2*game_state->ls[i].symbol*TILE_SIZE;
        src.y=10*TILE_SIZE;
        SDL_Rect dest={(12-i)*TILE_SIZE*2,34*TILE_SIZE,0,0};
        SDL_BlitSurface(image, &src, screen, &dest);
    }
}

void DrawT(SDL_Surface* image, SDL_Surface* screen, char* text, int lastchar, int row, int flashing, int counter)
{
    int length=0;
    for(;text!=NULL && text[length]!='\0';length++);
    if(!flashing || counter%(FAST_FLASH_FREQUENCY*2)<FAST_FLASH_FREQUENCY)
    {
        for(int i=0;i<=length;i++)
        {
            SDL_Rect src = {0,0,TILE_SIZE,TILE_SIZE};
            if(text[length-i]==' ')
            {
                src.x=0*TILE_SIZE;
                src.y=4*TILE_SIZE;
            }
            else if(text[length-i]<='9')
            {
                src.y=0;
                src.x=(text[length-i]-'0')*TILE_SIZE;
            }else
            {
                src.y=2*TILE_SIZE;
                src.x=(text[length-i]-'A'+1)*TILE_SIZE;
            }
            SDL_Rect dest={(lastchar-i)*TILE_SIZE,row*TILE_SIZE,0,0};
            SDL_BlitSurface(image,&src,screen,&dest);
        }
    }
}

void DrawTexts(SDL_Surface* image, SDL_Surface* screen, int counter, int score)
{
    char* level="1UP";
    char* highscore="HIGH SCORE";
    char sscore [8];

    sprintf(sscore,"%02d",score);

    DrawT(image,screen, level,6,0,1, counter);
    DrawT(image,screen, highscore,19,0,0,0);
    DrawT(image, screen, sscore,7,1,0,0);

}

void Draw(SDL_Surface* screen, State* game_state,SDL_Surface* image)
{
    static int counter=0;
    Drawfield(image,screen, game_state,counter);
    Drawactors(image, screen, game_state, counter);
    Drawlives(image,screen,game_state->lives);
    Drawlevels(image,screen,game_state);
    DrawTexts(image, screen, counter,game_state->score);
    SDL_Flip(screen);
    counter++;
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

Uint32 Unique_event(Uint32 ms, void* param)
{

    SDL_Event* ev=(SDL_Event*) param;
    SDL_PushEvent(ev);
    return 0;
}

/*Uint32 Mode_tick(Uint32 ms, void* param)
{
    SDL_Event ev;
    ev.type = MODE_TICK;
    SDL_PushEvent(&ev);
    printf("barack\n");
    return 0;
}

Uint32 Fright_timer(Uint32 ms, void* param)
{
    SDL_Event ev;
    ev.type = FLASH_START;
    SDL_PushEvent(&ev);

    return 0;
}*/

Uint32 Test_tick(Uint32 ms, void* param)
{
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

    //////////////////////////SET_UP TIMERS
    int before_frightening=-1;
    SDL_TimerID frightening_timer;
    int starttime=SDL_GetTicks();
    int modeev=MODE_TICK;
    int frightev=FRIGHT_END;
    int flashev=FLASH_START;

    SDL_Event ev;
    ActorTimer Pac_timer={PAC_TICK,PAC_SPEED};
    ActorTimer Blinky_timer={BLINKY_TICK,Pac_timer.nexttick*80/75};
    SDL_TimerID pact = SDL_AddTimer(PAC_SPEED, Actor_tick, &Pac_timer);
    SDL_TimerID blinky_t = SDL_AddTimer(Blinky_timer.nexttick, Actor_tick, &Blinky_timer);
    SDL_TimerID drawt = SDL_AddTimer(DRAW_FREQUENCY, Draw_tick, NULL);

    int mode_delay=game_state->ls[game_state->levelid].modes[game_state->modeid].delay;
    SDL_TimerID mode_timer=SDL_AddTimer(mode_delay,Unique_event,&modeev);

    //////////////////////EVENT_LOOP
     while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
        switch(ev.type)
        {
            case PAC_TICK:
                ;int hasEaten=Step_pacman(game_state);
                if(hasEaten==1)
                {
                    Pac_timer.nexttick=DRAW_FREQUENCY+PAC_SPEED;
                }
                else if(hasEaten==2)
                {
                    SDL_RemoveTimer(mode_timer);
                    SDL_RemoveTimer(frightening_timer);
                    Pac_timer.nexttick=4*DRAW_FREQUENCY+PAC_SPEED;
                    int frigmode_delay=Start_frightening(game_state);
                    if(before_frightening==-1)
                        before_frightening=SDL_GetTicks()-starttime;
                    int delay=frigmode_delay-2*FLASH_FREQUENCY*DRAW_FREQUENCY*game_state->ls[game_state->levelid].fright_flashes;
                    frightening_timer=SDL_AddTimer(delay,Unique_event,&flashev);
                    if(frightening_timer==NULL) printf("ures\n"); else printf("successful\n");

                    mode_timer=NULL;
                }
                else
                {
                    Pac_timer.nexttick=PAC_SPEED;
                }
            break;
            case BLINKY_TICK:
                ;int nexttime=Step_Ghost(game_state,game_state->Blinky);
                Blinky_timer.nexttick=PAC_SPEED*80/nexttime;
            break;
            case DRAW_TICK:
                Draw(screen,game_state,image);
            break;
            case MODE_TICK:

                SDL_RemoveTimer(mode_timer);
                mode_delay=Change_mode(game_state);
                starttime=SDL_GetTicks();
                if(mode_delay!=-1)
                    mode_timer=SDL_AddTimer(mode_delay,Unique_event,&modeev);
            break;
            case FLASH_START:
            Flash_ghosts(game_state);
            int flashtime=2*FLASH_FREQUENCY*DRAW_FREQUENCY*game_state->ls[game_state->levelid].fright_flashes;
            frightening_timer=SDL_AddTimer(flashtime,Unique_event,&frightev);
            break;
            case FRIGHT_END:
                End_frightening(game_state);
                starttime=SDL_GetTicks()-before_frightening;
                SDL_RemoveTimer(frightening_timer);
                if(mode_delay!=-1 && mode_timer==NULL)
                {
                    Uint32 delay=mode_delay-before_frightening/10*10;
                    mode_timer=SDL_AddTimer(delay,Unique_event,&modeev);
                    if(mode_timer==NULL)
                        printf("error\n");
                    printf("modetimer: %u\n",delay);
                }



                before_frightening=-1;
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
     SDL_RemoveTimer(blinky_t);
     SDL_RemoveTimer(mode_timer);
     SDL_RemoveTimer(frightening_timer);
     SDL_FreeSurface(image);
    SDL_Quit();
    return SUCCESFULL;
}

int Close_window();
