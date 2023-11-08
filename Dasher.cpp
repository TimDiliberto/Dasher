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

    // nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebulaRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebulaPos{winWidth, winHeight - nebulaRec.height};
    // nebula x velocity (pixels/sec)
    int nebulaVel{-600};

    // scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec{0, 0, scarfy.width/6, scarfy.height};
    Vector2 scarfyPos;
    scarfyPos.x = winWidth/2 - scarfyRec.width/2;
    scarfyPos.y = winHeight - scarfyRec.height;


    // animation frame
    int frame{};
    // time in s before animation frame updates
    const float updateTime{1.0/12.0};
    float runningTime{};

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

        // update nebula position
        nebulaPos.x += nebulaVel * dT;

        // update scarfy's position
        scarfyPos.y += velocity * dT;

        // update runningTime
        runningTime += dT;

        // update animation frame while on ground
        if (!isInAir)
        {
            if (runningTime >= updateTime)
            {
                runningTime = 0.0;
                scarfyRec.x = frame * scarfyRec.width;
                frame++;
                if (frame > 5) { frame = 0; }
            }
        }

        // draw nebula
        DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);

        // draw scarfy's texture rectangle
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // Deconstruct window data
        EndDrawing();
    }
    
    // deconstruct textures and window after closing out
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

    return 0;
}