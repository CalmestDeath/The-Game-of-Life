#include <stdio.h>
#include "raylib.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define ROWS 50
#define COLS 50

const int cellHeight = SCREEN_HEIGHT / ROWS;
const int cellWidth = SCREEN_WIDTH / COLS;


int currentGrid[ROWS][COLS] ;
int nextGrid[ROWS][COLS];




int CountNeighbors(int rows, int col) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; 
            
            int neighborRow = rows + i;
            int neighborCol = col + j;

            if (neighborRow >= 0 && neighborRow < ROWS && neighborCol >= 0 && neighborCol < COLS) {
                count += currentGrid[neighborRow][neighborCol];
            }
        }
    }
    return count;
}

void Update(void) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {

            if (currentGrid[r][c] == 1) {
                if (CountNeighbors(r, c) < 2 || CountNeighbors(r, c)> 3) {
                    nextGrid[r][c] = 0; 
                } else {
                    nextGrid[r][c] = 1; 
                }
            } else {
                if (CountNeighbors(r, c) == 3) {
                    nextGrid[r][c] = 1; 
                } else {
                    nextGrid[r][c] = 0; 
                }
            }
        }
    }

    for (int rows = 0; rows < ROWS; rows++) {
        for (int col = 0; col < COLS; col++) {
            currentGrid[rows][col] = nextGrid[rows][col];
        }
    }
}

void DrawCells(Color aliveColor) {
    
    for (int rows = 0; rows < ROWS; rows++) {
        for (int col = 0; col < COLS; col++) {
            

            if (currentGrid[rows][col] == 1) {
                DrawRectangle(col * cellWidth, rows * cellHeight, cellWidth - 2, cellHeight - 2, aliveColor); 
            }
            
        }
    }
}



void ClearGrid(int grid[ROWS][COLS]) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            grid[r][c] = 0;
        }
    }
}



int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The Game of Life - By CalmestDeath");
    SetTargetFPS(20); 

    int isRunning = 0;
    
    Color aliveColor = SKYBLUE; 

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_SPACE)) isRunning = !isRunning; 

        if (IsKeyPressed(KEY_C)) ClearGrid(currentGrid);


        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePos = GetMousePosition();
            int cols = mousePos.x / cellWidth;
            int rows = mousePos.y / cellHeight;
            
            if (rows >= 0 && rows < ROWS && cols >= 0 && cols < COLS) {
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) currentGrid[rows][cols] = 1;
            }
        }

        if (isRunning) Update();

        ClearBackground(BLACK);
        BeginDrawing();
         
            
        DrawCells(aliveColor); 
            
            if (isRunning) {
                DrawText("RUNNING [SPACE to pause | C to clear]", 10, 10, 20, GREEN);
            } else {
                DrawText("PAUSED [SPACE to play | Left Click to Draw]", 10, 10, 20, RED);
            }
            
        EndDrawing();
    }

    CloseWindow();
    return 0;
}









