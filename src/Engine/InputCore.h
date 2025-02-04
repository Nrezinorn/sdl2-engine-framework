#pragma once
#include "SDL2/SDL.h"

//#define WIN32_LEAN_AND_MEAN	
//#define SafeRelease(x)	if (x) {x->Release(); x=NULL;}

class CInputCore
{
public:
	CInputCore();
	~CInputCore();

	// Public memembers
	
	// Public methods
	void InitializeInput();

	void Shutdown();

	void ReadInput();
	
	bool KeyDown( SDL_Keycode Key );
	bool KeyPress( SDL_Keycode Key );
	bool SetKeyDown( SDL_Keycode Key );
	bool SetKeyUp( SDL_Keycode Key );

	SDL_Point GetMousePos() { return m_MousePos; }

	void CancelAllInput();

	bool JoyDetected();


private:
    //temp var
	//const Uint8 *keyStates;
	bool m_KeyPressState[322] = {false};
	bool m_LastKeyState[322] = {false};

    Uint32 m_MouseState;
	SDL_Point m_MousePos;

	// gamepad
	SDL_Joystick* gGameController = nullptr;
};
