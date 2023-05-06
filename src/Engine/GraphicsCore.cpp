#include "GraphicsCore.h"
#include <iostream>

CGraphics::CGraphics()
{
  m_window = NULL;
  m_renderer = NULL;
  m_Width  = 640;
  m_Height = 480;
  // start in windowed mode for testing
  m_Windowed = true;
  //SDL_Rect textureLocation = { 0, 0, 640, 480};
}

CGraphics::~CGraphics()
{
  this->Shutdown();
}

bool CGraphics::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    return 1;
  }
// set graphics class SDL window handle
this->m_window = SDL_CreateWindow(
			    "SDL2 Framework Engine",
          //FULLSCREEN OPTS  NULL, NULL, NULL,NULL,
			    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			    this->m_Width, this->m_Height, SDL_WINDOW_SHOWN
          //|SDL_WINDOW_FULLSCREEN_DESKTOP
			    );
          
if (this->m_window == NULL) {
  std::cout << "Error loading window" << std::endl;
  //printf(stderr, "could not create window: %s\n", SDL_GetError());
  return false;
}

// failed to set window
// TODO SDL_ERROR handling for clarity

// if we dont have a renderer for graphics yet, make one!  if you dont call init, other graphics calls will fail.
this->m_renderer = SDL_CreateRenderer(this->m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
SDL_SetRenderDrawColor(this->m_renderer, 0x00, 0x00, 0x00, 0xFF );
SDL_RenderSetLogicalSize(this->m_renderer, m_Width,m_Height);
SDL_RenderClear(this->m_renderer);
// TODO SDL_ERROR handling for clarity

return true;
}

bool CGraphics::Shutdown()
{
  // Need to Destroy window before renderer....of we segfault, wny?
  if (m_window)
    SDL_DestroyWindow(m_window);
  // cleanup renderer in graphics class.
  if (m_renderer)
    SDL_DestroyRenderer(m_renderer);
  //set window pointer in our class to NULL
  //m_window = NULL;

  return true;
}

// Draw texture to renderer
//TODO: add sprite scaling 
//TODO: add SDL_RenderFlip flags to function / elsewhere
bool CGraphics::Draw(SDL_Texture *tex, SDL_Rect *src, SDL_Rect *dst) {
  
  if (SDL_RenderCopy(this->m_renderer, tex, src, dst) < 0) {
    std::cout << "Error Adding to Renderer" <<std::endl; 
  }
  //SDL_RenderCopyEx(this->m_renderer, tex, src, dst, NULL, NULL, NULL);
  return true;
}

bool CGraphics::DrawFlip(SDL_Texture *tex, SDL_Rect *src, SDL_Rect *dst, SDL_Point *center) {
  if (SDL_RenderCopyEx(this->m_renderer, tex, src, dst, 0, center, SDL_FLIP_HORIZONTAL) < 0) {
    std::cout << "Error Adding to Renderer" <<std::endl; 
  }
  //SDL_RenderCopyEx(this->m_renderer, tex, src, dst, NULL, NULL, NULL);
  return true;
}

//For Debugging, hardcode 32x32 rects to the screen with 128 alpha
bool CGraphics::DrawPrimitiveRectScreen(int ScreenX, int ScreenY) {
  //screen X/Y are the upper corner to start the rect

  SDL_Rect objDstRect = { ScreenX, ScreenY, 32, 32 };
  
  //dont bother checking for failure
  SDL_RenderDrawRect(this->m_renderer, &objDstRect);

  return true;
}

bool CGraphics::DrawRowLineScreen(int ScreenY){
  // hardcoded X to 0 - 640, use yellow
  uint8_t r,g,b,a;
  SDL_GetRenderDrawColor(this->m_renderer, &r, &g, &b, &a);
  SDL_SetRenderDrawColor(this->m_renderer, 0xFF, 0xFF, 0x00, 0x80);

  if (SDL_RenderDrawLine(this->m_renderer, 0, ScreenY, 640, ScreenY) < 0)
      printf("%s", SDL_GetError());

  SDL_SetRenderDrawColor(this->m_renderer, r, g, b, a);

  return true;
}


