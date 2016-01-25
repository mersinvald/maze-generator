#ifndef TYPES_H
#define TYPES_H
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

struct cods_s{
    uint16_t x;
    uint16_t y;
};

typedef struct cods_s Cell_t;

typedef enum CellTypes { CELL, GENCELL, GENVISITED, RENDERED, WALL, WAY, CURRENT, LAST, SEEKED, EXIT } CellType_t;
typedef enum Actions   { NOTHING, GENERATE, SOLVE, ALL, STOP, OUTPUT } Action_t;

typedef int8_t*  MazeString_t;
typedef int8_t** MazeMatrix_t;

typedef struct CellString_s {
    Cell_t   *cells;
    uint32_t  size;
} CellString_t;

typedef struct Node_s {
    Cell_t cell;
    struct Node_s *next;
} Node_t;

typedef struct Stack_s {
    Node_t*  top;
    uint32_t size;
} Stack_t;

typedef struct mazeData_s {
    uint16_t    width;
    uint16_t    height;
    uint32_t    unvisitedNum;
    MazeMatrix_t  maze;
    Stack_t    *stack;
    Cell_t      startPoint;
    Cell_t      exitPoint;
    Cell_t      cellNext;
    bool        error;
} Data_t;

typedef struct Vertex_s {
    GLfloat x,y;
} Vertex_t;

typedef struct VertexColor_s {
    GLubyte r,g,b;
} VertexColor_t;

typedef struct RenderData {
    uint16_t       width;
    uint16_t       height;
    //opengl data
    GLfloat        x;
    GLfloat        y;
    GLfloat        pSize;
    Vertex_t      *vertices;
    VertexColor_t *verticesColor;
    uint32_t       vertices_count;

} RenderData_t;

typedef struct Parms_s {
        uint16_t width;
        uint16_t height;
        uint16_t windowW;
        uint16_t windowH;
        uint16_t animationDelay;
        uint8_t  framesDrop;
        bool     fullscreen;
        Cell_t   startPoint;
        Cell_t   exitPoint;
} Parms_t;

#endif // TYPES_H

