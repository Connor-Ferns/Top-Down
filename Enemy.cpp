#include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;

    width = texture.width / maxFrames;
    height = texture.height;
}

void Enemy::tick(float deltaTime)
{
    worldPoslastFrame = worldPos;

    //Update Anim
    runningTime += deltaTime;
    if(runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;    
        if(frame >= maxFrames) frame = 0;
    }

    //Draw Character
    Rectangle source = {width * frame, 0.0f, rightLeft * width, height};
    Rectangle dest = {screenPos.x, screenPos.y, scale * width, scale * height};      
    DrawTexturePro(texture, source, dest, Vector2{}, 0.0f, WHITE);
}