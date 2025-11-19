#include "player.h"
#include "stage.h"
#include "stdio.h"
#include "textures.h"

Player player;

Vector2 pOneSpawnPoint = {600, 400};
Vector2 pTwoSpawnPoint = {1200, 400};

float gravity = 1;

void playerInit(int id){
    player.id = id;
    if(id == 1){
        player.pos = pOneSpawnPoint;
    }
    else if(id == 2){
        player.pos = pTwoSpawnPoint;
    }

    player.rec = (Rectangle){player.pos.x, player.pos.y, 100, 100};

    //Gameplay stuff
    player.damage = 0.0f;

    player.dodgeTimer = GetTime();
    player.dodgeDelay = 1.5f;

    player.dodgePower = 100;

    player.lookingRight = true;

    //Attacks
    player.lightAttackHitBox = (Rectangle){player.pos.x, player.pos.y, 50, 50};
    player.lightAttackActive = false;
    player.lightAttackFrameCount = 0;

    player.isOnGround = false;
    player.velocityY = 0.0f;
    player.velocityX = 0.0f;
    player.jumpForce = -20.0f;
    player.movementSpeed = 6.0f;
    player.doubleJump = true;

    //Animation
    animationInit(&player.playerIdleAnim, 0, playerIdleTexture, 16, 4, 0, 0);
}

void playerDodge(){
    if(IsKeyPressed(KEY_LEFT_SHIFT) && (GetTime() - player.dodgeTimer >= player.dodgeDelay)){
        player.velocityX = player.lookingRight ? player.dodgePower : -player.dodgePower;
        player.velocityY = 0;
        player.dodgeTimer = GetTime();
    }
}

void playerAttack(){
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !player.lightAttackActive){
        player.lightAttackActive = true;
        player.lightAttackHitBox.x = player.pos.x + (player.lookingRight ? 100 : -50);
        player.lightAttackHitBox.y = player.pos.y + 25;

        printf("Attack\n");
    }

    if(player.lightAttackActive){
        player.lightAttackFrameCount++;

        if(player.lightAttackFrameCount >= 5){
            player.lightAttackActive = false;
            player.lightAttackFrameCount = 0;
        }   
    }

}

void playerMovement(){
    //Input velocity changes
    if(IsKeyDown(KEY_D)){
        player.velocityX = player.movementSpeed;
        player.lookingRight = true;
    }
    else if(IsKeyDown(KEY_A)){
        player.velocityX = -player.movementSpeed;
        player.lookingRight = false;
    }
    else{
        player.velocityX = 0;
    }

    //Dodging Function call
    playerDodge();

    //Player Attack Call
    playerAttack();

    //Jumping velocity changes
    if(IsKeyPressed(KEY_SPACE) && (player.isOnGround || player.doubleJump)){
        player.velocityY = player.jumpForce;

        if(!player.isOnGround){ 
            player.doubleJump = false;
        }
        player.isOnGround = false;
    }

    //Modify velocityY every frame
    if(!player.isOnGround){
        player.velocityY += gravity;
    }
    
    //Calculate new potential position
    float newX = player.pos.x + player.velocityX;
    float newY = player.pos.y + player.velocityY;
    float finalY, finalX;

    //Collision Check Vertical
    if(newY >=stage.y - player.rec.height && (player.pos.x >= stage.x - player.rec.width && player.pos.x <= stage.x + stage.width)){
        finalY = stage.y - player.rec.height;
        player.isOnGround = true;
        player.doubleJump = true;
        player.velocityY = 0;
    }
    else{
        finalY = player.pos.y + player.velocityY;
        player.isOnGround = false;
    }

    //Collision Check Horizontal
    finalX = player.pos.x + player.velocityX;

    //Apply movement
    player.pos.x = finalX;
    player.pos.y = finalY;

    //Update rectangle
    player.rec.x = player.pos.x;
    player.rec.y = player.pos.y;
}


void drawPlayer(){
    playAnimation(&player.playerIdleAnim, player.rec, player.lookingRight ? 1 : -1);
    DrawRectangleRec(stage, BLACK);

    if(player.lightAttackActive){
        DrawRectangleRec(player.lightAttackHitBox, BLUE);
    }
}

void updatePlayer(){

}