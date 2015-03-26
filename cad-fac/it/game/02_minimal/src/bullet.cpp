#include "bullet.hpp"

BulletSystem::BulletSystem( const float velocity, const short life ) {
    max_velocity = velocity;
    max_life = life;
}

BulletSystem::~BulletSystem() {
    bullet.clear();
}

void BulletSystem::append( Player & player ) {
    float angle = player.get_angle();
    int x = 0, y = 0;
    
    x = player.get_x() + round( player.a * sin( angle ) );
    y = player.get_y() - round( player.a * cos( angle ) );
    bullet.push_back( { x, y, max_life, angle, max_velocity } );
}

void BulletSystem::step( void ) {
    for ( auto & b : bullet ) {
        b.x -= round( b.velocity * cos( b.angle + M_PI / 2.0f ) );
        b.y -= round( b.velocity * sin( b.angle + M_PI / 2.0f ) );
        b.life--;
    }
    // FIX THIS CODE
    // std::sort( bullet.begin(), bullet.end(), 
    //     []( const bullet_t & a, const bullet_t &b ) { return a.life < b.life; } 
    // );
    // for ( size_t i = bullet.size() - 1; i > 0; i++ ) {
    //     if ( bullet[i].life > 0 ) {
    //         break;
    //     }
    //     // maybe it works!
    //     bullet.erase( bullet.begin() + i );
    // }
}

void BulletSystem::draw( DrawSystem & draw ) {
    draw.set_coloru( COLOR_WHITE );
    for ( auto & b : bullet ) {
        draw.circle( b.x, b.y, 4 );
    }
    draw.set_coloru( COLOR_BLACK );
}