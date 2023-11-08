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
    // Initialize window dimensions
    const int winDims[] {1600, 900};
    InitWindow(winDims[0], winDims[1], "Dapper Dasher");

    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    const int nebulaeSize{6};
    AnimData nebulae[nebulaeSize];
    for (int i=0; i<nebulaeSize; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.x = winDims[0] + (i * 750);
        nebulae[i].pos.y = winDims[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0/16.0;
    }

    // Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData {
        {0, 0, scarfy.width/6, scarfy.height}, // Rectangle rec
        //Vector2 pos
        {winDims[0]/2-scarfyData.rec.width/2, winDims[1] - scarfyData.rec.height},
        0, // int frame
        1.0/12.0, // float updateTime
        0.0 // float runningTime
    };
    // Initialize game physics
    const int gravity{1000}; // ((pixels/s)/s)
    int velocity{0};
    int nebVel{-600}; // nebula's x velocity (pixels/sec)
    bool isInAir{};
    const int jumpVel {-600}; // pixels/s

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
        if (scarfyData.pos.y >= winDims[1] - scarfyData.rec.height)
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
        scarfyData.pos.y += velocity * dT;

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

        // update nebula position and animation
        for (int i=0; i<nebulaeSize; i++)
        {
            nebulae[i].pos.x += nebVel * dT;
            nebulae[i].runningTime += dT;

            if (nebulae[i].runningTime >= nebulae[i].updateTime)
            {
                nebulae[i].runningTime = 0.0;
                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
                nebulae[i].frame++;
                if (nebulae[i].frame > 7) { nebulae[i].frame = 0; }
            }

            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }

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