function y = calc( )
    t0 = [0, 50];
    x0 = [5, 1];
    L0 = [3, 5];
    [t,x] = ode45( @trigger, t0, x0, [], L0 );
    data_export( t, x );
end

