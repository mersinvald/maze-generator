#include <common.h>

//initialisation finctions
Data_t initGeneratorData(uint16_t width, uint16_t height, Cell_t startPoint){
    Data_t d;
    d.width        = width;
    d.height       = height;
    d.startPoint.x = startPoint.x;
    d.startPoint.y = startPoint.y;
    d.maze         = init(width, height);
    d.stack        = calloc(1, sizeof(Stack_t));
    d.stack->top   = NULL;
    d.stack->size  = 0;
    d.unvisitedNum = unvisitedCount(width, height, d.maze) - 1;
    d.error        = false;
    setMode(d.startPoint, d.maze, GENVISITED);
    return d;
}

Data_t initSeekerData(Data_t d, Cell_t startPoint, Cell_t exitPoint){
    wipe(d.stack);
    free(d.stack);
    d.maze         = finalize(d.width, d.height, d.maze);
    d.startPoint   = startPoint;
    d.exitPoint    = exitPoint;
    d.stack        = calloc(1, sizeof(Stack_t));
    d.stack->top   = NULL;
    d.stack->size  = 0;
    d.error        = false;
    return d;
}

RenderData_t initRenderData(Data_t d, uint16_t windowW, uint16_t windowH){
    RenderData_t rd;
    rd.width = d.width;
    rd.height = d.height;
    rd.x = -windowW/2;
    rd.y = -windowH/2;

    GLfloat pSizeX = (GLfloat)(windowW) / (rd.width) ;
    GLfloat pSizeY = (GLfloat)(windowH) / (rd.height);

    if(pSizeX > pSizeY) rd.pSize = pSizeY;
    else                rd.pSize = pSizeX;

    int16_t marginX = (windowW - (rd.pSize * rd.width)) / 2;
    int16_t marginY = (windowH - (rd.pSize * rd.height)) / 2;

    rd.x += marginX;
    rd.y += marginY;

    //generate vertex array
    Vertex_t*      vArray = malloc(rd.width * rd.height * 4 * sizeof(Vertex_t));
    VertexColor_t* cArray = calloc(rd.width * rd.height * 4,  sizeof(Vertex_t)); //malloc(rd.width * rd.height * 4 * sizeof(VertexColor_t));

    uint32_t vert = 0;
    for(uint16_t i = 0; i < rd.height; i++){
        for(uint16_t j = 0; j < rd.width; j++){
            vArray[vert].x   = rd.x+rd.pSize*j;
            vArray[vert++].y = rd.y+rd.pSize*i;

            vArray[vert].x   = rd.x+rd.pSize*j;
            vArray[vert++].y = rd.y+rd.pSize+rd.pSize*i;

            vArray[vert].x   = rd.x+rd.pSize+rd.pSize*j;
            vArray[vert++].y = rd.y+rd.pSize+rd.pSize*i;

            vArray[vert].x   = rd.x+rd.pSize+rd.pSize*j;
            vArray[vert++].y = rd.y+rd.pSize*i;
        }
    }

    // memset(cArray, 0, sizeof(VertexColor_t)*rd.width*rd.height*4);

    rd.vertices       = vArray;
    rd.vertices_count = vert;  
    rd.verticesColor  = cArray;

    return rd;
}

RenderData_t clearSeekerColorArray(MazeMatrix_t maze, RenderData_t rd){
    uint16_t i, j, c;
    uint32_t col = 0;
    for(i = 0; i < rd.height; i++){
        for(j = 0; j < rd.width; j++){
            if(maze[i][j] != WALL){
                for(c = 0; c<4; c++){
                    rd.verticesColor[col++] = (struct VertexColor_s) {.r = 255, .g = 255, .b = 255};
                }
            }
            else col+=4;
        }
    }
    return rd;
}

Parms_t getInput(bool first, Action_t mode, Parms_t p){
    Parms_t input = p;
    SDL_DisplayMode displayMode;
    int ans;

    if(!first){
        printf("\n");
    }

    printf("Width x Height: \t");
    scanf ("%hu%hu", &input.width, &input.height);
    if(first){
        printf("Fullscreen? (1/0): ");
        scanf("%i", &ans);
        if(ans){
            input.fullscreen = SDL_WINDOW_FULLSCREEN;
            SDL_GetCurrentDisplayMode(0, &displayMode);
            input.windowW = displayMode.w;
            input.windowH = displayMode.h;
        }
        else{
            input.fullscreen = 0;
            printf("Window width x height: \t");
            scanf("%hu%hu", &input.windowW, &input.windowH);
        }
    }
    if(mode != GENERATE){
        printf("Start Point: \t\t");
        scanf("%hu%hu", &input.startPoint.x, &input.startPoint.y);
        //printf("Exit Point: \t\t");       scanf("%i%i", &input.exitPoint.x, &input.exitPoint.y);
    }
    printf("Step delay(msec): \t");
    scanf("%hu", &input.animationDelay);
    printf("Draw each x frame: \t");
    scanf("%hhu", &input.framesDrop);

    input.exitPoint.x = (input.width % 2 == 0)  ? input.width - 3  : input.width - 2;
    input.exitPoint.y = (input.height % 2 == 0) ? input.height - 3 : input.height - 2;

    return input;
}

//generator and seeker common functions
CellString_t getNeighbours(Data_t *data, Cell_t c, int8_t distance){
    uint16_t x   = c.x;
    uint16_t y   = c.y;
    Cell_t up    = {x, y - distance};
    Cell_t rt    = {x + distance, y};
    Cell_t dw    = {x, y + distance};
    Cell_t lt    = {x - distance, y};
    Cell_t d[4]  = {dw, rt, up, lt};
    uint8_t size = 0;

    CellString_t cells;
    cells.cells = malloc(4 * sizeof(Cell_t));

    uint16_t     height = data->height;
    uint16_t     width  = data->width;
    MazeMatrix_t maze   = data->maze;

    for(uint8_t i = 0; i < 4; i++){ //для каждого направдения d
        if(d[i].x > 0 && d[i].x < width && d[i].y > 0 && d[i].y < height){ //если не выходит за границ
            CellType_t mazeCellCurrent = maze[d[i].y][d[i].x];
            Cell_t     cellCurrent     = d[i];
            if(mazeCellCurrent != WALL && mazeCellCurrent != GENVISITED && mazeCellCurrent != SEEKED && mazeCellCurrent != WAY){ //и не посещена\является стеной
                cells.cells[size] = cellCurrent; //записать в массив;
                size++;
            }
        }
    }

    cells.size = size;
    return cells;
}

void setMode(Cell_t c, MazeMatrix_t maze, CellType_t mode){
    uint16_t x = c.x;
    uint16_t y = c.y;
    maze[y][x] = mode;
}

uint32_t randomRange(uint32_t low, uint32_t high){
    return rand() % (high - low + 1) + low;
}
