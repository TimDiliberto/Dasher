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

    // Initialize textures and sprite data
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = winWidth/2 - scarfyRec.width/2;
    scarfyPos.y = winHeight - scarfyRec.height;

    // Initialize game physics
    const int gravity{1000}; // ((pixels/s)/s)
    int velocity{0};
    bool isInAir{};
    const int jumpVel{-600}; // pixels/s

    // Ideal frames per second
    SetTargetFPS(60);

    // WindowShouldClose() will return false until you hit 'ESC' or 'X' button
    while (!WindowShouldClose())
    {
        // get time between current and previous frames
        float dT{ GetFrameTime() };

        // Setup window data
        BeginDrawing();
        ClearBackground(BLACK);

        // Dictate downward acceleration based on position relative to ground
        if (scarfyPos.y >= winHeight - scarfyRec.height)
        {
            velocity = 0;
            isInAir = false;
        }
        else
        {
            velocity += gravity * dT;
            isInAir = true;
        }

        // Jump feature ONLY on ground
        if (IsKeyPressed(KEY_SPACE) && !isInAir) { velocity += jumpVel; }

        // update scarfy's position
        scarfyPos.y += velocity * dT;

        // draw scarfy's texture rectangle
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // Deconstruct window data
        EndDrawing();
    }
    
    // deconstruct textures and window after closing out
    UnloadTexture(scarfy);
    CloseWindow();

    return 0;
}