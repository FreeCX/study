#pragma once
#include <SDL2/SDL.h>
#include "math.hpp"

enum COLOR {
    COLOR_WHITE     = 0xffffff,
    COLOR_BLACK     = 0x000000,
    COLOR_RED       = 0xff0000,
    COLOR_GREEN     = 0x00ff00,
    COLOR_BLUE      = 0x0000ff,
    COLOR_YELLOW    = 0xffff00,
    COLOR_MAGENTA   = 0xff00ff,
};

class DrawSystem {
public:
    DrawSystem( SDL_Renderer * renderer, const size_t segments );
    ~DrawSystem();
    void set_render( SDL_Renderer * renderer );
    Uint32 get_coloru( void );
    int set_coloru( Uint32 color );
    int set_color3u( Uint8 red, Uint8 green, Uint8 blue );
    int set_color4u( Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha );
    int circle( int x, int y, int r );
    int aaline( int x1, int y1, int x2, int y2 );
private:
    SDL_Renderer * render;
    Uint8 red, green, blue, alpha;
    float * coords;
    size_t segments;
};

inline void game_send_error( const char * buffer, int code ) {
    SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error", buffer, nullptr );
    if ( code != ERROR_PROBLEM ) {
        exit( code );
    }
}