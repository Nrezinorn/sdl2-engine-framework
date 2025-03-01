CXX = g++
CXXFLAGS = -w -Wall -g -DDEBUG
LDFLAGS :=
PROG :=
CMD_CLEAN :=

PROG_EXE = demo

ifeq ($(OS),Windows_NT)
PROG = ${PROG_EXE}.exe
else
# I use .bin on non windows systems
PROG = ${PROG_EXE}.bin
endif

all:  $(PROG)

# https://gist.github.com/sighingnow/deee806603ec9274fd47
ifeq ($(OS),Windows_NT)
#@echo "Building for Windows"

# Set Extra Flags here, I use SDL2 mostly, so here are my MSYS2 windows presets
CXXFLAGS += -fpermissive -IC:\\msys64\\mingw64\\include -LC:\\msys64\\mingw64\\lib
LDFLAGS += -mwindows -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image 
# -lSDL2_ttf
CMD_CLEAN = del /f /s $(obj)
else
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
#@echo "Building for Linux"
CXXFLAGS += -fpermissive `pkg-config freetype2 --cflags`
# More SDL2 Related flags
LDFLAGS += `/usr/bin/pkg-config --libs SDL2_mixer SDL2_image SDL2_ttf freetype2`
CMD_CLEAN = rm -fv $(obj)
endif
ifeq ($(UNAME_S),Darwin)
#@echo "Building for Mac"
CXXFLAGS += -F/Library/Frameworks
LDFLAGS= -framework cocoa
# SDL2 Frameworks used on mac 1
LDFLAGS= -framework SDL2 -framework SDL2_mixer -framework SDL2_image -framework cocoa -rpath /Library/Frameworks
CMD_CLEAN = rm -f $(obj)
endif
endif

#give up on object files in a folder of their own for now
OBJDIR=obj

src = $(wildcard src/*.cpp src/Engine/*.cpp )
obj = $(src:.cpp=.o)
dep = $(obj:.o=.d)

#http://nuclear.mutantstargoat.com/articles/make/  
# buy this guy a beer or soda

$(PROG): $(obj)
#@echo "${CXXFLAGS} ${LDFLAGS}"
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	@${CMD_CLEAN}
