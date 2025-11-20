#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
#include "animation.h"

#define DODGE_FRAMES 12

    typedef struct{
        Vector2 pos;
        Rectangle rec;
        
        int id;
        
        //Gameplay Stuff
        float dodgeTimer;
        float dodgeDelay;

        int dodgeCountdown;
        bool isDodging;

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
        Animation playerRunAnim;

        //Input variables
        bool moveRightInput;
        bool moveLeftInput;
        bool jumpInput;
        bool dodgeInput;
        bool lightAttackInput;

    }Player;

    void playerInit(Player *player, int id);

    void playerInput(Player *player);

    void playerDodge(Player *player);

    void playerAttack(Player *player);

    void playerMovement(Player *player);

    void drawPlayer(Player *player);

    void updatePlayer(Player *player);

    #endif
