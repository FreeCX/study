#pragma once
#include "math.hpp"
#include "draw.hpp"

class Player {
public:
    const char life_max = 10;
    const float velocity_max = 10.0f;
    const int a = 32, b = 16;
    const int max_length = 10;

    Player() : p( vec2( 0.0f, 0.0f ) ), life( 3 ), velocity( 0.0f ), angle( 0.0f ) {}
    void set_position( int x, int y );
    void set_angle( float angle );
    float get_x( void ) { return p.x; }
    float get_y( void ) { return p.y; }
    float get_velocity( void ) { return velocity; }
    float get_angle( void ) { return angle; }
    void add_angle( float add );
    void add_velocity( int add );
    void add_life( short add );
    char get_life( void );
    void step( const int width, const int height );
    void draw( DrawSystem & draw );
private:
    vec2 p;
    char life;
    float velocity, angle;
};