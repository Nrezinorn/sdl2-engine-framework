#include "Engine/AllCores.h"
#include <SDL2/SDL.h>

int main(int argc, char *argv[]){

    cGraphics core;
    core.Init();

    core.Display();

    SDL_Delay(4000);

    return 0;
}