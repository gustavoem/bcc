function retval = ep1(p)          
    starttime = time;       
    n = length(p);
    visit = zeros(1, n);
    P = [p; visit];
    orbits = 1;
    j = 1;
    
    for i = 1:n
        k = i;
        while (P(2, k) == 0)
            MC(orbits, j) = P(1, k);
            P(2, k) = 1;
            k = P(1, k);
            j++;
        endwhile
        if (j > 1)
            orbits = orbits + 1;
        endif
        j = 1;
    endfor

    %disp(MC);
    retval = MC;
    endtime = time;
    t = endtime - starttime;
    printf("Tempo de execucao: %.5f segundos\n", t);
endfunction