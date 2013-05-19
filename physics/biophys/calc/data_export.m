function func = data_export(t,x,n)
    l = length(t);
    buffer = sprintf( 'data_%04d.txt', n );
    f = fopen( buffer, 'w' );
    for k = 1:1:length(t);
        fprintf( f, '%.4f %.4f %.4f\n', t(k), x(k), x(k+l) );
    end;
    fclose( f );
    func = 0;
end
