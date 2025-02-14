#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"
#include "raymath.h"

class BaseCharacter
{
    public:
        BaseCharacter();
        Vector2 getWorldPos() { return worldPos; }
        void undoMovement();
        Rectangle GetCollisionRec();
    protected:
        Texture2D texture = LoadTexture("assets/characters/knight_idle_spritesheet.png");
        Texture2D idle = LoadTexture("assets/characters/knight_idle_spritesheet.png");
        Texture2D run = LoadTexture("assets/characters/knight_run_spritesheet.png");
        Vector2 screenPos{};
        Vector2 worldPos{};
        Vector2 worldPoslastFrame{};
        // 1 : facing right, -1 : facing left
        float rightLeft = 1.f;
        //Anim Var
        float runningTime = 0;
        int frame = 0;
        int maxFrames = 6;
        float updateTime = 1.f/12.f;
        float speed = 4.f;
        float width = 0;
        float height = 0;
        float scale = 4; 
};

#endif