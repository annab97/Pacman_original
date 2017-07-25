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
    fclose(fp);
}

void Copy(Mode* from, Mode* to)
{
    for(int i=0;i<8;i++)
    {
        to[i]=from[i];
    }
}

void print_Levelstate()
{
    FILE *fp;
    fp = fopen("levelStates.dat", "wb");
    if(fp==NULL)
    {
        perror("Error: Failed to load field.dat");
        return FAILED;
    }
    fclose(fp);
    fp = fopen("levelStates.dat", "wb");
    FILE *f;
    f = fopen("levelstates.txt", "rt");
    if(f==NULL)
    {
        perror("Error: Failed to load field.dat");
        return FAILED;
    }
    FILE *fmodes;
    fmodes = fopen("modes.txt", "rt");
    if(f==NULL)
    {
        perror("Error: Failed to load field.dat");
        return FAILED;
    }
    char* names[]={"Cherries","Strawberry","Peach","Apple","Grapes","Galaxian","Bell","Key"};

    LevelState stages[21];
    fscanf(f,"%*[^\n]\n",NULL);
    for(int i=0;i<21;i++)
    {
        LevelState ls;
        fscanf(f,"%d",&ls.id);
        char sym[20];
        fscanf(f,"%s",sym);
        Symbol s;
        for(int j=0;j<8;j++)
        {
            if(strcmp(names[j],sym)==0)
            {
                s=i;
            }
        }
        ls.symbol=s;
        fscanf(f,"%d",&ls.symbolBonus);
        fscanf(f,"%d",&ls.pac_speed);
        fscanf(f,"%d",&ls.ghost_speed);
        fscanf(f,"%d",&ls.ghost_tunnelspeed);
        fscanf(f,"%d",&ls.elroy_1_dots);
        fscanf(f,"%d",&ls.elroy_1_speed);
        fscanf(f,"%d",&ls.elroy_2_dots);
        fscanf(f,"%d",&ls.elroy_2_speed);
        fscanf(f,"%d",&ls.fright_pac);
        fscanf(f,"%d",&ls.fright_ghost);
        fscanf(f,"%d",&ls.fright_time);
        fscanf(f,"%d",&ls.fright_flashes);
        stages[i]=ls;
    }
    int untils[3];
    char* modenames[]= {"Scatter","Chase","Frightening"};
    fscanf(fmodes,"%*s",NULL);
    Mode modes[3][8];
    for(int i=0;i<3;i++)
    {
        fscanf(fmodes,"%d",&untils[i]);
    }
    for(int i=0;i<8;i++)
    {
        ModeName mn;
        char modename[10];
        fscanf(fmodes,"%s",modename);
        for(int j=0;j<3;j++)
        {
            if(strcmp(modename,modenames[j])==0)
                mn=j;
        }
        for(int j=0;j<3;j++)
        {
            double time;
            fscanf(fmodes,"%lf",&time);
            Mode m; m.name=mn; m.delay=time;
            modes[j][i]=m;
        }
    }
    int uindex=0;
    for(int i=0;i<21;)
    {
        while(i<untils[uindex]-1)
        {
            Copy(modes[uindex],stages[i].modes);
            i++;
        }
        uindex++;
    }


    fwrite(stages,sizeof(LevelState),21,fp);
    fclose(fmodes);
    fclose(f);
    fclose(fp);
}

int main()
{
    //print_Levelstate();
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
