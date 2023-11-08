/*
Dasher.cpp

Tim Diliberto
*/
#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{
    // Initialize window dimensions WIDTH and HEIGHT
    const int winWidth{1600};
    const int winHeight{900};
    InitWindow(winWidth, winHeight, "Dapper Dasher");

    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    AnimData nebData {
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle rec
        {winWidth, winHeight - nebData.rec.height}, // Vector2 pos
        0, // int frame
        1.0 / 12.0, // float updateTime
        0.0 // float runningTime
    };
    AnimData neb2Data {
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle rec
        {winWidth+750, winHeight - neb2Data.rec.height}, // Vector2 pos
        0, // int frame
        1.0 / 16.0, // float updateTime
        0.0 // float runningTime
    };
    // Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData {
        {0, 0, scarfy.width/6, scarfy.height}, // Rectangle rec
        //Vector2 pos
        {winWidth/2-scarfyData.rec.width/2, winHeight - scarfyData.rec.height},
        0, // int frame
        1.0/12.0, // float updateTime
        0.0 // float runningTime
    };
    // Initialize game physics
    const int gravity{1000}; // ((pixels/s)/s)
    int velocity{0};
    int nebVel{-600}; // nebula's x velocity (pixels/sec)
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
        if (scarfyData.pos.y >= winHeight - scarfyData.rec.height)
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
        nebData.pos.x += nebVel * dT;
        neb2Data.pos.x += nebVel * dT;

        // update scarfy's position
        scarfyData.pos.y += velocity * dT;

        // update nebula animation
        nebData.runningTime += dT;
        if (nebData.runningTime >= nebData.updateTime)
        {
            nebData.runningTime = 0.0;
            nebData.rec.x = nebData.frame * nebData.rec.width;
            nebData.frame++;
            if (nebData.frame > 7) { nebData.frame = 0; }
        }
        neb2Data.runningTime += dT;
        if (neb2Data.runningTime >= neb2Data.updateTime)
        {
            neb2Data.runningTime = 0.0;
            neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
            neb2Data.frame++;
            if (neb2Data.frame > 7) { neb2Data.frame = 0; }
        }

        // update scarfy animation while on ground
        scarfyData.runningTime += dT;
        if (!isInAir)
        {
            if (scarfyData.runningTime >= scarfyData.updateTime)
            {
                scarfyData.runningTime = 0.0;
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;
                if (scarfyData.frame > 5) { scarfyData.frame = 0; }
            }
        }

        // draw nebula
        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);
        DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, RED);

        // draw scarfy's texture rectangle
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // Deconstruct window data
        EndDrawing();
    }
    
    // deconstruct textures and window after closing out
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

    return 0;
}