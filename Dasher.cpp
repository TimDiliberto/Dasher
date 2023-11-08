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
    Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebPos{winWidth, winHeight - nebRec.height};

    Rectangle neb2Rec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 neb2Pos{winWidth+300, winHeight - nebRec.height};

    int nebVel{-600}; // nebula x velocity (pixels/sec)

    // nebula animation
    int nebFrame{};
    const float nebUpdateTime{1.0/12.0};
    float nebRunningTime{};

    int neb2Frame{};
    const float neb2UpdateTime{1.0/12.0};
    float neb2RunningTime{};

    // Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = winWidth/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = winHeight - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;

    /*
    Rectangle scarfyRec{0, 0, scarfy.width/6, scarfy.height};
    Vector2 scarfyPos;
    scarfyPos.x = winWidth/2 - scarfyRec.width/2;
    scarfyPos.y = winHeight - scarfyRec.height;
    */

    /*
    // animation frame
    int scarfyFrame{};
    // time in s before animation frame updates
    const float scarfyUpdateTime{1.0/12.0};
    float scarfyRunningTime{};
    */

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
        nebPos.x += nebVel * dT;
        neb2Pos.x += nebVel * dT;

        // update scarfy's position
        scarfyData.pos.y += velocity * dT;

        // update nebula animation
        nebRunningTime += dT;
        if (nebRunningTime >= nebUpdateTime)
        {
            nebRunningTime = 0.0;
            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;
            if (nebFrame > 7) { nebFrame = 0; }
        }
        neb2RunningTime += dT;
        if (neb2RunningTime >= neb2UpdateTime)
        {
            neb2RunningTime = 0.0;
            neb2Rec.x = neb2Frame * neb2Rec.width;
            neb2Frame++;
            if (neb2Frame > 7) { neb2Frame = 0; }
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
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);
        DrawTextureRec(nebula, neb2Rec, neb2Pos, RED);

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