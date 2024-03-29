CXX = g++
CXXFLAGS=-g -fpermissive -DDEBUG -Dmain=SDL_main
LDFLAGS= -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

PROG=demo

#give up on object files in a folder of their own for now
OBJDIR=obj

src = $(wildcard src/*.cpp) \
	$(wildcard src/Engine/*.cpp)
obj = $(src:.cpp=.o)
dep = $(obj:.o=.d)

#http://nuclear.mutantstargoat.com/articles/make/  
# buy this guy a beer or soda

all:  $(PROG) 

$(PROG): $(obj)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(obj)
	rm -f demo
