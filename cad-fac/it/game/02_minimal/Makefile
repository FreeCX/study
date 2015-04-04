CXX          := g++
CFLAGS 	     := -Wall -std=c++11 $(shell pkg-config --cflags openal vorbisfile sdl2)
LFLAGS       := $(shell pkg-config --libs openal vorbisfile sdl2 SDL2_image)
target_file  := minimal_game
dest_dir 	 := ./src/
object_files := $(patsubst %.cpp, %.o, $(wildcard $(dest_dir)*.cpp))

ifeq ($(RELEASE), 1)
	CFLAGS += -O3
endif
ifeq ($(DEBUG), 1)
	CFLAGS += -ggdb -g3
endif

all: $(dest_dir)$(target_file)

$(dest_dir)$(target_file): $(object_files)
	$(CXX) $(object_files) -o $(target_file) $(LFLAGS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	-$(RM) $(target_file) $(object_files)
