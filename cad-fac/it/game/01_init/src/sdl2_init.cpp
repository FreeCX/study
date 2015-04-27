#include <SDL2/SDL.h>

// используем структуру для хранения данных связанных с окном
struct Window {
    const char * name = (const char *) "Skeleton";
    const int SDL_RENDER_DRIVER = 0;
    SDL_Window * window = nullptr;
    SDL_Renderer * render = nullptr;
    SDL_Event event;
    bool quit_flag = false;
    int width = 640;
    int height = 640;
} gw;

// обработка ошибок
void game_send_error( int code ) {
    SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(), 
                              nullptr );
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
        case SDL_KEYDOWN:
            switch ( gw.event.key.keysym.sym ) {
                case SDLK_ESCAPE:
                    gw.quit_flag = true;
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
    // insert code here
}

// отрисовка
void game_render( void ) {
    SDL_RenderClear( gw.render );
    // insert code here
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
    gw.window = SDL_CreateWindow( gw.name, SDL_WINDOWPOS_CENTERED, 
                                  SDL_WINDOWPOS_CENTERED, 
                                  gw.width, gw.height, 
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
    if ( gw.window == nullptr ) {
        game_send_error( EXIT_FAILURE );
    }
    gw.render = SDL_CreateRenderer( gw.window, gw.SDL_RENDER_DRIVER, 
                                    SDL_RENDERER_SOFTWARE | 
                                    SDL_RENDERER_PRESENTVSYNC | 
                                    SDL_RENDERER_TARGETTEXTURE );
    if ( gw.render == nullptr ) {
        game_send_error( EXIT_FAILURE );
    }
    SDL_SetRenderDrawBlendMode( gw.render, SDL_BLENDMODE_BLEND );
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
