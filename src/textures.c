#include "textures.h"

Texture2D playerIdleTexture;

void loadTextures(){
    playerIdleTexture = LoadTexture("../assets/playerIdle.png");
}

void unloadTextures(){
    UnloadTexture(playerIdleTexture);
}