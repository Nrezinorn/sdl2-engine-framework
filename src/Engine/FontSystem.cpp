#include "FontSystem.h"
#include <stdio.h> 

cFont::cFont()
{
  m_Font = NULL;
}

cFont::~cFont()
{
  Free();
}

//Create a Texture from given text, and store as SDL Texture ready to use
bool cFont::Create(std::string *Name, long Size, bool Bold, bool Italic, bool Underline, bool Strikeout)
{
  if(Name == NULL)
  {
	  SDL_SetError( "cFont::Create - No Font Specified" );
	  return false;
  }
  
  #if __APPLE__
    fp = new std::string("/System/Library/Fonts/Supplemental/Times New Roman.ttf");
  #endif

  #if _WIN64
    fp = new std::string("C://Windows//Fonts//times.ttf");
  #endif
  
  //todo:  use the name to load the font every time
  //enjoy this kludge for now
  if (Name != fp)  fp = Name;

  //first time loading TTF?  Init TTF lazily
  if(!TTF_WasInit())  TTF_Init();

  //reset flags to none, due to font randomly glitching flags
  m_FontFlags = 0;

  if(Bold)  m_FontFlags |= TTF_STYLE_BOLD;
  if(Italic)  m_FontFlags |= TTF_STYLE_ITALIC;
  if(Underline)  m_FontFlags |= TTF_STYLE_UNDERLINE;
  if(Strikeout)  m_FontFlags |= TTF_STYLE_STRIKETHROUGH;

  //m_Font = TTF_OpenFont(this->fp + *Name + '.ttf', Size);
  m_Font = TTF_OpenFont(fp->c_str(), Size);

  TTF_SetFontStyle(m_Font, m_FontFlags);
  
  // Create the font objec
  if (m_Font == NULL)  {
	  SDL_SetError( "cFont::Create - Couldn't create font object" );
	  return false;
  }
  
  return true;
}

TTF_Font* cFont::getFont() {
  return (this->m_Font);
}

bool cFont::Free()
{
  TTF_CloseFont (m_Font);
  m_Font = NULL;
  return true;
}
