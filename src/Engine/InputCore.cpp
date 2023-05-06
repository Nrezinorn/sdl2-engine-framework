#include "InputCore.h"

CInputCore::CInputCore()
{
	
}

CInputCore::~CInputCore()
{

}

//Keyboard works out of the box, TODO: initialize the Controller here
void CInputCore::InitializeInput()
{
	// init all states to false
	for( int i = 0; i < 322; i++) {
		m_KeyPressState[i] = false;
		m_LastKeyState[i] = false;
	}
	// todo:: init joysticks
}

// close SDL_GAMECONTROLLER_SUBSYSTEM
void CInputCore::Shutdown()
{

}

// read all inputs kb+mouse+controller
void CInputCore::ReadInput()
{
    // copy prev frame keys
	for ( int x = 0; x < 322 ; x++) m_LastKeyState[x] = m_KeyPressState[x];
	
	// key keystates
	const Uint8 *keyStates = SDL_GetKeyboardState(NULL);

	//copy states into currentstates
    for ( int i = 0; i < 322 ; i++) m_KeyPressState[i] = keyStates[i];

}

bool CInputCore::KeyDown( SDL_Keycode Key )
{
  // KLUDGE: Key initializes to some huge nuymber somewhere without this....
  if (Key > 321) return false;
  if (m_KeyPressState[Key]){
	  return true;
  }
  return false;
}

bool CInputCore::KeyPress(SDL_Keycode Key)
{
    // KLUDGE: Key initializes to some huge nuymber somewhere without this....
	if (Key > 321) return false;

	if (m_KeyPressState[Key] && !m_LastKeyState[Key]) { 
		return true;
	}
	return false;
}

void CInputCore::CancelAllInput() {
	for( int i = 0; i < 322; i++ )
		m_KeyPressState[i] = 0;
}