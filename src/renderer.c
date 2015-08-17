#include <renderer.h>


void renderMatrix(mazeMatrix maze, renderData rd, int mode){
    glClear(GL_COLOR_BUFFER_BIT);
    //printVertices(rd.vertices, rd.vertices_count);

    if(mode == GENERATE)   drawGenerateMatrix(maze, rd);
    else                   drawSolveMatrix(maze, rd);

    glDrawArrays(GL_QUADS,0, rd.vertices_count);
    //memset(cArray, 255, sizeof(vertexColor)*rd.width*rd.height*4); //очистка массива цветов точек
}

void drawGenerateMatrix(mazeMatrix maze, renderData rd){
    int i, j, c, col = 0;
    for(i = 0; i < rd.height; i++){
        for(j = 0; j < rd.width; j++){
            if(maze[i][j] != WALL && maze[i][j] /*!= GENCELL*/){
                for(c = 0; c<4; c++){
                    switch (maze[i][j]){
                        case CURRENT: rd.verticesColor[col].r = 0;
                                      rd.verticesColor[col].g = 255;
                                      rd.verticesColor[col].b = 0;
                                      break;
                        case GENVISITED:
                                      rd.verticesColor[col].r = 255; //randomRange(0, 255);//= 0;
                                      rd.verticesColor[col].g = 30; //randomRange(0, 255);//= 0;
                                      rd.verticesColor[col].b = 100; //randomRange(0, 255);//= 0;
                                      break;
                        case GENCELL:
                                                              rd.verticesColor[col].r = 255;
                                                              rd.verticesColor[col].g = 255;
                                                              rd.verticesColor[col].b = 255;
                                                              break;
                    }
                    col++;
                }
            }
            else col+=4;
        }
    }
}


void drawSolveMatrix(mazeMatrix maze, renderData rd){
    int i, j, c, col = 0;
    static int cr = 255;
    static int cg = 30;
    static int cb = 30;
    static int fr, fg, fb;
    if(fr != 1){
        if(cr < 255) cr++;
        else         fr = 1;
    }
    else{
        if(cr > 100) cr--;
        else         fr = 0;
    }
    for(i = 0; i < rd.height; i++){
        for(j = 0; j < rd.width; j++){
            if(maze[i][j] != WALL && maze[i][j] != GENCELL && maze[i][j] != GENVISITED){
                for(c = 0; c<4; c++){
                    switch (maze[i][j]){
                        case WAY:
                                      rd.verticesColor[col].r = cr;
                                      rd.verticesColor[col].g = cg;
                                      rd.verticesColor[col].b = cb;
                                      break;
                        case SEEKED:  rd.verticesColor[col].r = 255;
                                      rd.verticesColor[col].g = 255;
                                      rd.verticesColor[col].b = 255;
                                      break;
                        case CURRENT:
                                      rd.verticesColor[col].r = 0;
                                      rd.verticesColor[col].g = 255;
                                      rd.verticesColor[col].b = 0;
                                      //rd.verticesColor[col].r = 10;
                                      //rd.verticesColor[col].g = 255;
                                      //rd.verticesColor[col].b = 70;
                                      break;
                        case EXIT:    rd.verticesColor[col].r = 0;
                                      rd.verticesColor[col].g = 255;
                                      rd.verticesColor[col].b = 0;
                        default: break;
                    }
                    col++;
                }
            }
            else col+=4;
        }
    }
}
