#include "bullet.hpp"

BulletSystem::BulletSystem( const float velocity, const short life, const short radius ) {
    max_velocity = velocity;
    max_life = life;
    max_radius = radius;
}

BulletSystem::~BulletSystem() {
    bullets.clear();
}

// функция добавления снаряда
void BulletSystem::append( Player & player ) {
    float angle = player.get_angle();
    vec2 p;
    
    // получаем вектор позиции
    p = vec2( player.get_x() + player.a * sin( angle ), player.get_y() - player.a * cos( angle ) );
    // добавляем в вектор
    bullets.push_back( { p, max_life, angle, max_velocity + player.get_velocity() } );
}

// функция перемещения снарядов
void BulletSystem::step( const int width, const int height ) {
    // мёртвая зона
    const int inv_zone = 20;

    // удаляем из вектора все 'мёртвые' элементы (время жизни <= 0)
    bullets.erase( std::remove_if( bullets.begin(), bullets.end(), 
        []( const bullet_t & a ) { return a.life <= 0; } ), bullets.end()
    );
    // цикл по всем снарядам
    for ( auto & b : bullets ) {
        b.p -= vec2( cos( b.angle + M_PI / 2.0f ), sin( b.angle + M_PI / 2.0f ) ) * b.velocity;
        /* блок зацикливания игрового пространства */
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
        /* блок зацикливания игрового пространства */
        // уменьшаем время жизни
        b.life--;
    }
}

// функция отрисовки снарядов
void BulletSystem::draw( DrawSystem & draw ) {
    draw.set_coloru( COLOR_WHITE );
    // проходим по всем и рисуем маленькие кружки
    for ( auto & b : bullets ) {
        draw.circle( round( b.p.x ), round( b.p.y ), max_radius );
    }
    draw.set_coloru( COLOR_BLACK );
}

bullet_v & BulletSystem::get_vector( void ) {
    return bullets;
}

// функция определения пересечения двух окружностей (снаряд и астероид)
bool collide( const asteroid_t & a, const bullet_t & b ) {
    vec2 p1 = a.p, p2 = b.p;
    vec2 p = p2 - p1;
    float d = a.radius - p.length();
    if ( d >= 0 ) {
        return true;
    } else {
        return false;
    }
}

// функция обработки столкновений
const size_t BulletSystem::collider( AsteroidSystem & asteroids ) {
    size_t game_score = 0;

    // цикл по всем астероидам
    for ( auto & ast : asteroids.get_vector() ) {
        // и по всем снарядам
        for ( auto & bul : bullets ) {
            // проверка на столкновение
            if ( collide( ast, bul ) ) {
                // уничтожаем снаряд и астероид
                ast.life = bul.life = 0;
                // и создаём 3 новый (но меньше и медленее)
                // при условии, что они больше минимального радиуса
                const int r = ast.radius / 3;
                if ( r > asteroids.asteroid_eps ) {
                    vec2 v = ast.v * 0.8f;
                    float nr = r * 0.8f;
                    asteroids.append( ast.p - vec2( 0, nr ), v.rot( 0.75f * M_PI ), r );
                    asteroids.append( ast.p + vec2( nr, 0 ), v, r );
                    asteroids.append( ast.p - vec2( nr, 0 ), v.rot( 1.25f * M_PI ), r );
                }
                // подсчёт заработанных игровых очков (чем больше астероид, тем больше очков)
                game_score += ast.radius * 3;
            }
        }
    }
    return game_score;
}