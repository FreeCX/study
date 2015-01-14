#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] ) {
    int dim_x, dim_y, dim_z, signal, i, j, k;
    const int size = 256;
    float h = 0.2;
    FILE * f;

    if ( argc == 2 ) {
        h = atof( argv[1] );
        printf( "[set] h = %e\n", h );
    }
    dim_x = dim_y = 512;
    dim_z = 128;
    i = j = k = 0;
    f = fopen( "linesField", "w" );
    fprintf( f, "%d %d %d\n%d\n", dim_x, dim_y, dim_z, size );
    fprintf( f, "%s\n", "0.0 64.0 64.0" );
    fprintf( f, "%e\n", h );
    for ( k = 0; k < dim_z; k++ ) {
        signal = -1;
        for ( i = 0; i < dim_x; i++ ) {
            if ( i % 8 == 0 ) {
                signal *= -1;
            }
            for ( j = 0; j < dim_y; j++ ) {
                if ( signal == -1 ) {
                    fprintf( f, "1 -1 0\n" );
                } else {
                    fprintf( f, "1 1 0\n" );
                }
            }
        }
    }
    fclose( f );
    return 0;
}
