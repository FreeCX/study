#pragma once
#include "asteroid.hpp"
#include "draw.hpp"
#include "math.hpp"

class Player {
public:
    const char life_max = 10;
    const float velocity_max = 10.0f;
    const int a = 32, b = 16;
    const int max_length = 10;

    Player() : p( vec2( 0.0f, 0.0f ) ), life( 3 ), velocity( 0.0f ), angle( 0.0f ) {}
    void set_position( int x, int y );
    void set_angle( float angle );
    float get_x( void ) const { return p.x; }
    float get_y( void ) const { return p.y; }
    float get_velocity( void ) const { return velocity; }
    float get_angle( void ) const { return angle; }
    void add_angle( float add );
    void add_velocity( int add );
    void add_life( signed short add );
    char get_life( void ) const;
    void step( const int width, const int height );
    void draw( DrawSystem & draw );
    bool collider( AsteroidSystem & asteroids );
private:
    vec2 p;
    short life;
    float velocity, angle;
};