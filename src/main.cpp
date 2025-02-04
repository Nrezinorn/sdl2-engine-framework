/* Example SDL2 Framework Program (c) 2024 TommyVisic and Jim Gorz */
#include "Engine/AllCores.h"
#include <SDL2/SDL.h>
#include <string>

// Everything gets declared here and then loaded in main()
// you can do whatever you like to meet your needs

// a font, this class doesn't handle font resizing currently
cFont gFont_28;
CGraphicsCore core;
// SoundCore Object Pointer
cSoundCore *SoundCore = nullptr;

CInputCore InputCore;
//Texture for text to be rendered, must happen after  core is initilized, as our gTexture class 
//holds a pointer to the renderer
CTexture gText;
CTexture gJoyText;

bool doLoop = true;

// used by Update()
SDL_Event e;

// Load all Graphics, Fonts, Sounds, etc
void Load() {
    // Load a TTF font so we can make a texture 
    const char* fontname = "EpBigGuy-PYmE.otf";
    std::string *str_font = new std::string(fontname);
    gFont_28.Create(str_font, 28);

    // pass the SDL flags we want to use to Init()
    core.Init(SDL_INIT_EVERYTHING);
    
    SoundCore = new cSoundCore(1,1);
    SoundCore->Initialize();  // Inititalize must be called before you load sound/music
    SoundCore->LoadSoundFromFile("Sound/LaserPowerUp.wav", 0, true);  // looping sound
    SoundCore->LoadMusicFromFile("Music/DemoMIDI.mid", 0);
    
    //probably will crash in MainLoop if not Initialized
    InputCore.InitializeInput();

    // Load Texture
    gText.CreateFontTexture(&core, &gFont_28, "HELLO WORLD", 128, 128, 128);
    gJoyText.CreateFontTexture(&core, &gFont_28, "Gamepad Detected", 255, 255, 255);

}

void Update() {
    while(SDL_PollEvent(&e) != 0) 
    {
      if(e.type == SDL_QUIT) doLoop = false;
    }
}

bool MainLoop() {
    Update(); // do nothing for now
    core.ClearDisplay();
    gText.Blit(core.GetWidth() / 2, core.GetHeight() / 2);

    // show text if we have a gamepad 
    if (InputCore.JoyDetected()) gJoyText.Blit(0, 0);

    core.Display();
    SDL_Delay(200);
    return true;
}

int main(int argc, char *argv[]){
    Load();
  
    SoundCore->PlayMusic(0);
    SoundCore->PlaySound(0);

    while(doLoop) MainLoop();  // main loop:  Update Inputs / Update Graphics
    
    gText.Free();
    gFont_28.Free();
    //SoundCore Handle's it's own shutdown / cleanup via destructor
    core.Shutdown();
    SDL_Quit();

    return 0;
}