void *rk4_kernel( void *args ) {
    kernel_args arguments = *( (kernel_args *) args );
    vector k1, k2, k3, k4, initial, direction;
    vector *points_aux = NULL;
    size_t n_points_aux = 0, j = 0;

    set( &initial, arguments.v0[arguments.id] );
    set( &direction, arguments.field[DataSet::offset( arguments.n_x, arguments.n_y, 
         initial.x, initial.y, initial.z )] );
    points_aux = (vector *) malloc( arguments.max_points * sizeof(vector) );
    while ( module( direction ) > 0 && n_points_aux < arguments.max_points ) {
        n_points_aux++;
        set( &(points_aux[n_points_aux - 1]), initial);
        set( &k1, mult_scalar( direction, arguments.h ) );
        set( &k2, mult_scalar( trilinear_interpolation( sum( initial, mult_scalar( k1, 0.5 ) ),
             arguments.n_x, arguments.n_y, arguments.n_z, arguments.field ), arguments.h ) );
        set( &k3, mult_scalar( trilinear_interpolation( sum( initial, mult_scalar( k2, 0.5 ) ),
             arguments.n_x, arguments.n_y, arguments.n_z, arguments.field ), arguments.h ) );
        set( &k4, mult_scalar( trilinear_interpolation( sum( initial, k3 ),
             arguments.n_x, arguments.n_y, arguments.n_z, arguments.field ), arguments.h ) );
        set( &initial, sum( initial, sum( mult_scalar( k1 , 0.166666667 ), 
             sum( mult_scalar( k2, 0.333333333 ), sum( mult_scalar( k3, 0.333333333 ), 
             mult_scalar( k4, 0.166666667 ) ) ) ) ) );
        set( &direction, trilinear_interpolation( initial, arguments.n_x, arguments.n_y, arguments.n_z, 
             arguments.field ) );
    }
    (arguments.fibers)[arguments.id] = Fiber( n_points_aux );
    for ( j = 0; j < n_points_aux; j++ ) {
        (arguments.fibers)[arguments.id].setPoint( j, points_aux[j] );
    }
    free( points_aux );
    return NULL;
}

void rk4_caller( FILE * std, size_t max_points, vector *v0, int count_v0, double h,
                 int n_x, int n_y, int n_z, vector_field field, Fiber **fibers ) {
    double start, finish;
    kernel_args *arguments;
    int i;

    omp_set_dynamic( 0 );
    omp_set_num_threads( count_v0 );
    *fibers = (Fiber *) malloc( count_v0 * sizeof(Fiber) );
    arguments = (kernel_args *) malloc( count_v0 * sizeof(kernel_args) );
    start = omp_get_wtime();
    #pragma omp parallel for shared( arguments, v0, fibers ) private( i )
    for ( i = 0; i < count_v0; i++ ){
        arguments[i].id = i;
        arguments[i].v0 = v0;
        arguments[i].count_v0 = count_v0;
        arguments[i].h = h;
        arguments[i].n_x = n_x;
        arguments[i].n_y = n_y;
        arguments[i].n_z = n_z;
        arguments[i].field = field;
        arguments[i].fibers = *fibers;
        arguments[i].max_points = max_points;
        rk4_kernel( &( arguments[i] ) );
    }
    finish = omp_get_wtime();
    free( arguments );
    free( *fibers );
    fprintf( std, "[ OpenMP] CPU time for RK4: %.4Es\n", finish - start );
    fprintf( std, " -------> max points: %lu\n", max_points );
}
