#include "draw.hpp"

SDL_Renderer * _render = nullptr;

void draw_init( SDL_Renderer * render ) {
    _render = render;
}

Uint32 get_coloru( void ) {
    Uint8 r, g, b;

    SDL_GetRenderDrawColor( _render, &r, &g, &b, nullptr );
    return ( r << 16 ) + ( g << 8 ) + b;
}

int set_coloru( Uint32 color ) {
    Uint8 r, g, b;

    r = ( color >> 16 );
    g = ( ( color >> 8 ) & 0xff );
    b = ( color & 0xff );
    return SDL_SetRenderDrawColor( _render, r, g, b, 0xff );
}

int set_color3u( Uint8 red, Uint8 green, Uint8 blue ) {
    return SDL_SetRenderDrawColor( _render, red, green, blue, 0xff );
}

int set_color4u( Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha ) {
    return SDL_SetRenderDrawColor( _render, red, green, blue, alpha );
}

int draw_aaline( int x1, int y1, int x2, int y2 ) {
    Uint32 intshift, erracc, erradj, erracctmp, wgt;
    int dx, dy, tmp, xdir, y0p1, x0pxdir, result;
    Sint32 xx0, yy0, xx1, yy1;
    Uint8 r, g, b, a;

    result = SDL_GetRenderDrawColor( _render, &r, &g, &b, &a );
    xx0 = x1; yy0 = y1;
    xx1 = x2; yy1 = y2;
    if ( yy0 > yy1 ) {
        tmp = yy0; yy0 = yy1;
        yy1 = tmp; tmp = xx0;
        xx0 = xx1; xx1 = tmp;
    }
    dx = xx1 - xx0;
    dy = yy1 - yy0;
    if ( dx == 0 || dy == 0 ) {
        return SDL_RenderDrawLine( _render, x1, y1, x2, y2 );
    }
    xdir = 1;
    if ( dx < 0 ) {
        xdir = -1;
        dx = -dx;
    }
    erracc = 0;
    intshift = 24;
    result |= set_color3u( r, g, b );
    result |= SDL_RenderDrawPoint( _render, x1, y1 );
    if ( dy > dx ) {
        erradj = ( ( dx << 16 ) / dy ) << 16;
        x0pxdir = xx0 + xdir;
        while ( --dy ) {
            erracctmp = erracc;
            erracc += erradj;
            if ( erracc <= erracctmp ) {
                xx0 = x0pxdir;
                x0pxdir += xdir;
            }
            yy0++;
            wgt = ( erracc >> intshift ) & 255;
            result |= set_color4u( r, g, b, 255 - wgt );
            result |= SDL_RenderDrawPoint( _render, xx0, yy0 );
            result |= set_color4u( r, g, b, wgt );
            result |= SDL_RenderDrawPoint( _render, x0pxdir, yy0 );
        }
    } else {
        erradj = ( ( dy << 16 ) / dx ) << 16;
        y0p1 = yy0 + 1;
        while ( --dx ) {
            erracctmp = erracc;
            erracc += erradj;
            if ( erracc <= erracctmp ) {
                yy0 = y0p1;
                y0p1++;
            }
            xx0 += xdir;
            wgt = ( erracc >> intshift ) & 255;
            result |= set_color4u( r, g, b, 255 - wgt );
            result |= SDL_RenderDrawPoint( _render, xx0, yy0 );
            result |= set_color4u( r, g, b, wgt );
            result |= SDL_RenderDrawPoint( _render, xx0, y0p1 );
        }
    }
    return result;
}