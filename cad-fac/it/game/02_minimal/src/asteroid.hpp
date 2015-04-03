#pragma once
#include <ctime>
#include <vector>
#include "math.hpp"
#include "draw.hpp"

typedef struct {
    vec2 p, v;
    int radius;
    int life;
    int index;
    float angle, rotate;
} asteroid_t;

typedef std::vector< asteroid_t > asteroid_v; 

class AsteroidSystem {
public:
    const int asteroid_eps = 8;
    AsteroidSystem( const int width, const int height, const int asteroid_count, const int segment_count );
    ~AsteroidSystem();
    void rand_append( void );
    void append( const vec2 & p, const vec2 & v, const int radius );
    void step( const int width, const int height );
    void draw( DrawSystem & draw );
    size_t count( void ) const;
    asteroid_v & get_vector( void );
private:
    void collide( int i, int j );
    asteroid_v asteroids;
    int asteroid_count;
    int segment_count;
    float * segments;
    int * pos;
    float * dist;
};