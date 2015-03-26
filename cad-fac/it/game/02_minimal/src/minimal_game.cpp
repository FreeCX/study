#include <SDL2/SDL.h>
#include <ctime>
#include <vector>
#include "draw.hpp"
#include "font.hpp"
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

size_t game_score = 0;
size_t asteroid_count = 8;
FontTable font;
Player player;
DrawSystem draw( nullptr, 16 );
BulletSystem bullet( 5, 10, 4 );
std::vector< Asteroid > asteroids;
bool move_flag = false;

// обработка ошибок
void game_send_error( int code ) {
    SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(), nullptr );
    exit( code );
}

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
                    player.add_angle( -0.05f );
                    break;
                case SDLK_RIGHT:
                    player.add_angle( +0.05f );
                    break;
                case SDLK_SPACE:
                    bullet.append( player );
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

// игровой цикл
void game_loop( void ) {
    static int counter = 0;

    player.step();
    bullet.step();
    for ( auto & a : asteroids ) {
        a.step();
    }
    if ( move_flag && counter % 8 == 0 ) {
        player.add_velocity( 1 );
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
    swprintf( text_buffer, BUFFER_SIZE, L"score %08zu\n life %s", game_score, life );
    // рисуем текст
    font.draw( 8, 8, text_buffer );
    // рисуем игрока
    player.draw( draw );
    bullet.draw( draw );
    for ( auto & a : asteroids ) {
        a.draw( draw );
    }
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
    srand( time( nullptr ) );
    SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS );
    gw.window = SDL_CreateWindow( gw.name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                  gw.width, gw.height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
    if ( gw.window == nullptr ) {
        game_send_error( EXIT_FAILURE );
    }
    gw.render = SDL_CreateRenderer( gw.window, gw.SDL_RENDER_DRIVER, 
                                    SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC | 
                                    SDL_RENDERER_TARGETTEXTURE );
    if ( gw.render == nullptr ) {
        game_send_error( EXIT_FAILURE );
    }
    // включаем режим смешивания
    SDL_SetRenderDrawBlendMode( gw.render, SDL_BLENDMODE_BLEND );
    // инициализируем модуля рисования
    draw.set_render( gw.render );
    // загружаем текстуру для шрифта
    font.load( gw.render, "./data/font.cfg" );
    // устанавливаем игрока по центру экрана
    player.set_position( gw.width / 2, gw.height / 2 );
    asteroids.resize( asteroid_count );
    for ( auto & a : asteroids ) {
        a.init( rand() % 12 + 8, ( rand() % 32 + 16 ) * 1.0f );
        a.set_rotation_speed( ( rand() % 100 + 1 ) / 2000.0f );
        a.set_speed( ( rand() % 100 - 50 ) / 30, ( rand() % 100 - 50 ) / 30 );
        a.set_position( rand() % gw.width, rand() % gw.height );
    }
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
