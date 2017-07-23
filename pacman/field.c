#include "field.h"
#include <stdio.h>


Result Read_table(Maze** maze)
{
    FILE *fp;
    fp = fopen("field.dat", "rb");
    if(fp==NULL)
    {
        perror("Error: Failed to load field.dat");
        return FAILED;
    }
    *maze=malloc(sizeof(Maze));
    fread(*maze,sizeof(Maze),1,fp);
    return SUCCESFULL;
}


Result Init_field(Maze** maze)
{
    return Read_table(maze);
}