//Present all rendered sprites to display, called once per frame
bool CGraphics::Display()
{
  SDL_RenderPresent(this->m_renderer);

  return true;
}

// NOTE: This function is used to clear a z-buffer. Use ClearDisplay otherwise
bool CGraphics::Clear()
{
  //TODO:  Remove this?
  return true; 
}

// m_renderer is only in our gfx class, so we can just call a clear function on it
bool CGraphics::ClearDisplay()
{
  SDL_RenderClear(this->m_renderer);
  return true; 
}  

bool CGraphics::EnableAlphaBlending(bool Enable ) //prob needs more here for blending
{
  return true;
}

bool CGraphics::EnableAlphaTesting(bool Enable)
{
//TODO:  do we need this anywhere ?  need to find SDL equivalency
  return false;
}

SDL_Renderer* CGraphics::GetRenderer() {
  return this->m_renderer;
}

SDL_Window* CGraphics::GetWindow() {
  return this->m_window;
}

long CGraphics::GetWidth()
{
  return this->m_Width;
}

long CGraphics::GetHeight()
{
  return this->m_Height;
}


// cTexture
cTexture::cTexture()
{
  m_Graphics = NULL; //SDL_Window
  m_Surface = NULL;
  m_Texture = NULL;  //SDL_Texture
  m_Width = m_Height = 0;
  m_curAlpha = 255;  // mostly? used for font stuff

  // optional value for text, dont want to refactor things
  m_Font = NULL;
}

cTexture::~cTexture()
{
  Free();
}

//we pass in the window handler of gfx, but are not using it
// Calls SDL_LoadBMP() on Filename, loads to m_Surface, sets m_Width and m_Height
bool cTexture::Load(CGraphics *graphics, const char* Filename )
{
  Free();
  this->m_Graphics = graphics;

  // load file to surface,  get h,w , set Texture for renderer in m_texture
  //todo handle osx pathing /bundle
  this->m_Surface = IMG_Load(Filename);
  
  if (m_Surface == NULL) std::cout << SDL_GetError() << std::endl;
  SDL_SetColorKey( m_Surface, SDL_TRUE, SDL_MapRGB( m_Surface->format, 0xFF, 0, 0xFF) );

  this->m_Width = m_Surface->w;
  this->m_Height = m_Surface->h;

  // could this renderer lookup be on same line?
  SDL_Renderer *rR = this->m_Graphics->GetRenderer();
  this->m_Texture = SDL_CreateTextureFromSurface(rR, m_Surface);

  SDL_FreeSurface(m_Surface);
  return true;
}

//surface to texture?  is this even needed?
/*
bool cTexture::Create(CGraphics gfx, SDL_Texture *Texture)
{
  Free();

  return true;
}
*/

bool cTexture::Free()
{
	if(m_Texture != NULL)
  {
		SDL_DestroyTexture(m_Texture);
		m_Texture = NULL;
	}
  
  m_Graphics = NULL;
  m_Width = m_Height = 0;

  return true;
}

bool cTexture::IsLoaded()
{
  if(m_Texture == NULL)
    return false;

  return true;
}

long cTexture::GetWidth()
{
  //TODO ERROR HANDLE
  return this->m_Width;
}

long cTexture::GetHeight()
{
  //TODO ERROR HANDLE
  return this->m_Height;
}


//do we need this?  nope.  we dont store m_Surface with the texture - it gets free'd
SDL_PixelFormat* cTexture::GetFormat()
{
  /*
  if(this->m_Surface == NULL)
  {
 	  SetError( "cTexture::GetFormat - Texture is not loaded" );
	  return SDL_PixelFormat(SDL_PIXELFORMAT_UNKNOWN);
  }
  */
  return this->m_Surface->format;
}

