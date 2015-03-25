#include "draw.hpp"

DrawSystem::DrawSystem( SDL_Renderer * renderer, const size_t segments ) {
    this->segments = segments;
    render = renderer;
    coords = new float [segments * 2];
    for ( size_t i = 0; i < segments * 2; i += 2 ) {
        coords[i+0] = cos( 0.5f * i / M_PI );
        coords[i+1] = sin( 0.5f * i / M_PI );
    }
}

DrawSystem::~DrawSystem() {
    delete[] coords;
}

void DrawSystem::set_render( SDL_Renderer * renderer ) {
    render = renderer;
}

Uint32 DrawSystem::get_coloru( void ) {
    SDL_GetRenderDrawColor( render, &red, &green, &blue, nullptr );
    return ( red << 16 ) + ( green << 8 ) + blue;
}

int DrawSystem::set_coloru( Uint32 color ) {
    red = ( color >> 16 );
    green = ( ( color >> 8 ) & 0xff );
    blue = ( color & 0xff );
    return SDL_SetRenderDrawColor( render, red, green, blue, 0xff );
}

int DrawSystem::set_color3u( Uint8 red, Uint8 green, Uint8 blue ) {
    return SDL_SetRenderDrawColor( render, red, green, blue, 0xff );
}

int DrawSystem::set_color4u( Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha ) {
    return SDL_SetRenderDrawColor( render, red, green, blue, alpha );
}

int DrawSystem::aaline( int x1, int y1, int x2, int y2 ) {
    Uint32 intshift, erracc, erradj, erracctmp, wgt;
    int dx, dy, tmp, xdir, y0p1, x0pxdir, result;
    Sint32 xx0, yy0, xx1, yy1;
    Uint8 r, g, b, a;

    result = SDL_GetRenderDrawColor( render, &r, &g, &b, &a );
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
        return SDL_RenderDrawLine( render, x1, y1, x2, y2 );
    }
    xdir = 1;
    if ( dx < 0 ) {
        xdir = -1;
        dx = -dx;
    }
    erracc = 0;
    intshift = 24;
    result |= set_color3u( r, g, b );
    result |= SDL_RenderDrawPoint( render, x1, y1 );
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
            result |= SDL_RenderDrawPoint( render, xx0, yy0 );
            result |= set_color4u( r, g, b, wgt );
            result |= SDL_RenderDrawPoint( render, x0pxdir, yy0 );
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
            result |= SDL_RenderDrawPoint( render, xx0, yy0 );
            result |= set_color4u( r, g, b, wgt );
            result |= SDL_RenderDrawPoint( render, xx0, y0p1 );
        }
    }
    return result;
}

int DrawSystem::circle( int x, int y, int r ) {
    int result = 0;

    // FIX THIS
    for ( size_t i = 0; i < segments * 2; i += 2 ) {
        if ( i != (segments-1) * 2 ) {
            result |= aaline( 
                x + r * coords[i+0], y + r * coords[i+1],
                x + r * coords[i+2], y + r * coords[i+3] 
            );
        } else {
            result |= aaline( 
                x + r * coords[i+0], y + r * coords[i+1],
                x + r * coords[0], y + r * coords[1] 
            );
        }
    }
}