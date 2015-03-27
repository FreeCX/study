#pragma once
#include <cmath>
#include "math.hpp"
#include "draw.hpp"

class Player {
public:
    const char life_max = 8;
    const float velocity_max = 10.0f;
    const int a = 32, b = 16;
    const int max_length = 10;

    Player() : life( 3 ), x( 0 ), y( 0 ), velocity( 0.0f ), angle( 0.0f ) {}
    void set_position( int x, int y );
    void set_angle( float angle );
    int get_x( void ) { return x; }
    int get_y( void ) { return y; }
    float get_velocity( void ) { return velocity; }
    float get_angle( void ) { return angle; }
    void add_angle( float add );
    void add_velocity( int add );
    void add_life( short add );
    char get_life( void );
    void step( void );
    void draw( DrawSystem & draw );
private:
    char life;
    int x, y;
    float velocity, angle;
};