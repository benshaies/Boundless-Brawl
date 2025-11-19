#include "raylib.h"
#include "player.h"
#include "stage.h"
#include "textures.h"

const int screenWidth = 1800;
const int screenHeight = 1000;

void draw(){
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawFPS(0,0);

    //drawStage(1);
    drawPlayer();

    EndDrawing();
}

void init(){
    InitWindow(screenWidth, screenHeight, "BenBlade");  
    SetTargetFPS(60);

    //Texture
    loadTextures();

    playerInit(1);
}

void update(){
    draw();
    playerMovement();
}

int main(void){

    init();

    while (!WindowShouldClose()){
        update();
    }

    unloadTextures();
    CloseWindow();
    return 0;
}