#include "bullet.hpp"

BulletSystem::BulletSystem( const float velocity, const short life, const short radius ) {
    max_velocity = velocity;
    max_life = life;
    max_radius = radius;
}

BulletSystem::~BulletSystem() {
    bullet.clear();
}

void BulletSystem::append( Player & player ) {
    float angle = player.get_angle();
    vec2 p;
    
    p = vec2( player.get_x() + player.a * sin( angle ), player.get_y() - player.a * cos( angle ) );
    bullet.push_back( { p, max_life, angle, max_velocity + player.get_velocity() } );
}

void BulletSystem::step( const int width, const int height ) {
    const int inv_zone = 20;

    for ( auto & b : bullet ) {
        b.p.x -= b.velocity * cos( b.angle + M_PI / 2.0f );
        b.p.y -= b.velocity * sin( b.angle + M_PI / 2.0f );
        if ( b.p.x > width + inv_zone ) {
            b.p.x = -inv_zone;
        } else if ( b.p.x < -inv_zone ) {
            b.p.x = width + inv_zone;
        }
        if ( b.p.y > height + inv_zone ) {
            b.p.y = -inv_zone;
        } else if ( b.p.y < -inv_zone ) {
            b.p.y = height + inv_zone;
        }
        b.life--;
    }
    std::sort( bullet.begin(), bullet.end(), 
        []( const bullet_t & a, const bullet_t &b ) { return a.life < b.life; } 
    );
    bullet.erase( std::remove_if( bullet.begin(), bullet.end(), 
        []( const bullet_t & a ) { return a.life == 0; } ), bullet.end()
    );
}

void BulletSystem::draw( DrawSystem & draw ) {
    draw.set_coloru( COLOR_WHITE );
    for ( auto & b : bullet ) {
        draw.circle( round( b.p.x ), round( b.p.y ), max_radius );
    }
    draw.set_coloru( COLOR_BLACK );
}