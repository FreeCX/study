#pragma once
#include <SDL2/SDL.h>
#include <cmath>
#include "math.hpp"
#include "draw.hpp"

class Asteroid {
public:
    Asteroid() {}
    ~Asteroid();
    void init( const int segment_count, const float radius );
    void set_speed( int vx, int vy );
    void set_position( int x, int y );
    void set_angle( float a );
    void set_rotation_speed( float w );
    void step( void );
    void draw( void );
private:
    int x, y, vx, vy;
    float angle, rotate;
    int sg_count;
    int * segments, * pos;
};