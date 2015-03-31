#pragma once
#include <vector>
#include "math.hpp"
#include "draw.hpp"
#include "player.hpp"

typedef struct {
    vec2 p;
    short life;
    float angle, velocity;
} bullet_t;

typedef std::vector< bullet_t > bullet_v;

class BulletSystem {
public:
    BulletSystem( const float velocity, const short life, const short radius );
    ~BulletSystem();
    void append( Player & player );
    void step( const int width, const int height );
    void draw( DrawSystem & draw );
    bullet_v & get_vector( void );
private:
    bullet_v bullets;
    float max_velocity = 5.0f;
    short max_life = 20;
    short max_radius = 4;
};