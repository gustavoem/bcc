n = 5;
m = 2;
A = rand(n, m);
b = rand(n);

%calcula todas as normas antes (column oriented)
for j = 1 : m
    infnorm = 0;
    %acha norma infinita da coluna
    for i = 1 : n
        if abs(A(i, j)) > infnorm
            infnorm = abs(A(i, j));
        end
    end
    %divide a coluna pela norma infinita e calcula norma2
    norm2 = 0;
    for i = 1 : n
        A(i, j) = A(i, j) / infnorm;
        norm2 = norm2 + A(i, j) * A(i, j);
    end
    sigma(k) = norm2 * infnorm;
end

for k = 1 : n
    %guarda o u
    if A(k, 1) < 0
        sigma(k) = sigma(k) * -1;
    A(k, 1) = A(k, 1) + sigma(k);

    %guarda o gama
    gama(k) = 1 / sigma(k) * A(k, 1);

    %multiplica Q_k por A_k
    for l = k + 1 : m
        w = 0
        for h = k : n
            w = w + A(h, k) * A(h, l);

    
end





