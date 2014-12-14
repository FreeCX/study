#include <cmath>
#include <iostream>
#include <random>

double func( double x, double y ) {
    return std::pow( x, 4 ) + std::pow( y, 3 ) + std::pow( x, 2 ) + y;
}

double randomize() {
    static std::uniform_real_distribution<> distribution( 0, 1 );
    static std::random_device generator;
    return distribution( generator );
}

void calc( double R, double T, size_t N, double & x0, double & y0 ) {
    double F0, F1, x1, y1, p;
    x0 = ( randomize() - 0.5 ) * R;
    y0 = ( randomize() - 0.5 ) * R;
    F0 = func( x0, y0 );
    for ( size_t i = 0; i < N; i++ ) {
        x1 = ( randomize() - 0.5 ) * R;
        y1 = ( randomize() - 0.5 ) * R;
        F1 = func( x1, y1 );
        if ( F1 < F0 ) {
            x0 = x1; y0 = y1;
        } else {
            p = ( F1 - F0 ) * std::exp( -T );
            if ( randomize() < p ) {
                x0 = x1; y0 = y1;
            }
        }
        R -= R / N;
        T -= T / N;
    }
}

int main( void ) {
    double R, T, x, y;
    size_t N;
    std::cout << "Enter R: ";
    std::cin >> R;
    std::cout << "Enter N: ";
    std::cin >> N;
    std::cout << "Enter T: ";
    std::cin >> T;
    calc( R, T, N, x, y );
    std::cout << "R = " << R << "; N = " << N << "; T = " << T 
              << "; x = " << x << "; y = " << y 
              << "; f(x, y) = " << func( x, y ) << std::endl;
    return 0;
}