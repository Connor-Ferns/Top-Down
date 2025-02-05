#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight)
{
    width = texture.width / maxFrames;
    height = texture.height;

    screenPos = {
        static_cast<float>(winWidth) / 2.0f - scale * (0.5f * width),
        static_cast<float>(winHeight) / 2.0f - scale * (0.5f * height)
    };
}

void Character::tick(float deltaTime)
{
    worldPoslastFrame = worldPos;

    Vector2 direction{};
    if(IsKeyDown(KEY_A)) direction.x -= 1.0;
    if(IsKeyDown(KEY_D)) direction.x += 1.0;
    if(IsKeyDown(KEY_W)) direction.y -= 1.0;
    if(IsKeyDown(KEY_S)) direction.y += 1.0;
    if(Vector2Length(direction) != 0.0)
    {           
        worldPos = Vector2Add(worldPos,  Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }

    //Update Anim
    runningTime += deltaTime;
    if(runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;    
        if(frame >= maxFrames) frame = 0;
    }

    //Draw Character
    Rectangle kightSource = {width * frame, 0.0f, rightLeft * width, height};
    Rectangle knightDest = {screenPos.x, screenPos.y, scale * width, scale * height};      
    DrawTexturePro(texture, kightSource, knightDest, Vector2{}, 0.0f, WHITE);
}

void Character::undoMovement()
{
    worldPos = worldPoslastFrame;
}