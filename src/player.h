#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
#include "animation.h"

    typedef struct{
        Vector2 pos;
        Rectangle rec;
        
        int id;
        
        //Gameplay Stuff
        float dodgeTimer;
        float dodgeDelay;

        float dodgePower;

        float damage;

        bool lookingRight;

        //Attacks
        Rectangle lightAttackHitBox;
        bool lightAttackActive;
        int lightAttackFrameCount;

        //Physcis stuff
        bool isOnGround;
        float velocityY;
        float velocityX;
        float jumpForce;
        bool doubleJump;
        float movementSpeed;

        //Animations
        Animation playerIdleAnim;

    }Player;

    extern Player player;

    void playerInit(int id);

    void playerDodge();

    void playerAttack();

    void playerMovement();

    void drawPlayer();

    void updatePlayer();
#endif
