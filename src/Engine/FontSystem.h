#ifndef FONT_SYSTEM_H
#define FONT_SYSTEM_H

#include <SDL2/SDL.h>
#if __APPLE__
#include <SDL2_ttf/SDL_ttf.h>
#endif
#if __WIN32__ || __LINUX__
#include <SDL2/SDL_ttf.h>
#endif
#include <string>

using std::string;

extern const char *FONT_PATH;

class cFont
{
  private:
    std::string *fp;
    TTF_Font *m_Font;
    bool m_Centered;
    uint8_t m_FontFlags;

  public:
    cFont();
    ~cFont();

    bool Create(std::string *Name, long Size = 16,
				bool Bold = false, bool Italic = false,
				bool Underline = false, bool Strikeout = false);
    
    TTF_Font* getFont();

    bool Free();

};
#endif
