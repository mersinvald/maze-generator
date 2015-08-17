#ifndef TYPES_H
#define TYPES_H
#include <SDL2/SDL_opengl.h>
#include <stdio.h>

struct cods{
    unsigned int x;
    unsigned int y;
};

typedef struct cods cell;

enum mazeCell {CELL = 0, GENCELL, GENVISITED, RENDERED, WALL, WAY, CURRENT, LAST, SEEKED, EXIT};

typedef int*               mazeString;
typedef int**              mazeMatrix;

struct cellString{
    cell* cells;
    unsigned int size;
};
typedef struct cellString cellString;

struct Stack{
    cell c;
    struct Stack *next;
};
typedef struct Stack stack;

struct mazeData{
    unsigned int width;
    unsigned int height;
    unsigned int unvisitedNum;
    mazeMatrix   maze;
    stack*       s;
    unsigned int stackSize;
    cell         startPoint;
    cell         exitPoint;
    cell         cellNext;
    int error;
};
typedef struct mazeData data;

struct vertex{
    GLfloat x,y;
};

struct vertexColor{
    GLubyte r,g,b;
};

typedef struct vertex vertex;
typedef struct vertexColor vertexColor;

struct renderData{
    unsigned int width;
    unsigned int height;
    //opengl data
    GLfloat x;
    GLfloat y;
    GLfloat pSize;
    vertex *vertices;
    vertexColor *verticesColor;
    int vertices_count;

};

typedef struct renderData renderData;

enum actions {NOTHING = 0, GENERATE, SOLVE, ALL, STOP, OUTPUT};

struct parms{
        int width;
        int height;
        int windowW;
        int windowH;
        int animationDelay;
        int framesDrop;
        int fullscreen;
        cell startPoint;
        cell exitPoint;
};
typedef struct parms parms;



#endif // TYPES_H

