#ifndef RENDERER_H
#define RENDERER_H
#include <stdio.h>
#include <stdlib.h>
#include <types.h>
#include <funcs.h>
#include <common.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_ttf.h>

void InitGL();

bool setViewport(uint16_t width, uint16_t height);

void renderMatrix(MazeMatrix_t maze, RenderData_t rd, Action_t mode);

#endif // RENDERER_H
