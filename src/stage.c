#include "stage.h"


Rectangle stage = {0, 850, 1800, 300};

void drawStage(int currentStage){
    DrawRectangleRec(stage, MAROON);
}