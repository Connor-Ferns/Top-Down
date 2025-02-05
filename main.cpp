#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main()
{
    const int screenWidth = 384;
    const int screenHeight = 384;
    InitWindow(screenWidth, screenHeight, "Top-Down");

    //Load Map
    Texture2D mapTexture = LoadTexture("assets/worldmap/WorldMap.png");
    Vector2 mapPos = {0.0, 0.0};
    const float mapScale = 4.f;

    Character knight;
    knight.setScreenPos(screenWidth, screenHeight);

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        //Draw Map
        DrawTextureEx(mapTexture, mapPos, 0.0, mapScale, WHITE);

        knight.tick(GetFrameTime());
        //Check Maps Bounds
        if(knight.getWorldPos().x < 0.f ||
           knight.getWorldPos().y < 0.f ||
           knight.getWorldPos().x + screenWidth > mapTexture.width * mapScale || 
           knight.getWorldPos().y + screenHeight > mapTexture.height * mapScale)
        {
            knight.undoMovement();
        }

        EndDrawing();
    }

    //De-Initialization
    UnloadTexture(mapTexture);
    CloseWindow();
}