/* Example SDL2 Framework Program (c) 2024 TommyVisic and Jim Gorz */
#include "Engine/AllCores.h"
#include <SDL2/SDL.h>
#include <string>

int main(int argc, char *argv[]){

    // Load a TTF font so we can make a texture 
    cFont gFont_28;
    const char* fontname = "EpBigGuy-PYmE.otf";
    std::string *str_font = new std::string(fontname);
    gFont_28.Create(str_font, 28);

    CGraphicsCore core;
    // pass the SDL flags we want to use to Init()
    core.Init(SDL_INIT_EVERYTHING);
    
    // Inititalize SoundCore for demo
    cSoundCore *SoundCore = new cSoundCore(1,1);

    SoundCore->Initialize();  // Inititalize must be called before you load sound/music
    SoundCore->LoadSoundFromFile("Sound/LaserPowerUp.wav", 0, true);  // looping sound
    SoundCore->LoadMusicFromFile("Music/DemoMIDI.mid", 0);

    SoundCore->PlayMusic(0);
    SoundCore->PlaySound(0);

    //Texture for text to be rendered, must happen after  core is initilized, as our gTexture class 
    //holds a pointer to the renderer
    CTexture gText;
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