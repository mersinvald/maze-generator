#include <generator.h>

CellString_t getCells(unsigned int width, unsigned int height, MazeMatrix_t maze){
    CellString_t cells;
    unsigned int i, j, size = 0;

    cells.cells = malloc(width*height*sizeof(Cell_t));

    for(i = 0; i < height; i++){
        for(j = 0; j < height; j++){
            if(maze[i][j] != WALL){
                cells.cells[size].x = j;
                cells.cells[size].y = i;
                size++;
            }
        }
    }
    cells.size = size;
    return cells;
}

CellString_t getUnvisitedCells(unsigned int width, unsigned int height, MazeMatrix_t maze){
    CellString_t cells;
    unsigned long long i, j, size = 0;

    //printBitmap(*maze, width, height);

    cells.cells = malloc(width*height*sizeof(Cell_t));

    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            if((maze[i][j] != WALL) && (maze[i][j] != GENVISITED)){
                cells.cells[size].x = j;
                cells.cells[size].y = i;
                size++;
            }
        }
    }
    cells.size = size;
    return cells;
}

void removeWall(Cell_t first, Cell_t second, MazeMatrix_t maze){
    int8_t xDiff = second.x - first.x;
    int8_t yDiff = second.y - first.y;
    int8_t addX, addY;
    Cell_t target;

    addX = (xDiff != 0) ? (xDiff / abs(xDiff)) : 0; //(diff.x > 0) ? 1 : 0, (!diff.x) ? 0
    addY = (yDiff != 0) ? (yDiff / abs(yDiff)) : 0;

    target.x = first.x + addX; //координаты стенки
    target.y = first.y + addY;

    maze[target.y][target.x] = GENVISITED;
}

uint32_t unvisitedCount(uint16_t width, uint16_t height, MazeMatrix_t maze){
    uint32_t count = 0;

    for (uint16_t i = 0; i < height; i++) {
        for (uint16_t j = 0; j < width; j++) {
            if(maze[i][j] != WALL && maze[i][j] != GENVISITED) count++;
        }
    }

    return count;
}

bool generateStep(Data_t* d){
    uint32_t     randNum;
    CellString_t cellStringUnvisited;
    CellString_t cellStringNeighbours = getNeighbours(d, d->startPoint, 2);

    if(cellStringNeighbours.size != 0){ //если у клетки есть непосещенные соседи
        //выбираем случайного соседа
        randNum  = randomRange(0, cellStringNeighbours.size-1);
        d->cellNext = cellStringNeighbours.cells[randNum];

        //заносим текущую точку в стек
        push(d->startPoint, d->stack);

         //убираем стену между текущей и сосендней точками
        removeWall(d->startPoint, d->cellNext, d->maze);
        d->unvisitedNum--;

        //делаем соседнюю точку текущей и отмечаем ее посещенной
        d->startPoint = d->cellNext;
        setMode(d->startPoint, d->maze, GENVISITED);

        free(cellStringNeighbours.cells);
    }

    else if(d->stack->size){ //если нет соседей, возвращаемся на предыдущую точку
        d->startPoint = pop(d->stack);
    }

    else{ //если нет соседей и точек в стеке, но не все точки посещены, выбираем случайную из непосещенных
        cellStringUnvisited = getUnvisitedCells(d->width, d->height, d->maze);
        randNum             = randomRange(0, cellStringUnvisited.size-1);
        d->startPoint       = cellStringUnvisited.cells[randNum];
        free(cellStringUnvisited.cells);
    }
    return d;
}

MazeMatrix_t init(uint16_t width, uint16_t height){
    MazeMatrix_t maze;
    maze  = malloc(height * sizeof(uint8_t*));
    for(uint16_t i = 0; i < height; i++){ //инициализируем матрицу и заполняем стенами
        maze[i] = malloc(width  * sizeof(uint8_t));
        for(uint16_t j = 0; j < width; j++){
            if((i % 2 != 0   && j % 2 != 0) &&
               (i < height-1 && j < width-1))
                    maze[i][j] = GENCELL;
            else    maze[i][j] = WALL;
        }
    }

    //for(i = 1; i < height-1; i+=2){ //инициализируем клетки.
    //    for(j = 1; j < width-1; j+=2){
    //        maze[i][j] = GENCELL;
    //    }
    //}
    return maze;
}

MazeMatrix_t finalize(uint16_t width, uint16_t height, MazeMatrix_t maze){
    for(uint16_t i = 0; i < height; i++){
        for(uint16_t j = 0; j < width; j++){
            if(maze[i][j] != WALL)
                maze[i][j] = CELL;
        }
    }

    return maze;
}

