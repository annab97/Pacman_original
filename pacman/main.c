//#include <SDL.h>
//#include <SDL_gfxPrimitives.h>

#include "field.h"
#include <stdio.h>

void print_maze()
{
    FILE *fp;
    fp = fopen("field.dat", "wb");
    if(fp==NULL)
    {
        perror("Error: Failed to load field.dat");
        return FAILED;
    }
    FILE *f;
    f = fopen("field.txt", "rt");
    if(f==NULL)
    {
        perror("Error: Failed to load field.dat");
        return FAILED;
    }
    Maze m;
    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLUMNS;j++)
        {
            int tile;
            fscanf(f,"%d",&tile);
            m.table[i][j]=tile;
        }
    }
    fwrite(&m,sizeof(Maze),1,fp);
}

int main()
{
    //print_maze();
    Init_window();
     /*SDL_Event ev;
    SDL_Surface *screen;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    screen = SDL_SetVideoMode(440, 360, 0, SDL_ANYFORMAT);
    if (!screen) {
        fprintf(stderr, "Window coudn't be opened\n");
        exit(1);
    }
    SDL_WM_SetCaption("original pacman", "pacman");



    int r = 50;
    int x = 100;
    int y = 100;
    filledCircleRGBA(screen, x, y, r, 255, 0, 0, 255);

    SDL_Flip(screen);
     while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {
    }

    SDL_Quit();*/

    return 0;
}