bool cTexture::Blit(long DestX, long DestY, int SrcX, int SrcY,
                    long Width, long Height, float XScale, float YScale, float Rotation,
                    uint8_t r, uint8_t g, uint8_t b) {

  if(this->m_Texture == NULL)
  {
	  SDL_SetError( " cTexture::Blit - Texture is not loaded" );
	  return false;
  }
  
  if(this->m_Graphics == NULL)
  {
	  SDL_SetError( "cTexture::Blit - Invalid graphics interface" );
		return false;
  }
  
  // scalar values to be dest rect
  long s_width, s_height = 0;

  // override width and height to squish/stretch things if passed
  // abs is Jim's kryptonite
  (Width) ? s_width = abs(Width * XScale) : s_width = abs( (this->m_Width * XScale) ) ;
  (Height) ? s_height = abs(Height * YScale) : s_height = abs( (this->m_Height * YScale) );
  
  //s_width = m_Width;
  //s_height = m_Height;
  
  // Width/height are Long, so we typecast, rather than updating 9000 other classes
  //objRect is our "image" we are about to blit to screen
  //THIS IS THE BUG IT "STRETCHES THE TEXT", prob written this way because it us used to clip spritesheet 
  //anim frames.
  //
  // srcRect == the whole Texture Obj: width+height
  SDL_Rect objSrcRect;
  if ((Width > 0) || (Height > 0)) { 
    objSrcRect.x = SrcX;
    objSrcRect.y = SrcY;
    objSrcRect.w = (int)s_width;
    objSrcRect.h = (int)s_height; 

  } else {
    objSrcRect.x = SrcX;
    objSrcRect.y = SrcY;
    objSrcRect.w = (int)(this->m_Width);
    objSrcRect.h = (int)(this->m_Height);
  }
  //dstRect == (Width+Height * scalar)
  SDL_Rect objDstRect = { DestX, DestY, (int)s_width, (int)s_height };
  // this below works fine for text boxes
  //SDL_Rect objSrcRect = { SrcX, SrcY, (int)Width, (int)Height };
  //SDL_Rect objDstRect = { DestX, DestY, (int)Width, (int)Height };

  if (XScale < 0)
  {
    //Kludge: find the center point of texture for flip and pass it to DrawFlip()
    // as the default" behavior is not true here for center in RenderDrawEx()
    // on extra inspection, this is all probably not needed....
    // force rotate around 0,0
    SDL_Point texCenter;
    texCenter.x = s_width / 2 ;
    texCenter.y = s_height / 2 ;
    //what we DO need is to modify the dsrRect.x by width before passing to renderx because the flip draws the image wrong
    //even tho the postion is not changing internally, ie - we cause a draw/render bug , so let's fix it here...
    objDstRect.x -= s_width;
    this->m_Graphics->DrawFlip(this->m_Texture, &objSrcRect, &objDstRect, &texCenter ); 
  }
  else
  {
    this->m_Graphics->Draw(this->m_Texture, &objSrcRect, &objDstRect);
  }
  return true;
}

bool cTexture::Print(long DestX, long DestY, Uint8 a) {

  if(this->m_Texture == NULL)
  {
	  SDL_SetError( " cTexture::Blit - Texture is not loaded" );
	  return false;
  }
  
  if(this->m_Graphics == NULL)
  {
	  SDL_SetError( "cTexture::Blit - Invalid graphics interface" );
		return false;
  }

  //Width = this->m_Width;	
	//Height = this->m_Height;
  
  if(this->m_curAlpha != a) { //if the alpha changed
  SDL_SetTextureAlphaMod(this->m_Texture, a);
  }
  // Width/height are Long, so we typecast, rather than updating 9000 other classes
  //objRect is our "image" we are about to blit to screen

  // this below works fine for text boxes
  SDL_Rect objSrcRect = { 0, 0, (int)(this->m_Width), (int)(this->m_Height) };
  SDL_Rect objDstRect = { DestX, DestY, (int)(this->m_Width), (int)(this->m_Height) };

  this->m_Graphics->Draw(this->m_Texture, &objSrcRect, &objDstRect);

  return true;
}


