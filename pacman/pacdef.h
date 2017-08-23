#ifndef PACDEF_H_INCLUDED
#define PACDEF_H_INCLUDED

#define ROWS 36
#define COLUMNS 28

typedef enum {
FAILED,SUCCESFULL
} Result;

typedef enum {
    Standing,Up, Left, Down, Right
} Direction;

typedef enum {
    BLINKY, PINKY, INKY, CLYDE
} GHOSTNAME;

typedef enum {
GS_NORMAL, GS_FRIGHTENING, GS_FLASHING, GS_EATEN
} GHOSTSTATUS;

typedef enum{
    CHERRIES, STRAWBERRY, PEACH, APPLE, GRAPES, GALAXIAN, BELL, KEY
}Symbol;

typedef enum{
    SCATTER, CHASE, FRIGHTENING
} ModeName;

typedef enum{
    EMPTY,POINT,ENERGISER,

    UPWALL, DOWNWALL, RIGHTWALL, LEFTWALL,
    ULCORNER, URCORNER, DLCORNER, DRCORNER,
    ULT, URT, DLT,DRT, UULT, UURT,

    SUPWALL, SDOWNWALL, SRIGHTWALL, SLEFTWALL,
    SULCORNER, SURCORNER, SDLCORNER, SDRCORNER,

    GHULCORNER, GHURCORNER, GHDLCORNER, GHDRCORNER, GHDOOR, GHBDOOR, GHADOOR
} Tile;

typedef enum {
    FULL,
    USMALL, LSMALL, DSMALL, RSMALL,
    UBIG, LBIG, DBIG, RBIG,
    USSMALL, LSSMALL, DSSMALL, RSSMALL,
    KILL1, KILL2, KILL3,  KILL4, KILL5, KILL6, KILL7, KILL8, KILL9, KILL10, KILL11
} PACFRAME;



typedef struct{
    int x, y;
} Position;

typedef struct{
    Tile table[ROWS][COLUMNS];
} Maze;

typedef struct{
    ModeName name;
    double delay;
}Mode;

typedef struct{
    int fromlevel;
    Mode modes[8];
}Mode_table;


typedef struct{
int id;
Mode modes[8];
Symbol symbol;
int symbolBonus;
int pac_speed;
int ghost_speed;
int ghost_tunnelspeed;
int elroy_1_dots;
int elroy_1_speed;
int elroy_2_dots;
int elroy_2_speed;
int fright_pac;
int fright_ghost;
int fright_time;
int fright_flashes;
}LevelState;

typedef struct {
    int x,y;
    int windowx, windowy;
    Direction next_step;
    PACFRAME frame;
    Direction d;
    Direction nextd;
} Pacman;

struct State;
typedef struct{
    GHOSTNAME name;
    int x,y;
    int windowx, windowy;
    Direction d;
    Position Target;
    Position home;
    GHOSTSTATUS status;
    void (*NextTarget) (struct State*);
} Ghost;

typedef struct State {
    Maze* field;
    Pacman* pacman;
    Ghost* Blinky;
    Ghost* Pinky;
    Ghost* Inky;
    Ghost* Clyde;
    LevelState* ls;
    int dotseaten;
    int modeid;
    int levelid;
    int levelnum;
    int score;
    int lives;
    ModeName currentState;
} State;

Position Nextmove(Position pos, Direction dir);

int Distance(Position from, Position to);

#endif // PACDEF_H_INCLUDED
