#include "asteroid.hpp"

AsteroidSystem::AsteroidSystem( const int width, const int height, const int asteroid_count, const int segment_count ) {
    const float delta = M_PI / segment_count;

    srand( time( nullptr ) );
    this->asteroid_count = asteroid_count;
    this->segment_count = segment_count;
    segments = new float [segment_count * 2];
    pos = new int [segment_count * 2];
    dist = new float [asteroid_count * segment_count * 2];
    for ( int i = 0; i < asteroid_count; i++ ) {
        for ( int j = 0; j < segment_count * 2; j += 2 ) {
            dist[i*segment_count*2+j+0] = ( 1.0f + 0.04f * ( rand() % 10 - 5 ) );
            dist[i*segment_count*2+j+1] = ( 1.0f + 0.04f * ( rand() % 10 - 5 ) );
        }
    }
    for ( int i = 0; i < segment_count * 2; i += 2 ) {
        segments[i+0] = cos( i * delta );
        segments[i+1] = sin( i * delta );
    }
}

AsteroidSystem::~AsteroidSystem() {
    asteroids.clear();
    delete[] segments;
    delete[] pos;
}

void AsteroidSystem::rand_append( void ) {
    asteroid_t a;
    a.radius = rand() % 32 + 16;
    a.rotate = ( rand() % 100 + 1 ) / 3000.0f;
    a.life   = 1;
    a.v      = vec2( ( rand() % 100 - 50 ) / 20.0f, ( rand() % 100 - 50 ) / 20.0f );
    a.p      = vec2( -a.radius, -a.radius );
    a.index  = rand() % asteroid_count;
    asteroids.push_back( a );
}

void AsteroidSystem::append( const vec2 & p, const vec2 & v, const int radius ) {
    asteroids.push_back( { p, v, radius, 1, rand() % asteroid_count, 0.0f, 0.0f } );
}

void AsteroidSystem::step( const int width, const int height ) {
    asteroids.erase( std::remove_if( asteroids.begin(), asteroids.end(), 
        []( const asteroid_t & a ) { return a.life <= 0; } ), asteroids.end()
    );
    for ( auto & a : asteroids ) {
        const int inv_zone = ceil( a.radius );
        a.p -= a.v;
        if ( a.p.x > width + inv_zone ) {
            a.p.x = -inv_zone;
        } else if ( a.p.x < -inv_zone ) {
            a.p.x = width + inv_zone;
        }
        if ( a.p.y > height + inv_zone ) {
            a.p.y = -inv_zone;
        } else if ( a.p.y < -inv_zone ) {
            a.p.y = height + inv_zone;
        }
        a.angle = _fmod( a.angle + a.rotate + M_PI, 2 * M_PI ) - M_PI;
    }
    if ( asteroids.size() > 0 ) {
        for ( size_t i = 0; i < asteroids.size() - 1; i++ ) {
            for ( size_t j = i; j < asteroids.size(); j++ ) {
                collide( i, j );
            }
        }
    }
}

void AsteroidSystem::draw( DrawSystem & draw ) {
    draw.set_coloru( COLOR_WHITE );
    for ( size_t j = 0; j < asteroids.size(); j++ ) {
        const auto & a = asteroids[j];
        for ( int i = 0; i < segment_count * 2; i += 2 ) {
            const float x = segments[i+0] * dist[a.index*segment_count*2+i+0] * a.radius;
            const float y = segments[i+1] * dist[a.index*segment_count*2+i+1] * a.radius;
            pos[i+0] = round( a.p.x + x * cos( a.angle ) - y * sin( a.angle ) );
            pos[i+1] = round( a.p.y + x * sin( a.angle ) + y * cos( a.angle ) );
        }
        for ( int i = 0; i < segment_count * 2; i += 2 ) {
            if ( i == ( segment_count - 1 ) * 2 ) {
                draw.aaline( pos[i+0], pos[i+1], pos[0], pos[1] );
            } else {
                draw.aaline( pos[i+0], pos[i+1], pos[i+2], pos[i+3] );
            }
        }
    }
    draw.set_coloru( COLOR_BLACK );
}

void AsteroidSystem::collide( int i, int j ) {
    vec2 & v1 = asteroids[i].v, & v2 = asteroids[j].v;
    vec2 & p1 = asteroids[i].p, & p2 = asteroids[j].p;
    vec2 p = p2 - p1;
    float d = ( asteroids[i].radius + asteroids[j].radius ) - p.length();

    if ( d >= 0 ) {
        vec2 n = p.norm();
        std::swap( v1, v2 );
        p1 -= n * d; p2 += n * d;
    }
}

size_t AsteroidSystem::count( void ) const {
    return asteroids.size();
}

asteroid_v & AsteroidSystem::get_vector( void ) {
    return asteroids;
}