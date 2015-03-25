#include "asteroid.hpp"

void Asteroid::init( const int segment_count, const float radius ) {
    x = y = angle = rotate = vx = vy = 0;
    sg_count = segment_count;
    segments = new int [sg_count * 2 + 1];
    pos = new int [sg_count * 2 + 1];
    const float delta = M_PI / sg_count;
    for ( int i = 0; i < sg_count * 2; i += 2 ) {
        segments[i+0] = radius * cos( i * delta ) * ( 1.0f + 0.05f * ( rand() % 10 - 5 ) );
        segments[i+1] = radius * sin( i * delta ) * ( 1.0f + 0.05f * ( rand() % 10 - 5 ) );
    }
}

Asteroid::~Asteroid() {
    delete[] segments;
    delete[] pos;
}

void Asteroid::set_speed( int vx, int vy ) {
    this->vx = vx; this->vy = vy;
}

void Asteroid::set_position( int x, int y ) {
    this->x = x; this->y = y;
}

void Asteroid::set_angle( float a ) {
    angle = a;
}

void Asteroid::set_rotation_speed( float w ) {
    rotate = w;
}

void Asteroid::step( void ) {
    x -= vx; y -= vy;
    if ( x > 690 ) {
        x = -50;
    } else if ( x < -50 ) {
        x = 690;
    }
    if ( y > 690 ) {
        y = -50;
    } else if ( y < -50 ) {
        y = 690;
    }
    angle = _fmod( angle + rotate + M_PI, 2 * M_PI ) - M_PI;
}

void Asteroid::draw( DrawSystem & draw ) {
    draw.set_coloru( COLOR_WHITE );
    for ( int i = 0; i < sg_count * 2; i += 2 ) {
        const float x = segments[i+0];
        const float y = segments[i+1];
        pos[i+0] = this->x + round( x * cos( angle ) - y * sin( angle ) );
        pos[i+1] = this->y + round( x * sin( angle ) + y * cos( angle ) );
    }
    for ( int i = 0; i < sg_count * 2; i += 2 ) {
        if ( i == ( sg_count - 1 ) * 2 ) {
            draw.aaline( pos[i+0], pos[i+1], pos[0], pos[1] );
        } else {
            draw.aaline( pos[i+0], pos[i+1], pos[i+2], pos[i+3] );
        }
    }
    draw.set_coloru( COLOR_BLACK );
}