#include <stdio.h>
#include <stdlib.h>

const char rotation_data[] =
    "0.0 16.0 10.0\n"
    "0.0 32.0 10.0\n"
    "0.0 48.0 10.0\n"
    "0.0 64.0 10.0\n"
    "0.0 80.0 10.0\n"
    "0.0 96.0 10.0\n"
    "0.0 112.0 10.0\n";

int main( int argc, char *argv[] ) {
    int dim_x, dim_y, dim_z, i, j, k;
    const int size = 7;
    float h = 0.1;
    FILE * f;

    if ( argc == 2 ) {
        h = atof( argv[1] );
        printf( "[set] h = %e\n", h );
    }
    dim_x = dim_y = 128;
    dim_z = 20;
    i = j = k = 0;
    f = fopen( "rotationField", "w" );
    fprintf( f, "%d %d %d\n%d\n", dim_x, dim_y, dim_z, size );
    fprintf( f, "%s", rotation_data );
    fprintf( f, "%e\n", h );
    for ( k = 1; k < dim_z; k++ ) {
        for ( i = 1; i < dim_x; i++ ) {
            for ( j = 1; j < dim_y; j++ ) {
                fprintf( f, "%f %f 0\n", (float) j / (float) i, -(float) i / (float) j );
            }
        }
    }
    fclose( f );
    return 0;
}
