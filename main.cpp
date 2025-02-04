#include "raylib.h"
#include "raymath.h"
#include <iostream>

int main()
{
    const int screenWidth = 384;
    const int screenHeight = 384;

    InitWindow(screenWidth, screenHeight, "Top-Down");

    //Load Map
    Texture2D mapTexture = LoadTexture("assets/worldmap/WorldMap.png");
    Vector2 mapPos = {0.0, 0.0};

    float speed = 4.0;

    Texture2D knight_idle = LoadTexture("assets/characters/knight_idle_spritesheet.png");
    Texture2D knight_run = LoadTexture("assets/characters/knight_run_spritesheet.png");
    Texture2D knight = knight_idle;
    Vector2 knightPos = {
        (float)screenWidth/2.0f - 4.0f * (0.5f * (float)knight.width/6.0f),
        (float)screenHeight/2.0f - 4.0f * (0.5f * (float)knight.height)
    };
    // 1 : facing right, -1 : facing left
    float rightLeft = 1.f;
    //Anim Var
    float runningTime = 0;
    int frame = 0;
    const int maxFrames = 6;
    const float updateTime = 1.f/12.f;



    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        Vector2 direction{};
        if(IsKeyDown(KEY_A)) direction.x -= 1.0;
        if(IsKeyDown(KEY_D)) direction.x += 1.0;
        if(IsKeyDown(KEY_W)) direction.y -= 1.0;
        if(IsKeyDown(KEY_S)) direction.y += 1.0;
        if(Vector2Length(direction) != 0.0)
        {           
            mapPos = Vector2Subtract(mapPos,  Vector2Scale(Vector2Normalize(direction), speed));
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
            knight = knight_run;
        }
        else
        {
            knight = knight_idle;
        }
        
        DrawTextureEx(mapTexture, mapPos, 0.0, 4.0, WHITE);

        //Update Anim
        runningTime += GetFrameTime();
        if(runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.f;    
            if(frame >= maxFrames) frame = 0;
        }

        //Draw Character
        Rectangle kightSource = {(float)knight.width/6.0f * frame, 0.0f, rightLeft * (float)knight.width/6.0f, (float)knight.height};
        Rectangle knightDest = {knightPos.x, knightPos.y, 4.0f * (float)knight.width/6.0f, 4.0f * (float)knight.height};      
        DrawTexturePro(knight, kightSource, knightDest, Vector2{}, 0.0f, WHITE);

        EndDrawing();
    }

    //De-Initialization
    UnloadTexture(mapTexture);
    CloseWindow();
}