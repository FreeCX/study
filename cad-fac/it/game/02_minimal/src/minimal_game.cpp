#include <SDL2/SDL.h>
#include "draw.hpp"
#include "font.hpp"
#include "sound.hpp"
#include "player.hpp"
#include "asteroid.hpp"
#include "bullet.hpp"

// используем структуру для хранения данных связанных с окном
struct Window {
    // название окна
    const char * name = (const char *) "Asteroids";
    // драйвер отрисовщик
    const int SDL_RENDER_DRIVER = 0;
    // указатель на окно
    SDL_Window * window = nullptr;
    // на рендер
    SDL_Renderer * render = nullptr;
    // структура с событиями окна
    SDL_Event event;
    // флаг закрытия
    bool quit_flag = false;
    // размеры окна
    int width = 640;
    int height = 640;
} gw;

// константы поворота игрока
enum {
    ROTATE_NONE,
    ROTATE_LEFT,
    ROTATE_RIGHT
};

// константы для подсчёта игровых очков и бонусов
size_t game_score = 0, last_score = 0;
// класс работы со шрифтами
FontTable font;
// класс игрока
Player player;
// система отрисовки
DrawSystem draw( nullptr, 16 );
// система снарядов
BulletSystem bullet( 5, 80, 2 );
// система астероидов
AsteroidSystem asteroid( gw.width, gw.height, 16, 16 );
// звуковая система
SoundSystem sound;
// флаг отвечающий за движение игрока
bool move_flag = false;
// флаг отвечающий за выстрелы
bool shoot_flag = false;
// флаг новой игры
bool gameover_flag = true;
// флаг поворота игрока
short rotate_flag = ROTATE_NONE;
// звуковые константы (для звуковой системы)
uint4_t sound_track, sound_shoot;
uint4_t sound_explosion, sound_bonus;

// обработка событий
void game_event( void ) {
    // получаем оконное событие от SDL
    SDL_PollEvent( &( gw.event ) );
    switch ( gw.event.type ) {
        // сигнал закрытия программы
        case SDL_QUIT:
            gw.quit_flag = true;
            break;
        // обрабатываем оконные события
        case SDL_WINDOWEVENT:
            // обработка изменения размера окна
            if ( gw.event.window.event == SDL_WINDOWEVENT_RESIZED ) {
                gw.width  = gw.event.window.data1;
                gw.height = gw.event.window.data2;
            }
            break;
        // обработка отпускания клавиш
        case SDL_KEYUP:
            switch ( gw.event.key.keysym.sym ) {
                case SDLK_UP:
                case SDLK_w:
                    move_flag = false;
                    break;
                case SDLK_LEFT:
                case SDLK_a:
                case SDLK_RIGHT:
                case SDLK_d:
                    rotate_flag = ROTATE_NONE;
                    break;
                case SDLK_SPACE:
                    shoot_flag = false;
                    break;
                default:
                    break;
            }
            break;
        // обработка нажатия клавиш
        case SDL_KEYDOWN:
            switch ( gw.event.key.keysym.sym ) {
                case SDLK_ESCAPE:
                    gw.quit_flag = true;
                    break;
                case SDLK_UP:
                case SDLK_w:
                    move_flag = true;
                    break;
                case SDLK_LEFT:
                case SDLK_a:
                    rotate_flag = ROTATE_LEFT;
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    rotate_flag = ROTATE_RIGHT;
                    break;
                case SDLK_SPACE:
                if ( gameover_flag ) {
                        game_score = last_score = 0;
                        gameover_flag = false;
                        player.set_life( 3 );
                        asteroid.get_vector().clear();
                    }
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

// игровой цикл
void game_loop( void ) {
    static int counter = 0;
    size_t add_score = 0;

    if ( gameover_flag == false ) {
        // обработка столкновения снарядов с астероидами
        add_score = bullet.collider( asteroid );
        if ( add_score > 0 ) {
            // добавляем очки при попадании
            game_score += add_score;
            // проигрываем звук взрыва астероида
            sound.play( sound_explosion, false );
        }
        // обработка столкновения игрока с астероидами
        if ( player.collider( asteroid ) ) {
            gameover_flag = player.destroy();
        }
        // двигаем игровые объекты
        player.step( gw.width, gw.height );
        bullet.step( gw.width, gw.height );
        asteroid.step( gw.width, gw.height );
        if ( counter % 8 == 0 ) {
            if ( move_flag ) {
                // разгон игрока
                player.add_velocity( 1 );
            }
            if ( shoot_flag ) {
                // выстрел игрока
                sound.play( sound_shoot, false );
                bullet.append( player );
            }
        }
        // добавляем астероид каждые 100 игровых циклов
        if ( counter % 100 == 0 ) {
            asteroid.rand_append();
        }
        // добавляем одну жизнь каждые 10000 очков
        if ( game_score > 0 && log10( game_score - last_score ) >= 4 ) {
            last_score = game_score;
            sound.play( sound_bonus, false );
            player.add_life( 1 );
        }
        // обработка поворота игрока
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
}

// отрисовка
void game_render( void ) {
    const std::size_t BUFFER_SIZE = 128;
    wchar_t text_buffer[BUFFER_SIZE];
    static char life[16] = { 0 };

    // очищаем окно
    SDL_RenderClear( gw.render );
    memset( life, 0, 16 );
    // представляем количество жизней в виде '+'
    memset( life, '+', player.get_life() );
    // подготавливаем выводимый текст
    swprintf( text_buffer, BUFFER_SIZE, L"score %010zu\n life %s\n", game_score, life );
    // рисуем текст
    font.draw( 8, 8, text_buffer );
    if ( gameover_flag ) {
        // выводим текст о начале новой игры
        const wchar_t new_game[] = L"press space to start a new game...";
        size_t ts = wcslen( new_game ) * font.get_width();
        font.draw( ( gw.width - ts ) / 2, gw.height / 2, new_game );
    } else {
        // рисуем игрока
        player.draw( draw );
    }
    // рисуем снаряды
    bullet.draw( draw );
    // рисуем астероиды
    asteroid.draw( draw );
    // сообщаем SDL о конце отрисовки
    SDL_RenderPresent( gw.render );
}

// освобождение используемых ресурсов
void game_destroy( void ) {
    // освобождаем рендер
    SDL_DestroyRenderer( gw.render );
    // освобождаем окно
    SDL_DestroyWindow( gw.window );
    // закрываем программу
    SDL_Quit();
}

// блок инициализации
void game_init( void ) {
    // инициализируем видео систему и систему событий
    SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS );
    // создаём окно
    gw.window = SDL_CreateWindow( gw.name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                  gw.width, gw.height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
    // обработка ошибок
    if ( gw.window == nullptr ) {
        game_send_error( SDL_GetError(), EXIT_FAILURE );
    }
    // создаём рендер
    gw.render = SDL_CreateRenderer( gw.window, gw.SDL_RENDER_DRIVER, 
                                    SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC | 
                                    SDL_RENDERER_TARGETTEXTURE );
    // обработка ошибок
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
    // загрузка звуковых файлов
    sound_track = sound.load( "./data/soundtrack.ogg" );
    sound_shoot = sound.load( "./data/shot.ogg" );
    sound_explosion = sound.load( "./data/explosion.ogg" );
    sound_bonus = sound.load( "./data/bonus.ogg" );
    // установка громкости для звуковых дорожек
    sound.set_volume( sound_track, 120 );
    sound.set_volume( sound_shoot, 150 );
    sound.set_volume( sound_bonus, 100 );
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
