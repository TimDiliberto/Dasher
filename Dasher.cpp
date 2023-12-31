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

bool isOnGround(AnimData data, int winHeight)
{
    return data.pos.y >= winHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, int maxFrames, float deltaT)
{
    // update runningTime
    data.runningTime += deltaT;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > maxFrames) { data.frame = 0; }
    }
    return data;
}

float updateBGPos(Texture2D background, float bgX, float bgA, float deltaT)
{
    bgX -= bgA * deltaT;
    if (bgX <= -background.width*6.25)
    {
        bgX = 0.0;
    }
    Vector2 bg1Pos{bgX, 0.0};
    DrawTextureEx(background, bg1Pos, 0.0, 6.25, WHITE);
    Vector2 bg2Pos{bgX + background.width * 6.25, 0.0};
    DrawTextureEx(background, bg2Pos, 0.0, 6.25, WHITE);

    return bgX;
}

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

    float finishLine{nebulae[nebulaeSize-1].pos.x + nebula.width/2};

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
    
    // backgroun textures
    Texture2D background = LoadTexture("textures/far-buildings.png");
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    Texture2D foreground = LoadTexture("textures/foreground.png");
    float bgx{};
    float mgx{};
    float fgx{};

    // Initialize game physics
    const int gravity{1000}; // ((pixels/s)/s)
    int velocity{0};
    int nebVel{-600}; // nebula's x velocity (pixels/sec)
    bool isInAir{};
    const int jumpVel {-600}; // pixels/s

    bool collision{};

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

        // update positions of each back, mid, & foreground
        bgx = updateBGPos(background, bgx, 50, dT);
        mgx = updateBGPos(midground, mgx, 150, dT);
        fgx = updateBGPos(foreground, fgx, 250, dT);

        // Dictate downward acceleration based on position relative to ground
        if (isOnGround(scarfyData, winDims[1]))
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

        if (!isInAir) { scarfyData = updateAnimData(scarfyData, 5, dT); }

        // update nebula position
        for (int i=0; i<nebulaeSize; i++)
        {
            nebulae[i].pos.x += nebVel * dT;
        }

        // update finish line position
        finishLine += nebVel * dT;

        // update nebula animation
        for (int i=0; i<nebulaeSize; i++)
        {
            nebulae[i] = updateAnimData(nebulae[i], 7, dT);
        }

        for (AnimData nebula : nebulae)
        {
            float pad{35};
            Rectangle nebRec{
                nebula.pos.x + pad,
                nebula.pos.y + pad,
                nebula.rec.width - 2*pad,
                nebula.rec.height - 2*pad
            };
            Rectangle scarfyRec{
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.rec.width,
                scarfyData.rec.height
            };
            if (CheckCollisionRecs(nebRec, scarfyRec))
            {
                collision = true;
            }
        }

        if (collision)
        {
            DrawText("Game Over!", winDims[0]/4, winDims[1]/2, 100, BLUE);
        }
        else if (scarfyData.pos.x >= finishLine)
        {
            DrawText("You Win!", winDims[0]/4, winDims[1]/2, 100, BLUE);
        }
        else
        {
            // draw scarfy's texture rectangle
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

            // draw nebulae texture rectangles
            for (int i=0; i<nebulaeSize; i++)
            {
                DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
            }
        }

        // Deconstruct window data
            EndDrawing();
    }
    
    // deconstruct textures and window after closing out
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();

    return 0;
}