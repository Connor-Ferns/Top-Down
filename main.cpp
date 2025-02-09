#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

int main()
{
    const int screenWidth = 384;
    const int screenHeight = 384;
    InitWindow(screenWidth, screenHeight, "Top-Down");

    //Load Map
    Texture2D mapTexture = LoadTexture("assets/worldmap/WorldMap.png");
    Vector2 mapPos = {0.0, 0.0};
    const float mapScale = 4.f;

    Character knight = Character(screenWidth, screenHeight);

    Prop props[2] = {
        Prop{Vector2{600.f,300.f}, LoadTexture("assets/nature_tileset/Rock.png")},
        Prop{Vector2{400.f,500.f}, LoadTexture("assets/nature_tileset/Log.png")}
    };

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        //Draw Map
        DrawTextureEx(mapTexture, mapPos, 0.0, mapScale, WHITE);

        //Draw Props
        for(auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        knight.tick(GetFrameTime());
        //Check Maps Bounds
        if(knight.getWorldPos().x < 0.f ||
           knight.getWorldPos().y < 0.f ||
           knight.getWorldPos().x + screenWidth > mapTexture.width * mapScale || 
           knight.getWorldPos().y + screenHeight > mapTexture.height * mapScale)
        {
            knight.undoMovement();
        }

        //Check for Props Collision
        for(auto prop : props)
        {
            if(CheckCollisionRecs(knight.GetCollisionRec(), prop.GetCollisionRec(knight.getWorldPos()))) knight.undoMovement();
        }

        EndDrawing();
    }

    //De-Initialization
    UnloadTexture(mapTexture);
    CloseWindow();
}