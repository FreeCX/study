#pragma once
#include <SDL2/SDL.h>
#include <cmath>
#include "math.hpp"
#include "draw.hpp"

class Player {
public:
    const char life_max = 8;
    const float velocity_max = 10.0f;

    Player() : life( 3 ), x( 0 ), y( 0 ), velocity( 0.0f ), angle( 0.0f ) {}
    void set_position( int x, int y );
    void set_angle( float angle );
    void add_angle( float add );
    void add_velocity( int add );
    void add_life( short add );
    char get_life( void );
    void step( void );
    void draw( void );
private:
    char life;
    int x, y;
    float velocity, angle;
};