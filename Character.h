#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
    public:
        Character(int screenWidth, int screenHeign);
        void tick(float deltaTime);
    private:
    
};