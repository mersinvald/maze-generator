#include <stdio.h>
#include <generator.h>
#include <seeker.h>
#include <renderer.h>
#include <types.h>
#include <funcs.h>
#include <common.h>
#include <stack.h>


int main(int argc, char **argv)
{
    parms input;
    /*
    input.width = 800;
    input.height = 450;
    input.fullscreen = SDL_WINDOW_FULLSCREEN;
    input.windowH = 900;
    input.windowW = 1600;
    input.animationDelay = 0;
    input.framesDrop = 1000;
    input.startPoint.x = 1;
    input.startPoint.y = 1;
    input.exitPoint.x  = 797;
    input.exitPoint.y  = 447;*/

    parms last;
    int quit = 0;
    data d;
    renderData rd;

    srand((unsigned)clock());

    //инициализация SDL2
    SDL_Init(SDL_INIT_VIDEO);
    input = getInput(1, ALL, input);
    SDL_Window   *window   = SDL_CreateWindow("Labytinth", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, input.windowW, input.windowH, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | input.fullscreen | SDL_WINDOW_BORDERLESS);
    SDL_GLContext context  = SDL_GL_CreateContext(window);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_Event event;

    //OpenGL 4.1
    glMatrixMode(GL_PROJECTION|GL_MODELVIEW);
    glLoadIdentity();
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glOrtho(-input.windowW/2,input.windowW/2,input.windowH/2,-input.windowH/2,0,1);
    glClearColor( 1, 1, 1, 0 );
    SDL_GL_SetSwapInterval( 1 ); //vsync

    uint8_t *data;
    int flagChanged = 0;
    int flagAction = NOTHING;
    int flagGenerated = 0;
    int flagGeneratorData   = 0;
    int flagSolverData   = 0;
    int flagSolved = 0;
    int i = 0;


    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);

    while(!quit){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT)
                quit = 1;

            else if (event.type == SDL_KEYDOWN){
                    switch (event.key.keysym.sym){
                case  SDLK_g:      flagAction = GENERATE;      break;
                case  SDLK_s:      flagAction = SOLVE;         break;
                case  SDLK_TAB:    flagAction = STOP;          break;
                case  SDLK_o:      flagAction = OUTPUT;        break;
                case  SDLK_ESCAPE: quit = 1;                   break;
                case  SDLK_UP:     input.framesDrop++;         break;
                case  SDLK_RIGHT:  input.animationDelay++;
                case  SDLK_DOWN:   input.framesDrop = (input.framesDrop - 1 > 0) ? input.framesDrop - 1 : 1;
                                   break;
                case  SDLK_LEFT:   input.animationDelay = (input.animationDelay - 1 >= 0) ? input.animationDelay - 1 : 0;
                                   break;
                }
            }
        }
        if(flagAction == GENERATE){
            if(!flagGeneratorData){
                d = initGeneratorData(input.width, input.height, input.startPoint);
                rd = initRenderData(d, input.windowW, input.windowH);
                glVertexPointer(2, GL_FLOAT, sizeof(vertex), rd.vertices);
                glColorPointer(3, GL_UNSIGNED_BYTE, sizeof(vertexColor), rd.verticesColor);
                flagGeneratorData = 1;
                flagGenerated = 0;
                flagSolved = 0;
                flagSolverData = 0;
            }
            for(i = 0; i < input.framesDrop; i++){
                if(d.unvisitedNum != 0){
                    d = generateStep(d);
                    flagAction = NOTHING; //пошаговое выполнение
                }
                else{
                    flagGeneratorData = 0;
                    flagGenerated = 1;
                    flagAction = NOTHING;
                    break;
                }
            }
            d.maze[d.startPoint.y][d.startPoint.x] = CURRENT;
            renderMatrix(d.maze, rd, GENERATE);
            d.maze[d.startPoint.y][d.startPoint.x] = GENVISITED;
            flagChanged = 1;
        }
        else if(flagAction == SOLVE && flagGenerated){
            if(!flagSolverData){
                d = initSeekerData(d, input.startPoint, input.exitPoint);
                rd = clearSeekerColorArray(d.maze, rd);
                flagSolverData = 1;
            }
            for(i = 0; i < input.framesDrop; i++){
                if((d.startPoint.x != d.exitPoint.x || d.startPoint.y != d.exitPoint.y) && d.error != 1){
                    d = seekStep(d);
                }
                else if(d.error){
                    printf("ERROR: Lanyrinth cannot be solved! :C\n");
                }
                else{
                    flagSolved = 1;
                    flagSolverData = 0;
                    flagAction = NOTHING;
                    d.maze = setMode(d.exitPoint, d.maze, WAY);
                    break;
                }
            }
            setMode(d.startPoint, d.maze, CURRENT);
            renderMatrix(d.maze, rd, SOLVE);
            setMode(d.startPoint, d.maze, WAY);
            flagChanged = 1;
        }
        else if(flagAction == STOP){
            last = input;
            input = getInput(0, GENERATE, last);
            if((last.width != input.width) || (last.height != input.height)){
                //d = initGeneratorData(input.width, input.height, input.startPoint);
                //rd = initRenderData(d, input.windowW, input.windowH);
                //glVertexPointer(2, GL_FLOAT, sizeof(vertex), rd.vertices);
                //glColorPointer(3, GL_UNSIGNED_BYTE, sizeof(vertexColor), rd.verticesColor);
                flagGenerated = 0;
                flagGeneratorData = 0;
                flagSolverData = 0;
                flagSolved = 0;
            }
            flagAction = NOTHING;
            flagChanged = 1;
        }
        else if(flagAction == OUTPUT){
            data = malloc(input.windowW * input.windowH * 4 * sizeof(uint8_t));
            glReadBuffer(GL_FRONT);
            glReadPixels(0, 0, input.windowW , input.windowH,  GL_RGBA, GL_UNSIGNED_BYTE, data);
            save_png_libpng("./labyrinth.png", data, input.windowW, input.windowH);
            flagAction = NOTHING;

        }
        if(flagAction != NOTHING || flagChanged){
            SDL_Delay(input.animationDelay);
            SDL_GL_SwapWindow(window);
            flagChanged = 0;
        }
    }

    //cleanup
    wipe(&d.s, &d.stackSize);
    return 0;
}
