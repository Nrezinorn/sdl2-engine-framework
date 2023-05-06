#include "Engine/AllCores.h"
#include <SDL2/SDL.h>
#include <string>

int main(int argc, char *argv[]){

    // Load a TTF font so we can make a texture 
    cFont gFont_28;
    const char* fontname = "EpBigGuy-PYmE.otf";
    std::string *str_font = new std::string(fontname);
    gFont_28.Create(str_font, 28);

    CGraphics core;
    core.Init();
    
    //Texture for text to be rendered, must happen after  core is initilized, as our gTexture class 
    //holds a pointer to the renderer
    cTexture gText;
    gText.CreateFontTexture(&core, &gFont_28, "HELLO WORLD", 128, 128, 128);


    core.ClearDisplay();
    gText.Blit(core.GetWidth() / 2, core.GetHeight() / 2);    
    core.Display();

    SDL_Delay(10000);

    gText.Free();
    gFont_28.Free();
    core.Shutdown();
    SDL_Quit();

    return 0;
}