#include "raylib.h"
#include "player.h"
#include "stage.h"
#include "textures.h"

const int screenWidth = 1800;
const int screenHeight = 1000;

Player player;
Player opponent;

void draw(){
    BeginDrawing();

    ClearBackground(WHITE);
    DrawFPS(0,0);

    drawPlayer(&player);
    drawPlayer(&opponent);

    EndDrawing();
}

void init(){
    InitWindow(screenWidth, screenHeight, "BenBlade");  
    SetTargetFPS(60);

    //Texture
    loadTextures();

    playerInit(&player, 1);
    playerInit(&opponent, 2);
}

void update(){
    draw();
    updatePlayer(&player);
    updatePlayer(&opponent);
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