#pragma once
#include <SDL2/SDL.h>

enum COLOR {
    COLOR_WHITE     = 0xffffff,
    COLOR_BLACK     = 0x000000,
    COLOR_RED       = 0xff0000,
    COLOR_GREEN     = 0x00ff00,
    COLOR_BLUE      = 0x0000ff,
    COLOR_YELLOW    = 0xffff00,
    COLOR_MAGENTA   = 0xff00ff,
};

void draw_init( SDL_Renderer * render );
Uint32 get_coloru( void );
int set_coloru( Uint32 color );
int set_color3u( Uint8 red, Uint8 green, Uint8 blue );
int set_color4u( Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha );
int draw_aaline( int x1, int y1, int x2, int y2 );