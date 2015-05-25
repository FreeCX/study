#include <cstdio>

typedef struct ker_args{
    int id;
    vector * v0;
    int count_v0;
    double h;
    int n_x;
    int n_y;
    int n_z;
    vector_field field;
    runge_kutta::Fiber *fibers;
    size_t max_points;
} kernel_args;

void rk4_caller( FILE * std, size_t max_points, vector *v0, int count_v0, double h, 
                 int n_x, int n_y, int n_z, vector_field field, runge_kutta::Fiber **fibers );
