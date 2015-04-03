#include "player.hpp"

void Player::set_position( int x, int y ) {
    p = vec2( x, y ); 
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

    p.x -= velocity * cos( angle + M_PI / 2.0f );
    p.y -= velocity * sin( angle + M_PI / 2.0f );
    if ( p.x > width + inv_zone ) {
        p.x = -inv_zone;
    } else if ( p.x < -inv_zone ) {
        p.x = width + inv_zone;
    }
    if ( p.y > heigth + inv_zone ) {
        p.y = -inv_zone;
    } else if ( p.y < -inv_zone ) {
        p.y = heigth + inv_zone;
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
        pos[i+0] = round( p.x + x * cos( angle ) - y * sin( angle ) );
        pos[i+1] = round( p.y + x * sin( angle ) + y * cos( angle ) );
    }
    for ( int i = 0; i < max_length - 2; i += 2 ) {
        draw.aaline( pos[i+0], pos[i+1], pos[i+2], pos[i+3] );
    }
    draw.set_coloru( COLOR_BLACK );
}

bool collide( vec2 p1, vec2 p2, asteroid_t & ast ) {
    // написать функцию проверки пересечения отрезка и круга
    return false;
}

bool Player::collider( AsteroidSystem & asteroids ) {
    vec2 p1, p2, p3, p4;
    bool status = false;

    p1 = p + vec2( 0.0f, -a ).rot( angle );
    p2 = p + vec2( -a / 2.0f, b ).rot( angle );
    p3 = p;
    p4 = p + vec2( a / 2.0f, b ).rot( angle );
    for ( auto & ast : asteroids.get_vector() ) {
        status = collide( p1, p2, ast ) | collide( p2, p3, ast ) | 
                 collide( p3, p4, ast ) | collide( p4, p1, ast );
        if ( status ) {
            return status;
        }
    }
    return false;
}