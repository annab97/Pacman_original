#include "pacdef.h"

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

int Distance(Position from, Position to)
{
    int x=from.x-to.x; int y=from.y-to.y;
    return x*x+y*y;
}
