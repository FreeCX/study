CXX         := g++
CFLAGS 	    := -Wall -std=c++11
CFLAGS_SDL  := $(CFLAGS) $(shell sdl2-config --cflags)
LFLAGS_SDL  := $(shell sdl2-config --libs) -lSDL2_image

ifeq ($(shell uname -s),Linux)
	LFLAGS_GLUT := -lGL -lGLU -lglut -lm
else
	LFLAGS_GLUT := -lopengl32 -lglu32 -lfreeglut -lm
endif

target_one   := glut_init
target_two   := sdl2_init
dest_dir     := ./src/

all:
	$(CXX) $(CFLAGS) $(dest_dir)$(target_one).cpp -o $(target_one) $(LFLAGS_GLUT)
	$(CXX) $(CFLAGS_SDL) $(dest_dir)$(target_two).cpp -o $(target_two) $(LFLAGS_SDL)

clean:
	-$(RM) $(target_one) $(target_two)
