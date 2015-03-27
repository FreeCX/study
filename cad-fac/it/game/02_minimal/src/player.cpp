#include "player.hpp"

void Player::set_position( int x, int y ) { 
    this->x = x; this->y = y; 
}

void Player::set_angle( float angle ) { 
    this->angle = angle; 
}

void Player::add_angle( float add ) { 
    angle = _fmod( angle + add + M_PI, 2 * M_PI ) - M_PI;
}

void Player::add_velocity( int add ) {
    if ( velocity < velocity_max ) {
        velocity += add; 
    }
}

void Player::add_life( short add ) { 
    if ( life + add <= life_max ) {
        life += add; 
    }
}

char Player::get_life( void ) { 
    return life; 
}

void Player::step( const int width, const int heigth ) {
    static const int inv_zone = a;
    static short counter = 0;

    x -= round( velocity * cos( angle + M_PI / 2.0f ) );
    y -= round( velocity * sin( angle + M_PI / 2.0f ) );
    if ( x > width + inv_zone ) {
        x = -inv_zone;
    } else if ( x < -inv_zone ) {
        x = width + inv_zone;
    }
    if ( y > heigth + inv_zone ) {
        y = -inv_zone;
    } else if ( y < -inv_zone ) {
        y = heigth + inv_zone;
    }
    if ( velocity > 0 && counter % 32 == 0 ) {
        velocity--;
    }
    counter++;
}

void Player::draw( DrawSystem & draw ) {
    //            0    1    2      3  4  5  6      7  8   9
    int pos[] = { 0, - a, - a / 2, b, 0, 0, a / 2, b, 0, -a };

    draw.set_coloru( COLOR_WHITE );
    for ( int i = 0; i < max_length; i += 2 ) {
        const float x = pos[i+0];
        const float y = pos[i+1];
        pos[i+0] = this->x + round( x * cos( angle ) - y * sin( angle ) );
        pos[i+1] = this->y + round( x * sin( angle ) + y * cos( angle ) );
    }
    for ( int i = 0; i < max_length - 2; i += 2 ) {
        draw.aaline( pos[i+0], pos[i+1], pos[i+2], pos[i+3] );
    }
    draw.set_coloru( COLOR_BLACK );
}