#ifndef COMMON_H
#define COMMON_H
#include <generator.h>
#include <SDL2/SDL.h>
#include <types.h>
#include <libpng16/png.h>

Data_t initGeneratorData(uint16_t width, uint16_t height, Cell_t startPoint);

Data_t initSeekerData(Data_t d, Cell_t startPoint, Cell_t exitPoint);

RenderData_t initRenderData(Data_t d, uint16_t windowW, uint16_t windowH);

RenderData_t clearSeekerColorArray(MazeMatrix_t maze, RenderData_t rd);

Parms_t      getInput(bool first, Action_t mode, Parms_t p);

//generator and seeker common functions
void         setMode (Cell_t cell, MazeMatrix_t maze, CellType_t type);

CellString_t getNeighbours(Data_t *data, Cell_t cell, int8_t distance);

uint32_t     randomRange (uint32_t low, uint32_t high);

//save to png
bool save_png_libpng(const char *filename, uint8_t *pixels, uint16_t w, uint16_t h);

#endif // COMMON_H

