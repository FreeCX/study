#pragma once
#include <cmath>
#include <float.h>

// windows MinGW fix
#ifdef __MINGW32__
#ifndef M_PI
    const double M_PI   = 3.14159265358979323846264338327950288;
#endif
#endif

inline float _fmod( float x, float y ) { 
    return fmod( fmod( x, y ) + y, y ); 
}

struct vec2 {
    vec2() {}
    vec2( const float x0, const float y0 ) : x( x0 ), y( y0 ) {}
    void operator () ( const float x0, const float y0 );
    bool operator == ( const vec2 &v );
    bool operator != ( const vec2 &v );
    vec2 & operator = ( const vec2 &v );
    vec2 operator - ( void );
    vec2 operator + ( const vec2 &v );
    vec2 operator - ( const vec2 &v );
    vec2 operator * ( const float k );
    vec2 operator / ( const float k );
    vec2 operator -= ( const vec2 &v );
    vec2 operator += ( const vec2 &v );
    vec2 operator *= ( const float k );
    vec2 operator /= ( const float k );
    vec2 operator * ( const vec2 &v );
    vec2 abs( void );
    vec2 norm( void );
    float length( void );
    float dot( const vec2 &v );
    float x, y;
};