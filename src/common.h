#ifndef COMMON_H
#define COMMON_H
#include <generator.h>
#include <SDL2/SDL.h>
#include <types.h>
#include <libpng16/png.h>

data initGeneratorData(int width, int height, cell startPoint);
data initSeekerData(data d,cell startPoint, cell exitPoint);
renderData initRenderData(data d, int windowW, int windowH);
renderData clearSeekerColorArray(mazeMatrix maze, renderData rd);
parms getInput(int first, int mode, parms p);

//generator and seeker common functions
mazeMatrix setMode      (cell c,
                         mazeMatrix maze,
                         int type);

cellString getNeighbours(unsigned int width,
                         unsigned int height,
                         mazeMatrix maze,
                         cell       c,
                         int distance);

//cellString getCells     (unsigned int width,
//                         unsigned int height,
//                         mazeMatrix maze,
//                         int type);

unsigned int        randomRange
                        (unsigned int low,
                         unsigned int high);

//save to png
int save_png_libpng(const char *filename, uint8_t *pixels, int w, int h);

#endif // COMMON_H

