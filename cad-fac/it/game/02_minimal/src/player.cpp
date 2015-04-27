#include "player.hpp"

// установка координат игрока
void Player::set_position( int x, int y ) {
    p = vec2( x, y ); 
}

// установка угла поворота игрока
void Player::set_angle( float angle ) { 
    this->angle = angle; 
}

// добавление к углу поворота
void Player::add_angle( float add ) { 
    angle = _fmod( angle + add + M_PI, 2 * M_PI ) - M_PI;
}

// добавление к скорости
void Player::add_velocity( int add ) {
    if ( velocity < velocity_max ) {
        velocity += add; 
    }
}

// добавление к жизням
void Player::add_life( short add ) { 
    if ( life + add <= life_max && life + add >= 0 ) {
        life += add; 
    }
}

// установка игровых жизней
void Player::set_life( signed short life ) {
    this->life = life > life_max ? life_max : life;
}

// получение игровых жизней
char Player::get_life( void ) const { 
    return life; 
}

// функция перемещения игрока
void Player::step( const int width, const int heigth ) {
    // мёртвая зона для отрисовки
    static const int inv_zone = a;
    static short counter = 0;

    // передвигаем игрока по направлению angle со скоростью velocity
    p -= vec2( cos( angle + M_PI / 2.0f ), sin( angle + M_PI / 2.0f ) ) * velocity;
    /* блок зацикливания игрового поля */
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
    /* блок зацикливания игрового поля */
    // уменьшение скорости игрока
    if ( velocity > 0 && counter % 32 == 0 ) {
        velocity--;
    }
    // время неуязвимости игрока
    if ( immortal != 0 ) {
        immortal--;
    }
    counter++;
}

// функция отрисовки игрока
void Player::draw( DrawSystem & draw ) {
    // координаты узловых точек корабля в формате (x0, y0, x1, y1, ...)
    //            0    1    2      3  4  5  6      7  8   9
    int pos[] = { 0, - a, - a / 2, b, 0, 0, a / 2, b, 0, -a };

    // отрисовка каждый 8 кадр при неуязвимости
    if ( immortal % 8 == 0 ) {
        // устанавливаем цвет для рисования
        draw.set_coloru( COLOR_WHITE );
        // собираем координаты всех точек корабля с учётом угла
        for ( int i = 0; i < max_length; i += 2 ) {
            const float x = pos[i+0];
            const float y = pos[i+1];
            pos[i+0] = round( p.x + x * cos( angle ) - y * sin( angle ) );
            pos[i+1] = round( p.y + x * sin( angle ) + y * cos( angle ) );
        }
        // рисуем все точки
        for ( int i = 0; i < max_length - 2; i += 2 ) {
            draw.aaline( pos[i+0], pos[i+1], pos[i+2], pos[i+3] );
        }
        // возвращаем цвет
        draw.set_coloru( COLOR_BLACK );
    }
}

// функция проверки на пересечение отрезка и круга (астероида)
bool collide( vec2 p1, vec2 p2, asteroid_t & ast ) {
    // немного магии
    p1 -= ast.p; p2 -= ast.p;
    vec2 delta = p2 - p1;
    float a = delta.dot( delta );
    float b = 2.0f * p1.dot( delta );
    float c = p1.dot( p1 ) - powf( ast.radius, 2.0f );
    if ( b > 0 ) {
        return c < 0;
    }
    if ( b > ( 2.0f * a ) ) {
        return ( 4.0f * a * c - powf( b, 2.0f ) ) < 0;
    }
    return a + b + c < 0;
}

// функция обработки столкновений
bool Player::collider( AsteroidSystem & asteroids ) {
    vec2 p1, p2, p3, p4;
    bool status = false;

    // выходим если игрок неуязвим
    if ( immortal != 0 ) {
        return status;
    }
    // получаем вектора всех точек корабля
    p1 = p + vec2( 0.0f, -a ).rot( angle );
    p2 = p + vec2( -a / 2.0f, b ).rot( angle );
    p3 = p;
    p4 = p + vec2( a / 2.0f, b ).rot( angle );
    // проходим цикл по всем астероидам
    for ( auto & ast : asteroids.get_vector() ) {
        // проверяем на все возможные пересечения
        status = collide( p1, p2, ast ) | collide( p2, p3, ast ) | 
                 collide( p3, p4, ast ) | collide( p4, p1, ast );
        // в случае существования пересечений
        if ( status ) {
            // получаем новую скорость астероидов
            vec2 v = ast.v * 0.5f;
            // а также новый радиус
            float nr = ast.radius * 0.5f;
            // добавляем 3 новых (но меньше по размеру и скорости)
            asteroids.append( ast.p - vec2( 0, nr ), v.rot( 0.75f * M_PI ), nr );
            asteroids.append( ast.p + vec2( nr, 0 ), v, nr );
            asteroids.append( ast.p - vec2( nr, 0 ), v.rot( 1.25f * M_PI ), nr );
            // уничтожаем существующий астероид
            ast.life = 0;
            return status;
        }
    }
    return status;
}

// функция обработки уничтожения игрока
bool Player::destroy( void ) {
    // вычитаем жизнь
    add_life( -1 );
    // в случае нуля возвращаем истину
    if ( life == 0 ) {
        return true;
    }
    // время неуязвимости
    immortal = 255;
    return false;
}