#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main( int argc, char *argv[] ) {
    int dim_x, dim_y, dim_z, r1, r2, r3, i, j, k;
    const int size = 256;
    float h = 0.1;
    FILE * f;

    if ( argc == 2 ) {
        h = atof( argv[1] );
        printf( "[set] h = %e\n", h );
    }
    dim_x = dim_y = dim_z = 256;
    i = j = k = 0;
    srand( time( NULL ) );
    f = fopen( "randomField", "w" );
    fprintf( f, "%d %d %d\n%d\n", dim_x, dim_y, dim_z, size );
    for ( i = 0; i < size; i++ ) {
        fprintf( f, "%d %d %d\n", rand() % 255, rand() % 255, rand() % 255 );
    }
    fprintf( f, "%e\n", h );
    for ( k = 0; k < dim_z; k++ ) {
        for ( i = 0; i < dim_x; i++ ) {
            for ( j = 0; j < dim_y; j++ ) {
                r1 = ( rand() % dim_x ) - ( ( dim_x - 1 ) / 2 );
                r2 = ( rand() % dim_y ) - ( ( dim_y - 1 ) / 2 );
                r3 = ( rand() % dim_z ) - ( ( dim_z - 1 ) / 2 );
                fprintf( f, "%d %d %d\n", r1, r2, r3 );
            }
        }
    }
    fclose( f );
    return 0;
}
