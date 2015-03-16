CXX          := g++
CFLAGS 	     := -Wall -std=c++11 $(CFLAGS) $(shell sdl2-config --cflags)
LFLAGS       := $(shell sdl2-config --libs) -lSDL2_image
target_file  := minimal_game
dest_dir 	 := ./src/
object_files := $(patsubst %.cpp, %.o, $(wildcard $(dest_dir)*.cpp))

all: $(dest_dir)$(target_file)

$(dest_dir)$(target_file): $(object_files)
	$(CXX) $(object_files) -o $(target_file) $(LFLAGS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	-$(RM) $(prog_name) $(object_files)
