function y = calc( t0, X0, L0 )
    n = 1;
    for gamma = 0.90:0.0005:1;
        [t,x] = ode45( @trigger, t0, X0, [], L0, gamma );
        data_export( t, x, n );
        n  = n + 1;
    end;
end

