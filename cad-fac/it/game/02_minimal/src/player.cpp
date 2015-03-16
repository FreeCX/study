#include "player.hpp"

void Player::draw( void ) {
    const int a = 32, b = 16;
    //            0    1        2        3    4  5      6        7
    int pos[] = { x, y - a, x - a / 2, y + b, x, y, x + a / 2, y + b };

    for ( int i = 0; i < 8; i += 2 ) {
        float x = pos[i+0] - this->x; 
        float y = pos[i+1] - this->y;
        pos[i+0] = this->x + round( x * cos( angle ) - y * sin( angle ) );
        pos[i+1] = this->y + round( x * sin( angle ) + y * cos( angle ) );
    }
    set_coloru( COLOR_WHITE );
    draw_aaline( pos[0], pos[1], pos[2], pos[3] );
    draw_aaline( pos[2], pos[3], pos[4], pos[5] );
    draw_aaline( pos[4], pos[5], pos[6], pos[7] );
    draw_aaline( pos[6], pos[7], pos[0], pos[1] );
    set_coloru( COLOR_BLACK );
}