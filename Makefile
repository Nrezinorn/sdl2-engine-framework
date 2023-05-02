
CXX = g++
CXXFLAGS=-g -fpermissive -DDEBUG -IC:\\msys64\\mingw64\\include -LC:\\msys64\\mingw64\\lib -Dmain=SDL_main
LDFLAGS= -lmingw32 -mwindows -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

PROG=demo

#give up on object files in a folder of their own for now
OBJDIR=obj

src = $(wildcard src/*.cpp) \
	$(wildcard src/Engine/*.cpp)
obj = $(SOURCES:.cpp=.o)
dep = $(obj:.o=.d)

#http://nuclear.mutantstargoat.com/articles/make/  
# buy this guy a beer or soda

all:  $(PROG) 

$(PROG): $(obj)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	del /f /s $(obj)