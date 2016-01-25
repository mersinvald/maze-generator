#ifndef GENERATOR_H
#define GENERATOR_H
#include <types.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <funcs.h>
#include <common.h>
#include <stack.h>


bool generate             (Data_t* d);

bool generateStep         (Data_t* d);

MazeMatrix_t init         (uint16_t width, uint16_t height);

MazeMatrix_t finalize     (uint16_t width, uint16_t height, MazeMatrix_t maze);

uint32_t unvisitedCount(uint16_t width, uint16_t height, MazeMatrix_t maze);

#endif // GENERATOR_H

