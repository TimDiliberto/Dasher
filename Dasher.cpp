/*
Dasher.cpp

Tim Diliberto
*/
#include "raylib.h"

int main()
{
    // Initialize window dimensions WIDTH and HEIGHT
    const int winWidth{1600};
    const int winHeight{900};
    InitWindow(winWidth, winHeight, "Dapper Dasher");

    const int gravity{1};

    // Initialize rectangle dimensions
    const int width{50};
    const int height{50};

    int posY{winHeight - height};
    int velocity{0};
    bool isInAir{};
    const int jumpVel{-22};

    // Ideal frames per second
    SetTargetFPS(60);

    // WindowShouldClose() will return false until you hit 'ESC' or 'X' button
    while (!WindowShouldClose())
    {
        // Setup window data
        BeginDrawing();
        ClearBackground(BLACK);

        // GAME LOGIC

        if (posY >= winHeight - height)
        {
            velocity = 0;
            isInAir = false;
        }
        else
        {
            velocity += gravity;
            isInAir = true;
        }

        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        posY += velocity;

        DrawRectangle(winHeight/2, posY, width, height, BLUE);

        // Deconstruct window data
        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}