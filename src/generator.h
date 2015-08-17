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


data generate           (data d);

data generateStep       (data d);

mazeMatrix init         (unsigned int width,
                         unsigned int height);

mazeMatrix finalize     (unsigned int width,
                         unsigned int heiggt,
                         mazeMatrix   maze);

mazeMatrix removeWall   (cell first,
                         cell second,
                         mazeMatrix maze);

cellString getCells     (unsigned int width,
                         unsigned int height,
                         mazeMatrix maze);

cellString getUnvisitedCells
                        (unsigned int width,
                         unsigned int height,
                         mazeMatrix maze);

unsigned int        unvisitedCount
                        (unsigned int width,
                         unsigned int height,
                         mazeMatrix maze);

//steps       addStep      (mazeMatrix *maze,
//                          unsigned int width,
//                          unsigned int height,
//                          cell cellCurrent,
//                          steps s);
#endif // GENERATOR_H

