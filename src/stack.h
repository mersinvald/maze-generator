#ifndef STACK_H
#define STACK_H
#include <stdlib.h>
#include <types.h>


void push(cell c, stack **s, unsigned int* sizeptr);
cell pop(stack **s, unsigned int* sizeptr);

void wipe(stack **s, unsigned int* sizeptr);
#endif // STACK_H