bool cTexture::CreateFontTexture(CGraphics *Graphics, cFont *Font, const char *Text,
  uint8_t r, uint8_t g, uint8_t b)
{
  if(Graphics == NULL || Font == NULL)
  {
	  SDL_SetError( "Can't Create Font Texture" );
	  return false;
  }

  SDL_Color textColor;
  textColor.r = r;
  textColor.g = g;
  textColor.b = b;
  this->m_Graphics = Graphics;
  m_Surface = TTF_RenderText_Blended(Font->getFont(), Text, textColor);

  // store dimensions
  m_Width = m_Surface->w;
  m_Height = m_Surface->h;

  /* debugging info 
  int fontw, fonth = 0;
  fontw = m_Surface->w;
  fonth = m_Surface->h;
  
  std::cout << "h: " << fonth << "w: "<< fontw << std::endl;
  */

  SDL_Renderer *rR = this->m_Graphics->GetRenderer();
  this->m_Texture = SDL_CreateTextureFromSurface(rR, m_Surface);

  /* //destination rect to put on screen
  SDL_Rect dRect;
  
  dRect.h = m_Surface->h;
  dRect.w = m_Surface->w;
  dRect.x = 0;
  dRect.y = ;
  */ 
  if(m_Font == NULL)
  {
	  SDL_SetError( "cFont::Print - No Font" );
	  return false;
  }

  SDL_FreeSurface(m_Surface);

  return true;
}

bool cTexture::CreateFontTextureWrapped(CGraphics *Graphics, cFont *Font, const char *Text,
  uint8_t r, uint8_t g, uint8_t b, int WrapSize)
{
  if(Graphics == NULL || Font == NULL)
  {
	  SDL_SetError( "Can't Create Font Texture" );
	  return false;
  }

  SDL_Color textColor;
  textColor.r = r;
  textColor.g = g;
  textColor.b = b;

  this->m_Graphics = Graphics;
  m_Surface = TTF_RenderText_Blended_Wrapped(Font->getFont(), Text, textColor, WrapSize);

  // store dimensions
  m_Width = m_Surface->w;
  m_Height = m_Surface->h;

  /* debugging info 
  int fontw, fonth = 0;
  fontw = m_Surface->w;
  fonth = m_Surface->h;
  
  std::cout << "h: " << fonth << "w: "<< fontw << std::endl;
  */

  SDL_Renderer *rR = this->m_Graphics->GetRenderer();
  this->m_Texture = SDL_CreateTextureFromSurface(rR, m_Surface);

  /* //destination rect to put on screen
  SDL_Rect dRect;
  
  dRect.h = m_Surface->h;
  dRect.w = m_Surface->w;
  dRect.x = 0;
  dRect.y = ;
  */ 
  if(m_Font == NULL)
  {
	  SDL_SetError( "cFont::Print - No Font" );
	  return false;
  }

  SDL_FreeSurface(m_Surface);

  return true;
}

// this reads a RECT from spritesheet to blit elsewhere, ie, multiple frames an actor has, or 
// picking a different tile in a set.
// Looks currently unused???????
SDL_Point cTexture::GetSrcPoint( int a_Index, int a_FramesPerCol )
{
	SDL_Point SourcePoint;

	int Column = a_Index % a_FramesPerCol;
	int Row = a_Index / a_FramesPerCol;
	
	// Hardcoded to 32 for actors only. Change later
	SourcePoint.x = Column * 32;
	SourcePoint.y = Row * 32;

	return SourcePoint;
}

void cTexture::SetColor(SDL_Color color)
{
    if (this->m_Texture == NULL) return;  // bounce out and not crash if texture not set lol
    SDL_SetTextureColorMod(this->m_Texture, color.r, color.g, color.b);
}