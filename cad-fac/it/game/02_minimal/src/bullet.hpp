#pragma once
#include <cmath>
#include <algorithm>
#include <vector>
#include "draw.hpp"
#include "player.hpp"

typedef struct {
    int x, y;
    short life;
    float angle, velocity;
} bullet_t;

class BulletSystem {
public:
    BulletSystem( const float velocity, const short life, const short radius );
    ~BulletSystem();
    void append( Player & player );
    void step( const int width, const int height );
    void draw( DrawSystem & draw );
private:
    std::vector< bullet_t > bullet;
    float max_velocity = 5.0f;
    short max_life = 20;
    short max_radius = 4;
};