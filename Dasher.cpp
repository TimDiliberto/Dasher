/*
Dasher.cpp

Tim Diliberto
*/
#include "raylib.h"

int main()
{
    // Initialize window dimensions WIDTH and HEIGHT
    int winWidth{1600};
    int winHeight{900};
    InitWindow(winWidth, winHeight, "Dapper Dasher");

    // Ideal frames per second
    SetTargetFPS(60);

    // WindowShouldClose() will return false until you hit 'ESC' or 'X' button
    while (!WindowShouldClose())
    {
        // Setup window data
        BeginDrawing();
        ClearBackground(BLACK);

        // GAME LOGIC

        // Deconstruct window data
        EndDrawing();
    }

    return 0;
}