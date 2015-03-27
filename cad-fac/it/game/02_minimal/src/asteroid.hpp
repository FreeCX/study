#pragma once
#include <cmath>
#include <ctime>
#include <vector>
#include "math.hpp"
#include "draw.hpp"

typedef struct {
    int x, y;
    int vx, vy;
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
    std::vector< asteroid_t > asteroids;
    int asteroid_count;
    int segment_count;
    float * segments;
    int * pos;
    float * dist;
};