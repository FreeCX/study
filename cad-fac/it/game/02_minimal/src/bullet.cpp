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
    int x = 0, y = 0;
    
    x = player.get_x() + round( player.a * sin( angle ) );
    y = player.get_y() - round( player.a * cos( angle ) );
    bullet.push_back( { x, y, max_life, angle, max_velocity + player.get_velocity() } );
}

void BulletSystem::step( void ) {
    for ( auto & b : bullet ) {
        b.x -= round( b.velocity * cos( b.angle + M_PI / 2.0f ) );
        b.y -= round( b.velocity * sin( b.angle + M_PI / 2.0f ) );
        if ( b.x > 660 ) {
            b.x = -20;
        } else if ( b.x < -20 ) {
            b.x = 660;
        }
        if ( b.y > 660 ) {
            b.y = -20;
        } else if ( b.y < -20 ) {
            b.y = 660;
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
        draw.circle( b.x, b.y, max_radius );
    }
    draw.set_coloru( COLOR_BLACK );
}