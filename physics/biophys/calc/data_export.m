function func = data_export(t,x)
    l = length(t);
    f = fopen( 'data.txt', 'w' );
    for k = 1:1:length(t);
        fprintf( f, '%.4f %.4f %.4f\n', t(k), x(k), x(k+l) );
    end;
    fclose( f );
    func = 0;
end
