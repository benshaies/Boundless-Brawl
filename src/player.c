#include "player.h"
#include "stage.h"
#include "stdio.h"
#include "textures.h"

Vector2 pOneSpawnPoint = {600, 400};
Vector2 pTwoSpawnPoint = {1200, 400};

float gravity = 0.85;

void playerInit(Player *player,int id){
    player->id = id;
    if(id == 1){
        player->pos = pOneSpawnPoint;
        player->id = id;
        player->lookingRight = true;
    }
    else if(id == 2){
        player->pos = pTwoSpawnPoint;
        player->id = id;
        player->lookingRight = false;
    }

    player->rec = (Rectangle){player->pos.x, player->pos.y, 100, 100};

    //Gameplay stuff
    player->damage = 0.0f;

    player->dodgeTimer = GetTime();
    player->dodgeDelay = 1.5f;

    player->dodgeCountdown = 0;
    player->isDodging = false;

    player->dodgePower = 25;


    //Attacks
    player->lightAttackHitBox = (Rectangle){player->pos.x, player->pos.y, 50, 50};
    player->lightAttackActive = false;
    player->lightAttackFrameCount = 0;

    player->isOnGround = false;
    player->velocityY = 0.0f;
    player->velocityX = 0.0f;
    player->jumpForce = -20.0f;
    player->movementSpeed = 6.0f;
    player->doubleJump = true;

    //Animation
    animationInit(&player->playerIdleAnim, 0, playerIdleTexture, 16, 4, 0, 0);
    animationInit(&player->playerRunAnim, 0, playerRunTexture, 16, 4, 0, 0);

    //Input variables
    player->moveRightInput = false;
    player->moveLeftInput = false;
    player->jumpInput = false;
    player->dodgeInput = false;
    player->lightAttackInput = false;
}


void playerInput(Player *player){
    player->moveRightInput = IsKeyDown(KEY_D);
    player->moveLeftInput = IsKeyDown(KEY_A);
    player->jumpInput = IsKeyPressed(KEY_SPACE);
    player->dodgeInput = IsKeyPressed(KEY_LEFT_SHIFT);
    player->lightAttackInput = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void enemyInput(Player *enemy){
    if(enemy->pos.x > 1100){
        enemy->moveLeftInput = true;
        enemy->moveRightInput = false;
    }
    else if(enemy->pos.x < 200){
        enemy->moveLeftInput = false;
        enemy->moveRightInput = true;
    }
}

void playerDodge(Player *player){
    //Timer and input for dodge check
    if(player->dodgeInput && (GetTime() - player->dodgeTimer >= player->dodgeDelay) && !player->isDodging){
        player->isDodging = true;
        player->dodgeTimer = GetTime();
    }

    //Applying dodge when bool is active
    if(player->isDodging){
        player->velocityX = player->lookingRight ? player->dodgePower : -player->dodgePower;
        player->velocityY = 0;
        player->dodgeCountdown++;
    }

    //Making sure dodge is happening for 5 frames and then resetting boolean
    if(player->dodgeCountdown >= DODGE_FRAMES){
        player->isDodging = false;
        player->dodgeCountdown = 0;
    }
}

void playerAttack(Player *player){
    if(player->lightAttackInput && !player->lightAttackActive){
        player->lightAttackActive = true;
        player->lightAttackHitBox.x = player->pos.x + (player->lookingRight ? 100 : -50);
        player->lightAttackHitBox.y = player->pos.y + 25;

        printf("Attack\n");
    }

    if(player->lightAttackActive){
        player->lightAttackFrameCount++;

        if(player->lightAttackFrameCount >= 5){
            player->lightAttackActive = false;
            player->lightAttackFrameCount = 0;
        }   
    }

}

void playerMovement(Player *player){
    //Input velocity changes
    if(player->moveRightInput && !player->isDodging){
        player->velocityX = player->movementSpeed;
        player->lookingRight = true;
    }
    else if(player->moveLeftInput && !player->isDodging){
        player->velocityX = -player->movementSpeed;
        player->lookingRight = false;
    }
    else{
        player->velocityX = 0;
    }

    //Dodging Function call
    playerDodge(player);

    //Player Attack Call
    playerAttack(player);

    //Jumping velocity changes
    if(player->jumpInput && (player->isOnGround || player->doubleJump)){
        player->velocityY = player->jumpForce;

        if(!player->isOnGround){ 
            player->doubleJump = false;
        }
        player->isOnGround = false;
    }

    //Modify velocityY every frame
    if(!player->isOnGround){
        if(IsKeyDown(KEY_S)){
            player->velocityY += gravity + 1;
        }
        else{
            player->velocityY += gravity;
        }
        
    }
    
    //Calculate new potential position
    float newX = player->pos.x + player->velocityX;
    float newY = player->pos.y + player->velocityY;
    float finalY, finalX;

    //Collision Check Vertical
    if(newY >=stage.y - player->rec.height && (player->pos.x >= stage.x - player->rec.width && player->pos.x <= stage.x + stage.width)){
        finalY = stage.y - player->rec.height;
        player->isOnGround = true;
        player->doubleJump = true;
        player->velocityY = 0;
    }
    else{
        finalY = player->pos.y + player->velocityY;
        player->isOnGround = false;
    }

    //Collision Check Horizontal
    finalX = player->pos.x + player->velocityX;

    //Apply movement
    player->pos.x = finalX;
    player->pos.y = finalY;

    //Update rectangle
    player->rec.x = player->pos.x;
    player->rec.y = player->pos.y;
}


void drawPlayer(Player *player){

    if(player->moveLeftInput || player->moveRightInput){
        playAnimation(&player->playerRunAnim, player->rec, player->lookingRight ? 1 : -1, 0.10, player->isDodging ? GRAY : WHITE);
    }
    else{
        playAnimation(&player->playerIdleAnim, player->rec, player->lookingRight ? 1 : -1, 0.10, player->isDodging ? GRAY : WHITE);
    }
    
    DrawRectangleRec(stage, BLUE);

    if(player->lightAttackActive){
        DrawRectangleRec(player->lightAttackHitBox, RED);
    }
}

void updatePlayer(Player *player){
    //Only apply 
    if(player->id == 1){
        playerInput(player);
    }
    else if(player->id == 2){
        //enemyInput(player);
    }
    
    playerMovement(player);
}