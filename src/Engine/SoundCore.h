#pragma once

#if __APPLE__
#include <SDL2_mixer/SDL_mixer.h>
#else
#include "SDL2/SDL_mixer.h"
#endif
#include <string>
using std::string;

// Hardcoded values for Testing
#define SOUND_SLOT_SIZE 3  // we have 4 sounds
#define MUSIC_SLOT_SIZE 2  // we have 1 midi file

class cSoundCore
{
public:
	cSoundCore();
	cSoundCore(int MAX_SOUNDS, int MAX_MUSIC);
	~cSoundCore();

	void Initialize();
	void Shutdown();

	void LoadSoundFromFile(const char* a_FilePath, int a_Slot, bool a_Loop = false );
	void PlaySound(int a_SoundNumber, long a_Volume = 128 );  //128 is max volume level in SDL2
	void StopSound(int);
	void LoadMusicFromFile(const char* a_FilePath, int track);
	void PlayMusic(int track);
	void StopMusic();
	void StopAllSounds();
	void UnloadSound(int ai_Slot);
	void UnloadMusic(int track);

private:
	int MAX_SOUNDS;
	int MAX_MUSIC;
	Mix_Chunk* mp_Sounds[SOUND_SLOT_SIZE];
	Mix_Music* mp_Songs[MUSIC_SLOT_SIZE];
	bool mb_Dead;  //Turn on all Playback
};