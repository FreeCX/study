#include "player.hpp"

void Player::step( void ) {
    static short counter = 0;

    x -= round( velocity * cos( angle + M_PI / 2.0f ) );
    y -= round( velocity * sin( angle + M_PI / 2.0f ) );
    if ( x > 660 ) {
        x = -20;
    } else if ( x < -20 ) {
        x = 660;
    }
    if ( y > 660 ) {
        y = -20;
    } else if ( y < -20 ) {
        y = 660;
    }
    if ( velocity > 0 && counter % 32 == 0 ) {
        velocity--;
    }
    counter++;
}

void Player::draw( void ) {
    const int a = 32, b = 16;
    const int max_length = 10;
    //            0    1    2      3  4  5  6      7  8   9
    int pos[] = { 0, - a, - a / 2, b, 0, 0, a / 2, b, 0, -a };

    set_coloru( COLOR_WHITE );
    for ( int i = 0; i < max_length; i += 2 ) {
        const float x = pos[i+0];
        const float y = pos[i+1];
        pos[i+0] = this->x + round( x * cos( angle ) - y * sin( angle ) );
        pos[i+1] = this->y + round( x * sin( angle ) + y * cos( angle ) );
    }
    set_coloru( COLOR_WHITE );
    for ( int i = 0; i < max_length - 2; i += 2 ) {
        draw_aaline( pos[i+0], pos[i+1], pos[i+2], pos[i+3] );
    }
    set_coloru( COLOR_BLACK );
}