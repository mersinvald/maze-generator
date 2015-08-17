#include <funcs.h>

void printBitmap(mazeMatrix maze, int w, int h){
    int i, j;

    printf("\n");
    for(i = 0; i < h; i++){
        printf("\n");
        for(j = 0; j < w; j++){
                /*if(maze[i][j] != WALL)
                    printf("\033[34m%s\033[0m ", "1" \u25A0");
                else
                    printf("\033[31m%s\033[0m ", "0" "\u00A0");*/
                printf("%s ", (maze[i][j] == WALL) ? "\u25A0" : "\u00A0");
        }
    }
    printf("\n");
}

void printVertices(vertex* array, int count){
    int i, j;

    printf("\n");

    for(j = 0; j < count; j++){
                /*if(maze[i][j] != WALL)
                    printf("\033[34m%s\033[0m ", "1" \u25A0");
                else
                    printf("\033[31m%s\033[0m ", "0" "\u00A0");*/
                printf("%f %f\n", array[j].x, array[j].y);
                if(j % 4 == 0) printf("\n");
    }
    printf("\n");
}
