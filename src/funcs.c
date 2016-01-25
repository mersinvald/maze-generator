#include <funcs.h>

void printBitmap(MazeMatrix_t maze, uint16_t w, uint16_t h){
    printf("\n");
    for(uint16_t i = 0; i < h; i++){
        printf("\n");
        for(uint16_t j = 0; j < w; j++){
                /*if(maze[i][j] != WALL)
                    printf("\033[34m%s\033[0m ", "1" \u25A0");
                else
                    printf("\033[31m%s\033[0m ", "0" "\u00A0");*/
                printf("%s ", (maze[i][j] == WALL) ? "\u25A0" : "\u00A0");
        }
    }
    printf("\n");
}

void printVertices(Vertex_t* array, uint16_t count){
    printf("\n");
    for(uint16_t i = 0; i < count; i++){
                /*if(maze[i][j] != WALL)
                    printf("\033[34m%s\033[0m ", "1" \u25A0");
                else
                    printf("\033[31m%s\033[0m ", "0" "\u00A0");*/
                printf("%f %f\n", array[i].x, array[i].y);
                if(i % 4 == 0) printf("\n");
    }
    printf("\n");
}
