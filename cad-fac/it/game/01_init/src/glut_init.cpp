#include <GL/glut.h>

// используем структуру для хранения данных связанных с окном
struct Window {
    const char * name = (const char *) "Skeleton";
    const GLuint fps = 1000 / 60;
    GLint win_id = 0;
    GLint width = 640;
    GLint height = 640;
} gw;

// отрисовка
void game_render( void ) {
    glClear( GL_COLOR_BUFFER_BIT );
    // render code
    glutSwapBuffers();
}

// игровой цикл
void game_loop( int value ) {
    game_render();
    glutTimerFunc( gw.fps, game_loop, 0 );
}

// обработка событий клавиатуры
void game_keyboard( unsigned char key, int x, int y ) {
    static bool fullscreen = true;
    if ( key == 'q' ) {
        glutDestroyWindow( gw.win_id );
    } else if ( key == 'f' ) {
        if ( fullscreen ) {
            glutFullScreen();
        } else {
            glutReshapeWindow( gw.width, gw.height );
        }
        fullscreen = !fullscreen;
    }
}

// блок инициализации
void game_init( void ) {
    GLint sw = glutGet( GLUT_SCREEN_WIDTH );
    GLint sh = glutGet( GLUT_SCREEN_HEIGHT );
    glutInitWindowSize( gw.width, gw.height );
    glutInitWindowPosition( ( sw - gw.width ) / 2, ( sh - gw.height) / 2  );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    gw.win_id = glutCreateWindow( gw.name );
    glutDisplayFunc( game_render );
    glutKeyboardFunc( game_keyboard );
    glutTimerFunc( gw.fps, game_loop, 0 );
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
}

// освобождение используемых ресурсов
void game_destroy( void ) {
    // insert code here
}

// точка входа программы
int main( int argc, char *argv[] ) {
    glutInit( &argc, argv );
    game_init();
    glutMainLoop();
    game_destroy();
    return EXIT_SUCCESS;
}
