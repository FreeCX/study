#pragma once
#include <cmath>
#include <ctime>
#include <vector>
#include "math.hpp"
#include "draw.hpp"

typedef struct {
    vec2 p;
    vec2 v;
    int radius;
    float angle, rotate;
} asteroid_t;

class AsteroidSystem {
public:
    AsteroidSystem( const int width, const int height, const int asteroid_count, const int segment_count );
    ~AsteroidSystem();
    void step( const int width, const int height );
    void draw( DrawSystem & draw );
private:
    void collide( int i, int j );
    std::vector< asteroid_t > asteroids;
    int asteroid_count;
    int segment_count;
    float * segments;
    int * pos;
    float * dist;
};