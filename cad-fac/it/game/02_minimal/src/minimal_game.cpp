#include <SDL2/SDL.h>
#include "draw.hpp"
#include "font.hpp"
#include "sound.hpp"
#include "player.hpp"
#include "asteroid.hpp"
#include "bullet.hpp"

// используем структуру для хранения данных связанных с окном
struct Window {
    const char * name = (const char *) "Minimal Game";
    const int SDL_RENDER_DRIVER = 0;
    SDL_Window * window = nullptr;
    SDL_Renderer * render = nullptr;
    SDL_Event event;
    bool quit_flag = false;
    int width = 640;
    int height = 640;
} gw;

enum {
    ROTATE_NONE,
    ROTATE_LEFT,
    ROTATE_RIGHT
};

size_t game_score = 0;
size_t asteroid_count = 8;
FontTable font;
Player player;
DrawSystem draw( nullptr, 16 );
BulletSystem bullet( 5, 80, 2 );
AsteroidSystem asteroid( gw.width, gw.height, 16, 16 );
SoundSystem sound;
bool move_flag = false;
bool shoot_flag = false;
short rotate_flag = ROTATE_NONE;
const int asteroid_eps = 8;
uint4_t sound_track, sound_shoot;

// обработка событий
void game_event( void ) {
    SDL_PollEvent( &( gw.event ) );
    switch ( gw.event.type ) {
        case SDL_QUIT:
            gw.quit_flag = true;
            break;
        case SDL_WINDOWEVENT:
            if ( gw.event.window.event == SDL_WINDOWEVENT_RESIZED ) {
                gw.width  = gw.event.window.data1;
                gw.height = gw.event.window.data2;
            }
            break;
        case SDL_KEYUP:
            switch ( gw.event.key.keysym.sym ) {
                case SDLK_UP:
                    move_flag = false;
                    break;
                case SDLK_LEFT:
                case SDLK_RIGHT:
                    rotate_flag = ROTATE_NONE;
                    break;
                case SDLK_SPACE:
                    shoot_flag = false;
                    break;
                default:
                    break;
            }
            break;
        case SDL_KEYDOWN:
            switch ( gw.event.key.keysym.sym ) {
                case SDLK_ESCAPE:
                    gw.quit_flag = true;
                    break;
                case SDLK_UP:
                    move_flag = true;
                    break;
                case SDLK_LEFT:
                    rotate_flag = ROTATE_LEFT;
                    break;
                case SDLK_RIGHT:
                    rotate_flag = ROTATE_RIGHT;
                    break;
                case SDLK_SPACE:
                    shoot_flag = true;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

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

void collider( AsteroidSystem & a, BulletSystem & b ) {
    auto & av = a.get_vector();
    auto & bv = b.get_vector();

    for ( auto & ast : av ) {
        for ( auto & bul : bv ) {
            if ( collide( ast, bul ) ) {
                ast.life = bul.life = 0; // destroy it
                const int r = ast.radius / 3;
                if ( r > asteroid_eps ) {
                    vec2 v = ast.v * 0.8f;
                    float nr = r * 0.8f;
                    a.append( ast.p - vec2( 0, nr ), v.rot( 0.75f * M_PI ), r );
                    a.append( ast.p + vec2( nr, 0 ), v, r );
                    a.append( ast.p - vec2( nr, 0 ), v.rot( 1.25f * M_PI ), r );
                    game_score += ast.radius * 3;
                }
            }
        }
    }
}

// игровой цикл
void game_loop( void ) {
    static int counter = 0;

    collider( asteroid, bullet );
    player.step( gw.width, gw.height );
    bullet.step( gw.width, gw.height );
    asteroid.step( gw.width, gw.height );
    if ( counter % 8 == 0 ) {
        if ( move_flag ) {
            player.add_velocity( 1 );
        }
        if ( shoot_flag ) {
            sound.play( sound_shoot, false );
            bullet.append( player );
        }
    }
    if ( counter % 100 == 0 ) {
        asteroid.rand_append();
    }
    switch ( rotate_flag ) {
        case ROTATE_LEFT:
            player.add_angle( -0.05f );
            break;
        case ROTATE_RIGHT:
            player.add_angle( +0.05f );
            break;
        default:
            break;
    }
    counter++;
}

// отрисовка
void game_render( void ) {
    const std::size_t BUFFER_SIZE = 128;
    wchar_t text_buffer[BUFFER_SIZE];
    char life[player.life_max+1] = { 0 };

    SDL_RenderClear( gw.render );
    // представляем количество жизней в виде '+'
    memset( life, '+', player.get_life() );
    // подготавливаем выводимый текст
    swprintf( text_buffer, BUFFER_SIZE, L"score %08zu\n life %s\nasteroid %ld", 
        game_score, life, asteroid.count() );
    // рисуем текст
    font.draw( 8, 8, text_buffer );
    // рисуем игрока
    player.draw( draw );
    bullet.draw( draw );
    asteroid.draw( draw );
    SDL_RenderPresent( gw.render );
}

// освобождение используемых ресурсов
void game_destroy( void ) {
    SDL_DestroyRenderer( gw.render );
    SDL_DestroyWindow( gw.window );
    SDL_Quit();
}

// блок инициализации
void game_init( void ) {
    SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS );
    gw.window = SDL_CreateWindow( gw.name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                  gw.width, gw.height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
    if ( gw.window == nullptr ) {
        game_send_error( SDL_GetError(), EXIT_FAILURE );
    }
    gw.render = SDL_CreateRenderer( gw.window, gw.SDL_RENDER_DRIVER, 
                                    SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC | 
                                    SDL_RENDERER_TARGETTEXTURE );
    if ( gw.render == nullptr ) {
        game_send_error( SDL_GetError(), EXIT_FAILURE );
    }
    // включаем режим смешивания
    SDL_SetRenderDrawBlendMode( gw.render, SDL_BLENDMODE_BLEND );
    // инициализируем модуля рисования
    draw.set_render( gw.render );
    // загружаем текстуру для шрифта
    font.load( gw.render, "./data/font.cfg" );
    // устанавливаем игрока по центру экрана
    player.set_position( gw.width / 2, gw.height / 2 );
    sound_track = sound.load( "./data/soundtrack.ogg" );
    sound_shoot = sound.load( "./data/shot.ogg" );
    sound.set_volume( sound_track, 120 );
    sound.set_volume( sound_shoot, 150 );
    sound.play( sound_track, true );
}

// точка входа программы
int main( int argc, char * argv[] ) {
    game_init();
    while ( !gw.quit_flag ) {
        game_event();
        game_loop();
        game_render();
    }
    game_destroy();
    return EXIT_SUCCESS;
}
