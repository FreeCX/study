#pragma once
#include <SDL2/SDL.h>
#include <cmath>
#include "draw.hpp"

class Player {
public:
    Player( void ) : x( 0 ), y( 0 ), velocity( 0.0f ), angle( 0.0f ) {}
    void set_position( int x, int y ) { this->x = x; this->y = y; }
    void set_angle( float angle ) { this->angle = angle; }
    void add_angle( float add ) { angle += add; }
    void add_velocity( int add ) {
        if ( velocity < velocity_max ) {
            velocity += add; 
        }
    }
    void step( void );
    void draw( void );
private:
    int x, y;
    float velocity, angle;
    const float velocity_max = 10.0f;
};