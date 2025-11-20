#include "textures.h"

Texture2D playerIdleTexture;
Texture2D playerRunTexture;

void loadTextures(){
    playerIdleTexture = LoadTexture("../assets/playerIdle.png");
    playerRunTexture = LoadTexture("../assets/playerRun.png");
}

void unloadTextures(){
    UnloadTexture(playerIdleTexture);
    UnloadTexture(playerRunTexture);
}