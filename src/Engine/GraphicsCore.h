#ifndef GRAPHICS_CORE_H
#define GRAPHICS_CORE_H

#include <SDL2/SDL.h>

#if __APPLE__
#include "SDL2_image/SDL_image.h"
#else
#include <SDL2/SDL_image.h>
#endif
#include "FontSystem.h"
#include <iostream>
#include <fstream>

using namespace std;

// ERRORCONTROL IS WINDOWS SPECIFIC?
//#include "ErrorControl.h"

class cGraphics;
class cTexture;

class cGraphics
{
protected:
	  //HWND              m_hWnd;
      //SDL Window is already created when we invoke Core, but its needed for the render to know what its rendering on
      SDL_Window        *m_window;
	  //IDirect3D8       *m_pD3D;
      SDL_Renderer      *m_renderer;
	  //IDirect3DDevice8 *m_pD3DDevice;
	  //ID3DXSprite      *m_pSprite;
	  //D3DDISPLAYMODE    m_d3ddm;
	  bool              m_Windowed;
	  long              m_Width;
	  long              m_Height;

public:
    cGraphics();
    ~cGraphics();

	//IDirect3D8       *GetDirect3DCOM();
    //IDirect3DDevice8 *GetDeviceCOM();
    //ID3DXSprite      *GetSpriteCOM();

    bool Init();
    bool Shutdown();
    // shutdown seems to do D3D related things, not going to use this function anymore
    //bool Shutdown();
    bool Draw(SDL_Texture *tex, SDL_Rect *src, SDL_Rect *dst);
    bool DrawFlip(SDL_Texture *tex, SDL_Rect *src, SDL_Rect *dst, SDL_Point *center);
    bool DrawPrimitiveRectScreen(int ScreenX, int ScreenY);
    bool DrawRowLineScreen(int ScreenY);
    bool Display();
    bool Clear();
    bool ClearDisplay();
	bool EnableAlphaBlending(bool Enable = true);
	bool EnableAlphaTesting(bool Enable = true);

    SDL_Renderer* GetRenderer();
    SDL_Window* GetWindow();
    long GetWidth();
    long GetHeight();
};


class cTexture
{
  protected:
    cGraphics          *m_Graphics;
    SDL_Surface        *m_Surface;
    SDL_Texture        *m_Texture;
    // alpha value for quick modification
    Uint8              m_curAlpha;
    // yes, we waste mem on storing a font on every object
    TTF_Font           *m_Font;
    unsigned long      m_Width, m_Height;


  public:
    cTexture();
    ~cTexture();

    //bool Load( cGraphics *Graphics, const char* Filename, DWORD Transparent = 0,
	//	D3DFORMAT Format = D3DFMT_UNKNOWN );

    // gfx == our SDL_Renderer already initialized
    bool Load( cGraphics *graphics, const char *Filename );

	//bool Create( cGraphics gfx, SDL_Texture *Texture );
    bool Free();

    bool      IsLoaded();

    long      GetWidth();
    long      GetHeight();
    SDL_PixelFormat* GetFormat();

	//
    //TODO: what is POINT and why are we using GetSrcPoint) - maybe return SDL_RECT?
	//POINT GetSrcPoint( int a_Index, int a_FramesPerCol );
    
    //Blit may be replaced with with SDL Surface render in specific drawing order...  this is probbaly
    //the main function that draws each object to screen.
    bool Blit(long DestX = 0, long DestY = 0, int SrcX = 0, int SrcY = 0,
              long Width = 0, long Height = 0, float XScale = 1.0f,
			  float YScale = 1.0f, float Rotation = 0.0f,
              uint8_t r = 255, uint8_t g = 255, uint8_t b = 255);  // unsure on SDL_Color here...
    
    //draw routine for fonts
    bool Print(long DestX = 0, long DestY = 0, uint8_t a = 255);
    
    //Create texture from TTf_Font
    bool CreateFontTexture(cGraphics *Graphics, cFont *Font, const char *Text, uint8_t r ,uint8_t g, uint8_t b);
    bool CreateFontTextureWrapped(cGraphics *Graphics, cFont *Font, const char *Text, uint8_t r ,uint8_t g, uint8_t b , int WrapSize);
    
    SDL_Point GetSrcPoint(int a_Index, int a_FramesPerCol);
    void SetColor(SDL_Color color);
};
#endif