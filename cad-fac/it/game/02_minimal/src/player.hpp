#pragma once
#include <SDL2/SDL.h>
#include <cmath>
#include "draw.hpp"

class Player {
public:
    Player( void ) { x = y = vx = vy = angle = 0; }
    void set_position( int x, int y ) { this->x = x; this->y = y; }
    void set_angle( float angle ) { this->angle = angle; }
    void add_angle( float add ) { this->angle += add; }
    void draw( void );
private:
    int x, y;
    float vx, vy, angle;
};