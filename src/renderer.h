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
int SetViewport(int width, int height);
void renderMatrix(mazeMatrix maze, renderData rd, int mode);
void drawSolveMatrix(mazeMatrix maze, renderData rd);
void drawGenerateMatrix(mazeMatrix maze, renderData rd);
int handleTextInput(SDL_Event e);
#endif // RENDERER_H
