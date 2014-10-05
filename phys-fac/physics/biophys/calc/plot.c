#include <stdio.h>
#include <stdlib.h>

char init_gnuplot[] = 
    "set terminal png\n"
    "set grid\n";
char graph[] =
    "set output 'graph_%04d.png'\n"
    "set title 'gamma = %.4f'\n"
    "plot 'data_%04d.txt' using 1:2 title 'L_1 = %.2f' with lines lt 7 lc 1 lw 2," 
    "'data_%04d.txt' using 1:3 title 'L_2 = %.2f' with lines lt 7 lc 2 lw 2\n";

int main( void )
{
    FILE *f;
    float L1 = 8.0f, L2 = 20.0f, gamma;
    int n = 1;

    f = popen("gnuplot -persistent", "w" );
    fprintf( f, init_gnuplot );
    for ( gamma = 0.90f; gamma < 1.0f; gamma += 0.0005f ){
        fprintf( f, graph, gamma, n, n, L1, n, L2 );    
        n++;
    }
    return 0;
}
