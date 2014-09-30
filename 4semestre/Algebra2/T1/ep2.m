function retval = ep2(n, d)
    starttime = time;
    %Gera uma sequência aleatória sem repetições com os elementos 1..n
    visit = zeros(1, n);
    j = 1;
    for j = 1:n
        settled = 0;
        while(!settled)
            image = myrand(n);
            if (visit(image) != 1)
                randseq(j) = image;
                settled = 1;
                visit(image) = 1;
            endif
        endwhile
    endfor

    %Isso garante que teremos extamente d ciclos
    j = 1;
    for i = 1:d
        MC(i,2) = randseq(j); 
        %Usaremos essa posição da matriz para indicar o tamanho do ciclo
        %da i-ésima linha
        MC(i,1) = 1;    
        j++;
    endfor

    %Coloca os elementos restantes da sequência em ciclos aleatóriamente
    %escolhidos
    while (j <= n)
        row = myrand(d);
        MC(row, MC(row,1) + 2) = randseq(j);
        MC(row, 1) = MC(row, 1) + 1;
        j++;
    endwhile

    %Constrói o vetor com a permutação resultante
    for i = 1:d
        j = 2;
        while (j <= columns(MC) && MC(i, j) != 0)
            if (j < columns(MC) && MC(i, j + 1) == 0 || j == columns(MC))
                retval(MC(i, j)) = MC(i, 2);
            else
                retval(MC(i, j)) = MC(i, j + 1);
            endif
            j++;
        endwhile
    endfor
    endtime = time;
    t = endtime - starttime;
    printf("Tempo de execucao: %.5f segundos\n", t);
endfunction

%Retorna um inteiro entre 1 e top
function retval = myrand(top)
    retval = mod(int32(rand * (top)), top) + 1;
endfunction