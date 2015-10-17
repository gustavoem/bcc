%Nome: Gustavo Estrela de Matos
%NUSP: 8536051

function retval = count(n)
    starttime = time;
    i = n;
    k = 0;
    while (i > 0)
        k += 1;
        A(k, 1) = i;
        A(k, 2) = n - i;
        last = 2;
        while (A(k, last) > 1)
            k += 1;
            A(k, 1) = 0;
            A(k, length(A(k, : )) + 1) = 0;
            %copia ultima linha pra baixo
            for j = 1:length(A(k, : ))
                A(k, j) = A(k - 1, j);
            endfor
            A(k, last) -= 1;
            %coloca um tirado de "last" no fim da linha
            j = last;
            while (A(k, j) != 0)
                j += 1;
                if (j > length(A))
                    A(k, j) = 0;
                endif
            endwhile
            A(k, j) = 1;
            if (A(k, last) == 1)
                last += 1;
            endif
        endwhile
        i -= 1;
    endwhile
    retval = rows(A) - countDumbLines(A);
    endtime = time;
    printf("Tempo de execucao: %.5f segundos\n", endtime - starttime);
endfunction


%recebe uma vetor e verifica se ele contem um elemento value e devolve a posicao da ocorrencia
function retval = contains(v, value)
    retval = -1;
    for j = 1:length(v)
        if (v(j) == value)
            retval = j;
        endif
    endfor
endfunction

%recebe uma matrix e verifica se duas linhas são permutações uma da outra
function retval = isPerm(A, i, k)
    v = A(i, : );
    w = A(k, : );
    flag = 1;
    for j = 1:length(v)
        l = contains(w, v(j));
        if (l != -1)
            w(l) = -1;
        else
            flag = 0;
            break;
        endif
    endfor
    retval = flag;
endfunction

%conta quantas linhas são permutações de outra
function retval = countDumbLines(A)
    retval = 0;
    for i = 1:rows(A)
        for j = i + 1:rows(A)
            if (isPerm(A, i, j))
                retval += 1;
            endif
        endfor
    endfor
endfunction